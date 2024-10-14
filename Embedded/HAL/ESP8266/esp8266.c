


/**************	Section: Includes *********************************/
#include "esp8266.h"

/**************	Section: Local Variables Declarations *************/

PatternManager_t patternManager;

uint8_t ESP8266_TX_BUFF[ESP8266_TX_BUFF_SIZE] = {0};
uint8_t ESP8266_RX_BUFF[ESP8266_RX_BUFF_SIZE] = {0};

uint8_t ignorePatternsLength = 0;

/**************	Section: Local Methods Prototype Declarations *****/

ESP8266_ResponseType_t _ESP8266_send(USART_Number_t usartNumber, int8_t *restrict data, uint32_t size);

ESP8266_ResponseType_t _ESP8266_sendString(USART_Number_t usartNumber, int8_t *restrict data, uint32_t size);

ESP8266_ResponseType_t
_ESP8266_WaitPattern(USART_Number_t usartNumber, int8_t *restrict data, sint32_t *restrict foundPattern,
                     sint32_t *restrict const count, uint32_t maxSize);


/**************	Section: Methods Declarations *********************/


ESP8266_ResponseType_t HAL_ESP8266_GPIOInit(ESP8266_Config_t *restrict esp) {
    ESP8266_ResponseType_t ret = ESP8266_Return_OK;
    if (esp == NULL) {
        ret = ESP8266_Return_ARG_ERROR;
    } else {

        HAL_GPIO_ConfigPinsDirect(esp->resetPinConfig.port, esp->resetPinConfig.pin, Pin_Mode_Output_2MHZ,
                                  Pin_Mode_Config_Output_PUSH_PULL_GENERAL_PURPOSE);
        HAL_GPIO_SetPinsValue(esp->resetPinConfig.port, esp->resetPinConfig.pin, Pin_State_ON);
    }
    return ret;
}

ESP8266_ResponseType_t HAL_ESP8266_resetHard(ESP8266_Config_t *restrict esp) {
    ESP8266_ResponseType_t ret = ESP8266_Return_OK;
    if (esp == NULL) {
        ret = ESP8266_Return_ARG_ERROR;
    } else {
        if (!esp->resetPinConfig.enableHardReset) {
            ret = ESP8266_Return_ERROR;
        } else {
            HAL_GPIO_SetPinsValue(esp->resetPinConfig.port, esp->resetPinConfig.pin, Pin_State_OFF);
            HAL_Delay_us(50);
            HAL_GPIO_SetPinsValue(esp->resetPinConfig.port, esp->resetPinConfig.pin, Pin_State_ON);
        }
    }
    return ret;
}

ESP8266_ResponseType_t HAL_ESP8266_Init(ESP8266_Config_t *restrict esp) {
    ESP8266_ResponseType_t ret = ESP8266_Return_OK;
    if (esp == NULL) {
        ret = ESP8266_Return_ARG_ERROR;
    } else {


        HAL_Delay_ms(10);
        HAL_ESP8266_closeUART_WIFI_PassThroughConnection(esp);

        if (esp->resetPinConfig.enableHardReset) {
            HAL_ESP8266_GPIOInit(esp);
            HAL_ESP8266_resetHard(esp);
        }


        PatternManager_Init(&patternManager, 5);
//        ignorePatternsLength = 1;


        Pattern_Init(&patternManager.patterns[0], "OK\r\n", 0);
        Pattern_Init(&patternManager.patterns[1], "ERROR\r\n", 0);
        Pattern_Init(&patternManager.patterns[2], "FAIL\r\n", 0);
        Pattern_Init(&patternManager.patterns[3], "Ai-Thinker Technology Co. Ltd.\r\n\r\nready\r\n", 0);

        Pattern_Init(&patternManager.patterns[4], "busy s...\r\n", 0);



        if (esp->selectedConfigs & ESP8266_SelectedConfigs_BasicConfigs) {
            HAL_ESP8266_setEchoMode(esp, esp->basicConfig.echoMode);
            HAL_ESP8266_setSleepMode(esp, esp->basicConfig.sleepMode);
        }


        if (esp->selectedConfigs & ESP8266_SelectedConfigs_WifiConfigs) {
            HAL_ESP8266_setWiFiWorkingMode(esp, esp->wifiConfig.workingMode);
        }

        if (esp->selectedConfigs & ESP8266_SelectedConfigs_ConnectionConfigs) {
            HAL_ESP8266_setMultiConnectionMode(esp, esp->connectionConfig.multiConnection);
        }
        if (esp->selectedConfigs & ESP8266_SelectedConfigs_UARTConfigs) {
            HAL_ESP8266_sendUARTConfig(esp, &esp->uartConfig);
        }


    }
    return ret;

}


ESP8266_ResponseType_t HAL_ESP8266_setWiFiWorkingMode(ESP8266_Config_t *esp, ESP8266_WiFi_WorkingMode_t mode) {
    ESP8266_ResponseType_t ret = ESP8266_Return_OK;

    if (esp == NULL) {
        ret = ESP8266_Return_ARG_ERROR;
    } else {
        switch (mode) {

            case ESP8266_Wifi_WorkingMode_StationMode:
                _ESP8266_sendString(esp->usartNumber, (int8_t *) ESP8266_CMD_SET_WIFI_MODE_STA,
                                    sizeof(ESP8266_CMD_SET_WIFI_MODE_STA));
                break;
            case ESP8266_Wifi_WorkingMode_AccessPointMode:
                _ESP8266_sendString(esp->usartNumber, (int8_t *) ESP8266_CMD_SET_WIFI_MODE_AP,
                                    sizeof(ESP8266_CMD_SET_WIFI_MODE_AP));
                break;
            case ESP8266_Wifi_WorkingMode_StationAndAccessPointMode:
                _ESP8266_sendString(esp->usartNumber, (int8_t *) ESP8266_CMD_SET_WIFI_MODE_AP_STA,
                                    sizeof(ESP8266_CMD_SET_WIFI_MODE_AP_STA));
                break;
        }

        ret = HAL_ESP8266_WaitForResponse(esp, NULL, NULL);
    }
    return ret;
}

ESP8266_ResponseType_t
HAL_ESP8266_configAP(ESP8266_Config_t *esp, int8_t *name, int8_t *pass, ESP8266_ChannelNumber_t channelNumber,
                     ESP8266_EncryptionType_t encryptionType) {
    ESP8266_ResponseType_t ret = ESP8266_Return_OK;
    if ((name == NULL) || (pass == NULL)) {
        ret = ESP8266_Return_ARG_ERROR;
    } else {

        uint32_t size = 0;
        size = sprintf((char *) ESP8266_TX_BUFF, ESP8266_CMD_AP_SET_AP_CFG_SSID_PWD_CH_ENC(%s, %s, %d, %d), name, pass,
                       channelNumber, encryptionType);
        _ESP8266_send(esp->usartNumber, (int8_t *)ESP8266_TX_BUFF, size);
        ret = HAL_ESP8266_WaitForResponse(esp, NULL, NULL);
    }

    return ret;
}


ESP8266_ResponseType_t
HAL_ESP8266_configAP_Full(ESP8266_Config_t *esp, int8_t *name, int8_t *pass, ESP8266_ChannelNumber_t channelNumber,
                          ESP8266_EncryptionType_t encryptionType, ESP8266_MaxConnection_t maxConnection,
                          ESP8266_HiddenState_t hiddenState) {
    ESP8266_ResponseType_t ret = ESP8266_Return_OK;
    if ((name == NULL) || (pass == NULL)) {
        ret = ESP8266_Return_ARG_ERROR;
    } else {

        uint32_t size = 0;
        size = sprintf((char *) ESP8266_TX_BUFF,
                       ESP8266_CMD_AP_SET_AP_CFG_SSID_PWD_CH_ENC_MAXCONN_HIDDEN(%s, %s, %d, %d, %d, %d),
                       name, pass, channelNumber, encryptionType, maxConnection, hiddenState);
        _ESP8266_send(esp->usartNumber, (int8_t *)ESP8266_TX_BUFF, size);
        ret = HAL_ESP8266_WaitForResponse(esp, NULL, NULL);
    }

    return ret;
}

ESP8266_ResponseType_t HAL_ESP8266_setEchoMode(ESP8266_Config_t *restrict config, ESP8266_EchoMode_t mode) {

    ESP8266_ResponseType_t ret = ESP8266_Return_OK;

    if (config == NULL) {
        ret = ESP8266_Return_ARG_ERROR;
    } else {

        switch (mode) {

            case ESP8266_EchoMode_Disable:
                _ESP8266_sendString(config->usartNumber, (int8_t *) ESP8266_CMD_SET_ECHO_OFF,
                                    sizeof(ESP8266_CMD_SET_ECHO_OFF));

                break;
            case ESP8266_EchoMode_Enable:
                _ESP8266_sendString(config->usartNumber, (int8_t *) ESP8266_CMD_SET_ECHO_ON,
                                    sizeof(ESP8266_CMD_SET_ECHO_ON));
                break;
        }
//        HAL_Delay_ms(1);
        ret = HAL_ESP8266_WaitForResponse(config, NULL, NULL);

    }
    return ret;
}

ESP8266_ResponseType_t HAL_ESP8266_setSleepMode(ESP8266_Config_t *restrict config, ESP8266_SleepMode_t sleepMode) {
    ESP8266_ResponseType_t ret = ESP8266_Return_OK;

    if (config == NULL) {
        ret = ESP8266_Return_ARG_ERROR;
    } else {
        switch (sleepMode) {

            case ESP8266_SleepMode_Disable:
                _ESP8266_sendString(config->usartNumber, (int8_t *) ESP8266_CMD_SET_SLEEP_MODE_DISABLE,
                                    sizeof(ESP8266_CMD_SET_SLEEP_MODE_DISABLE));
                break;
            case ESP8266_SleepMode_Light:
                _ESP8266_sendString(config->usartNumber, (int8_t *) ESP8266_CMD_SET_SLEEP_MODE_LIGHT,
                                    sizeof(ESP8266_CMD_SET_SLEEP_MODE_LIGHT));
                break;
            case ESP8266_SleepMode_Modem:
                _ESP8266_sendString(config->usartNumber, (int8_t *) ESP8266_CMD_SET_SLEEP_MODE_MODEM,
                                    sizeof(ESP8266_CMD_SET_SLEEP_MODE_MODEM));
                break;
        }
        ret = HAL_ESP8266_WaitForResponse(config, NULL, NULL);
    }

    return ret;

}

ESP8266_ResponseType_t HAL_ESP8266_send(ESP8266_Config_t *restrict esp, uint8_t *restrict data, uint32_t size) {
    ESP8266_ResponseType_t ret = ESP8266_Return_OK;

    if ((esp == NULL) || (data == NULL) || (size == 0)) {
        ret = ESP8266_Return_ARG_ERROR;
    } else {
        ret = _ESP8266_send(esp->usartNumber,(int8_t *) data, size);
        ret = HAL_ESP8266_WaitForResponse(esp, NULL, NULL);

    }
    return ret;
}

ESP8266_ResponseType_t
HAL_ESP8266_sendString(ESP8266_Config_t *restrict esp, uint8_t *restrict data, uint32_t maxSize) {
    ESP8266_ResponseType_t ret = ESP8266_Return_OK;

    if ((esp == NULL) || (data == NULL) || (maxSize == 0)) {
        ret = ESP8266_Return_ARG_ERROR;
    } else {
        ret = _ESP8266_sendString(esp->usartNumber,(int8_t *) data, maxSize);
        ret = HAL_ESP8266_WaitForResponse(esp, NULL, NULL);
    }
    return ret;
}

ESP8266_ResponseType_t
HAL_ESP8266_joinAccessPoint(ESP8266_Config_t *restrict esp, int8_t *restrict name, int8_t *restrict pass) {
    ESP8266_ResponseType_t ret = ESP8266_Return_OK;

    if ((esp == NULL) || (name == NULL) || (pass == NULL)) {
        ret = ESP8266_Return_ARG_ERROR;
    } else {
        uint32_t size = 0;
        size = sprintf((char *) ESP8266_TX_BUFF, ESP8266_CMD_STA_JOIN_AP(%s, %s), name, pass);
        ret = _ESP8266_send(esp->usartNumber, (int8_t *)ESP8266_TX_BUFF, size);
        ret = HAL_ESP8266_WaitForResponse(esp, NULL, NULL);


    }
    return ret;
}


ESP8266_ResponseType_t
HAL_ESP8266_joinAccessPoint_BSSID(ESP8266_Config_t *restrict esp, uint8_t *restrict name, uint8_t *restrict pass,
                                  uint8_t *restrict bssid) {
    ESP8266_ResponseType_t ret = ESP8266_Return_OK;

    if ((esp == NULL) || (name == NULL) || (pass == NULL) || (bssid == NULL)) {
        ret = ESP8266_Return_ARG_ERROR;
    } else {
        uint32_t size = 0;
        size = sprintf((char *) ESP8266_TX_BUFF, ESP8266_CMD_STA_JOIN_AP_BSSID(%s, %s, %s), name, pass, bssid);
        ret = _ESP8266_send(esp->usartNumber, (int8_t *)ESP8266_TX_BUFF, size);
        ret = HAL_ESP8266_WaitForResponse(esp, NULL, NULL);
    }
    return ret;
}

ESP8266_ResponseType_t HAL_ESP8266_disconnectAccessPoint(ESP8266_Config_t *restrict esp) {
    ESP8266_ResponseType_t ret = ESP8266_Return_OK;

    if (esp == NULL) {
        ret = ESP8266_Return_ARG_ERROR;
    } else {
        ret = _ESP8266_sendString(esp->usartNumber, (int8_t *) ESP8266_CMD_STA_QUIT_AP,
                                  sizeof ESP8266_CMD_STA_QUIT_AP);
        ret = HAL_ESP8266_WaitForResponse(esp, NULL, NULL);
    }
    return ret;
}

ESP8266_ResponseType_t
HAL_ESP8266_listAvailableAccessPoints(ESP8266_Config_t *restrict esp, ESP8266_AccessPoint_t *restrict accessPoints,
                                      uint32_t *restrict count,
                                      uint32_t maxCount) {

	/* TODO: HAL_ESP8266_listAvailableAccessPoints */
	return ESP8266_Return_OK;
}

ESP8266_ResponseType_t
HAL_ESP8266_setMACAddress(ESP8266_Config_t *restrict esp, ESP8266_WiFi_WorkingMode_t targetMode,
                          const uint8_t *restrict mac) {
    ESP8266_ResponseType_t ret = ESP8266_Return_OK;

    if ((esp == NULL) || (mac == NULL) || ((uint8_t) targetMode > ESP8266_Wifi_WorkingMode_StationAndAccessPointMode)) {
        ret = ESP8266_Return_ARG_ERROR;
    } else {
        uint16_t size = 0;
        if (targetMode & ESP8266_Wifi_WorkingMode_StationMode) {
            size = sprintf((char *) ESP8266_TX_BUFF, ESP8266_CMD_STA_SET_MAC(%s), mac);
            ret = _ESP8266_send(esp->usartNumber, (int8_t *)ESP8266_TX_BUFF, size);
            ret = HAL_ESP8266_WaitForResponse(esp, NULL, NULL);
        }
        if (targetMode & ESP8266_Wifi_WorkingMode_AccessPointMode) {

            size = sprintf((char *) ESP8266_TX_BUFF, ESP8266_CMD_AP_SET_MAC(%s), mac);
            ret = _ESP8266_send(esp->usartNumber, (int8_t *)ESP8266_TX_BUFF, size);
            ret = HAL_ESP8266_WaitForResponse(esp, NULL, NULL);
        }
    }
    return ret;
}


ESP8266_ResponseType_t
HAL_ESP8266_setIPAddress(ESP8266_Config_t *restrict esp, ESP8266_WiFi_WorkingMode_t targetMode,
                         const uint8_t *restrict ip) {
    ESP8266_ResponseType_t ret = ESP8266_Return_OK;

    if ((esp == NULL) || (ip == NULL) || ((uint8_t) targetMode > ESP8266_Wifi_WorkingMode_StationAndAccessPointMode)) {
        ret = ESP8266_Return_ARG_ERROR;
    } else {
        uint16_t size = 0;
        if (targetMode & ESP8266_Wifi_WorkingMode_StationMode) {
            size = sprintf((char *) ESP8266_TX_BUFF, ESP8266_CMD_STA_SET_IP(%s), ip);
            ret = _ESP8266_send(esp->usartNumber, (int8_t *)ESP8266_TX_BUFF, size);
            ret = HAL_ESP8266_WaitForResponse(esp, NULL, NULL);
        }
        if (targetMode & ESP8266_Wifi_WorkingMode_AccessPointMode) {

            size = sprintf((char *) ESP8266_TX_BUFF, ESP8266_CMD_AP_SET_IP(%s), ip);
            ret = _ESP8266_send(esp->usartNumber, (int8_t *)ESP8266_TX_BUFF, size);
            ret = HAL_ESP8266_WaitForResponse(esp, NULL, NULL);
        }
    }
    return ret;
}

ESP8266_ResponseType_t
HAL_ESP8266_getIP_MAC(ESP8266_Config_t *restrict esp, uint8_t *restrict stationIP, uint8_t *restrict stationMAC,
                      uint8_t *restrict APIP, uint8_t *restrict APMAC) {
    ESP8266_ResponseType_t ret = ESP8266_Return_OK;

    if (esp == NULL) {
        ret = ESP8266_Return_ARG_ERROR;
    } else {
        _ESP8266_sendString(esp->usartNumber, (int8_t *) ESP8266_CMD_GET_IP_MAC, sizeof(ESP8266_CMD_GET_IP_MAC));
        // WAIT and RETURN
        //todo: Get IP func
    }
    return ret;
}

ESP8266_ResponseType_t
HAL_ESP8266_setIP_Gateway_Mask(ESP8266_Config_t *restrict esp, ESP8266_WiFi_WorkingMode_t targetMode,
                               const uint8_t *restrict ip,
                               const uint8_t *restrict gateway, const uint8_t *restrict mask) {
    ESP8266_ResponseType_t ret = ESP8266_Return_OK;

    if ((esp == NULL) || (ip == NULL) || ((uint8_t) targetMode > ESP8266_Wifi_WorkingMode_StationAndAccessPointMode)) {
        ret = ESP8266_Return_ARG_ERROR;
    } else {
        uint16_t size = 0;
        if (targetMode & ESP8266_Wifi_WorkingMode_StationMode) {
            size = sprintf((char *) ESP8266_TX_BUFF, ESP8266_CMD_STA_SET_IP_GATE_MASK(%s, %s, %s), ip, gateway, mask);
            ret = _ESP8266_send(esp->usartNumber, (int8_t *)ESP8266_TX_BUFF, size);
            ret = HAL_ESP8266_WaitForResponse(esp, NULL, NULL);
        }
        if (targetMode & ESP8266_Wifi_WorkingMode_AccessPointMode) {

            size = sprintf((char *) ESP8266_TX_BUFF, ESP8266_CMD_AP_SET_IP_GATE_MASK(%s, %s, %s), ip, gateway, mask);
            ret = _ESP8266_send(esp->usartNumber, (int8_t *)ESP8266_TX_BUFF, size);
            ret = HAL_ESP8266_WaitForResponse(esp, NULL, NULL);
        }
    }
    return ret;
}

ESP8266_ResponseType_t
HAL_ESP8266_getAPConnectedDevices(ESP8266_Config_t *restrict esp, ESP8266_ConnectedDevice_t *restrict connectedDevices,
                                  uint32_t *restrict count, uint32_t max) {
    ESP8266_ResponseType_t ret = ESP8266_Return_OK;

    if ((esp == NULL) || (connectedDevices == NULL) || (count == NULL) || (max == 0)) {
        ret = ESP8266_Return_ARG_ERROR;
    } else {
        _ESP8266_sendString(esp->usartNumber, (int8_t *) ESP8266_CMD_STA_GET_AP_ALL,
                            sizeof(ESP8266_CMD_STA_GET_AP_ALL));
        ret = HAL_ESP8266_WaitForResponse(esp, NULL, NULL);
        if (ret == ESP8266_Return_OK) {
            // TODO: get Connected Devices with max
        }
    }
    return ret;

}

ESP8266_ResponseType_t
HAL_ESP8266_getAllAPConnectedDevices(ESP8266_Config_t *restrict esp,
                                     ESP8266_ConnectedDevice_t *restrict connectedDevices,
                                     uint32_t *restrict count, uint32_t max) {
    ESP8266_ResponseType_t ret = ESP8266_Return_OK;

    if ((esp == NULL) || (connectedDevices == NULL) || (count == NULL) || (max == 0)) {
        ret = ESP8266_Return_ARG_ERROR;
    } else {
        // TODO: Get All Connected Devices / this method dynamically append
    }
    return ret;

}

ESP8266_ResponseType_t
HAL_ESP8266_configDHCP(ESP8266_Config_t *restrict esp, ESP8266_WiFi_WorkingMode_t targetMode,
                       ESP8266_DHCP_State_t dhcpState,
                       uint8_t *restrict startIP, uint8_t *restrict endIP) {
    ESP8266_ResponseType_t ret = ESP8266_Return_OK;

    if (esp == NULL) {
        ret = ESP8266_Return_ARG_ERROR;
    } else {
        switch (dhcpState) {

            case ESP8266_DHCP_State_Disable:
                if (targetMode & ESP8266_Wifi_WorkingMode_StationMode) {
                    _ESP8266_sendString(esp->usartNumber, (int8_t *) ESP8266_CMD_SET_DHCP_STA_OFF,
                                        sizeof ESP8266_CMD_SET_DHCP_STA_OFF);
                }
                if (targetMode & ESP8266_Wifi_WorkingMode_AccessPointMode) {
                    _ESP8266_sendString(esp->usartNumber, (int8_t *) ESP8266_CMD_SET_DHCP_AP_OFF,
                                        sizeof ESP8266_CMD_SET_DHCP_AP_OFF);
                }

                break;
            case ESP8266_DHCP_State_Enable:
                if (targetMode & ESP8266_Wifi_WorkingMode_StationMode) {
                    _ESP8266_sendString(esp->usartNumber, (int8_t *) ESP8266_CMD_SET_DHCP_STA_ON,
                                        sizeof ESP8266_CMD_SET_DHCP_STA_ON);
                }
                if (targetMode & ESP8266_Wifi_WorkingMode_AccessPointMode) {
                    _ESP8266_sendString(esp->usartNumber, (int8_t *) ESP8266_CMD_SET_DHCP_AP_ON,
                                        sizeof ESP8266_CMD_SET_DHCP_AP_ON);
                    if ((startIP != NULL) && (endIP != NULL)) {
                        uint32_t size = 0;
                        size = sprintf((char *) ESP8266_TX_BUFF,
                                       ESP8266_CMD_SET_DHCP_IP_RANGE_ENABLE_LEASETIME_STARTIP_ENDIP(%d, %s, %s),
                                       2880, startIP, endIP);
                        _ESP8266_send(esp->usartNumber, (int8_t *)ESP8266_TX_BUFF, size);
                        ret = HAL_ESP8266_WaitForResponse(esp, NULL, NULL);

                    } else {

                        _ESP8266_sendString(esp->usartNumber, (int8_t *) ESP8266_CMD_SET_DHCP_IP_RANGE_DISABLE,
                                            sizeof ESP8266_CMD_SET_DHCP_IP_RANGE_DISABLE);
                        ret = HAL_ESP8266_WaitForResponse(esp, NULL, NULL);
                    }
                }


                break;
        }
    }
    return ret;
}


ESP8266_ResponseType_t
HAL_ESP8266_connStart(ESP8266_Config_t *restrict esp, ESP8266_LinkNumber_t linkNumber,
                      ESP8266_ProtocolType_t protocolType,
                      int8_t *restrict ip, uint16_t port, ESP8266_ProtocolOptions_t *restrict options) {
    ESP8266_ResponseType_t ret = ESP8266_Return_OK;

    if ((esp == NULL) || (ip == NULL)) {
        ret = ESP8266_Return_ARG_ERROR;
    } else {
        uint32_t size = 0;

        if (linkNumber == ESP8266_LinkNumber_Default) {
            switch (protocolType) {

                case ESP8266_ProtocolType_TCP:

                    if (options == NULL) {
                        size = sprintf((char *) ESP8266_TX_BUFF, ESP8266_CMD_START_TCP_SINGLE(%s, %d), ip, port);
                    } else {
                        size = sprintf((char *) ESP8266_TX_BUFF, ESP8266_CMD_START_TCP_SINGLE_KEEPALIVE(%s, %d, %d), ip,
                                       port, options->TCP.alive);
                    }

                    break;
                case ESP8266_ProtocolType_UDP:
                    if (options == NULL) {
                        size = sprintf((char *) ESP8266_TX_BUFF, ESP8266_CMD_START_UDP_SINGLE(%s, %d), ip, port);
                    } else {
                        size = sprintf((char *) ESP8266_TX_BUFF,
                                       ESP8266_CMD_START_UDP_SINGLE_LPORT_MODE(%s, %d, %s, %d),
                                       ip, port, options->UDP.localIP, options->UDP.localPort);
                    }

                    break;

                case ESP8266_ProtocolType_SSL:
                    if (options == NULL) {
                        size = sprintf((char *) ESP8266_TX_BUFF, ESP8266_CMD_START_SSL_SINGLE(%s, %d), ip, port);
                    } else {
                        size = sprintf((char *) ESP8266_TX_BUFF, ESP8266_CMD_START_SSL_SINGLE_KEEPALIVE(%s, %d, %d), ip,
                                       port, options->SSL.alive);
                    }
            }


        } else {
            switch (protocolType) {

                case ESP8266_ProtocolType_TCP:

                    if (options == NULL) {
                        size = sprintf((char *) ESP8266_TX_BUFF, ESP8266_CMD_START_TCP_MULTI(%d, %s, %d), linkNumber,
                                       ip,
                                       port);
                    } else {
                        size = sprintf((char *) ESP8266_TX_BUFF, ESP8266_CMD_START_TCP_MULTI_KEEPALIVE(%d, %s, %d, %d),
                                       linkNumber, ip,
                                       port, options->TCP.alive);
                    }

                    break;
                case ESP8266_ProtocolType_UDP:
                    if (options == NULL) {
                        size = sprintf((char *) ESP8266_TX_BUFF, ESP8266_CMD_START_UDP_MULTI(%d, %s, %d), linkNumber,
                                       ip,
                                       port);
                    } else {
                        size = sprintf((char *) ESP8266_TX_BUFF,
                                       ESP8266_CMD_START_UDP_MULTI_LPORT_MODE(%d, %s, %d, %s, %d),
                                       linkNumber, ip, port, options->UDP.localIP, options->UDP.localPort);
                    }

                    break;

                case ESP8266_ProtocolType_SSL:
                    if (options == NULL) {
                        size = sprintf((char *) ESP8266_TX_BUFF, ESP8266_CMD_START_SSL_MULTI(%d, %s, %d), linkNumber,
                                       ip,
                                       port);
                    } else {
                        size = sprintf((char *) ESP8266_TX_BUFF, ESP8266_CMD_START_SSL_MULTI_KEEPALIVE(%d, %s, %d, %d),
                                       linkNumber, ip,
                                       port, options->SSL.alive);
                    }
            }
        }

        _ESP8266_send(esp->usartNumber, (int8_t *)ESP8266_TX_BUFF, size);
        ret = HAL_ESP8266_WaitForResponse(esp, NULL, NULL);
    }
    return ret;
}

ESP8266_ResponseType_t HAL_ESP8266_connClose(ESP8266_Config_t *restrict esp, ESP8266_LinkNumber_t linkNumber) {
    ESP8266_ResponseType_t ret = ESP8266_Return_OK;

    if (esp == NULL) {
        ret = ESP8266_Return_ARG_ERROR;
    } else {
        if (linkNumber == ESP8266_LinkNumber_Default) {
            _ESP8266_sendString(esp->usartNumber,  ESP8266_CMD_CLOSE_CON, ESP8266_TX_BUFF_SIZE);
        } else {
            uint32_t size = 0;
            size = sprintf((char *) ESP8266_TX_BUFF, ESP8266_CMD_CLOSE_CON_LINK(%d), linkNumber);
            _ESP8266_send(esp->usartNumber, (int8_t *) ESP8266_TX_BUFF, size);
            ret = HAL_ESP8266_WaitForResponse(esp, NULL, NULL);
        }
    }
    return ret;
}

ESP8266_ResponseType_t
HAL_ESP8266_connSendBytes(ESP8266_Config_t *restrict esp, ESP8266_LinkNumber_t linkNumber, uint8_t *restrict data,
                          uint32_t size, ESP8266_UART_WiFi_PassThroughMode_t mode) {
    ESP8266_ResponseType_t ret = ESP8266_Return_OK;

    if ((esp == NULL) || (data == NULL) || (size == 0)) {
        ret = ESP8266_Return_ARG_ERROR;
    } else {
        if (mode == ESP8266_UART_WiFi_PassThroughMode_Off) {
            uint32_t command_size = 0;
            if (linkNumber == ESP8266_LinkNumber_Default) {
                command_size = sprintf((char *) ESP8266_TX_BUFF, ESP8266_CMD_SEND_TCP_SINGLE(%lu), size);

            } else if ((uint8_t) linkNumber <= ESP8266_LinkNumber_4) {
                command_size = sprintf((char *) ESP8266_TX_BUFF, ESP8266_CMD_SEND_TCP_MULTI(%d, %lu), linkNumber, size);
            }
            _ESP8266_send(esp->usartNumber, (int8_t *)ESP8266_TX_BUFF, command_size);
            ret = HAL_ESP8266_WaitForResponse(esp, NULL, NULL);
            if (ret == ESP8266_Return_OK) {

                _ESP8266_send(esp->usartNumber, (int8_t *)data, size);
                ret = HAL_ESP8266_WaitForResponse(esp, NULL, NULL);
            }
        } else {
            _ESP8266_send(esp->usartNumber, (int8_t *) data, size);
        }


    }
    return ret;

}

ESP8266_ResponseType_t
HAL_ESP8266_connSendString(ESP8266_Config_t *restrict esp, ESP8266_LinkNumber_t linkNumber, int8_t *restrict data,
                           sint32_t maxSize) {

    ESP8266_ResponseType_t ret = ESP8266_Return_OK;

    if ((esp == NULL) || (data == NULL)) {
        ret = ESP8266_Return_ARG_ERROR;
    } else {
        uint32_t size = 0;
        if (maxSize == -1) {
            // getting length of the data
            // (Note i ignored the warning of converting uint32_t -> sint32_t
            // because the channelUpdateMsg length will be so small compared to 2^31)
            maxSize = strlen(data);
        }
        if (linkNumber == ESP8266_LinkNumber_Default) {
            size = sprintf((char *) ESP8266_TX_BUFF, ESP8266_CMD_SEND_STRING_TCP_SINGLE(%lu), maxSize);

        } else if ((uint8_t) linkNumber <= ESP8266_LinkNumber_4) {
            size = sprintf((char *) ESP8266_TX_BUFF, ESP8266_CMD_SEND_STRING_TCP_MULTI(%d, %lu), linkNumber, maxSize);
        }
        _ESP8266_send(esp->usartNumber, (int8_t *)ESP8266_TX_BUFF, size);
        ret = HAL_ESP8266_WaitForResponse(esp, NULL, NULL);
        if (ret == ESP8266_Return_OK) {
            _ESP8266_send(esp->usartNumber, data, size);
            ret = HAL_ESP8266_WaitForResponse(esp, NULL, NULL);
        }

    }
    return ret;
}

ESP8266_ResponseType_t HAL_ESP8266_closeServer(ESP8266_Config_t *restrict esp) {
    ESP8266_ResponseType_t ret = ESP8266_Return_OK;

    if (esp == NULL) {
        ret = ESP8266_Return_ARG_ERROR;
    } else {
        _ESP8266_sendString(esp->usartNumber, ESP8266_CMD_SET_SERVER_OFF, sizeof(ESP8266_CMD_SET_SERVER_OFF));
        ret = HAL_ESP8266_WaitForResponse(esp, NULL, NULL);
    }
    return ret;
}

ESP8266_ResponseType_t
HAL_ESP8266_setMultiConnectionMode(ESP8266_Config_t *restrict esp, ESP8266_Connection_Multi_t mode) {
    ESP8266_ResponseType_t ret = ESP8266_Return_OK;

    if (esp == NULL) {
        ret = ESP8266_Return_ARG_ERROR;
    } else {
        switch (mode) {

            case ESP8266_Connection_Multi_Disable:
                _ESP8266_sendString(esp->usartNumber, ESP8266_CMD_SET_MULTIPLE_CON_OFF,
                                    sizeof(ESP8266_CMD_SET_MULTIPLE_CON_OFF));
                break;
            case ESP8266_Connection_Multi_Enable:
                _ESP8266_sendString(esp->usartNumber, ESP8266_CMD_SET_MULTIPLE_CON_ON,
                                    sizeof(ESP8266_CMD_SET_MULTIPLE_CON_ON));
                break;
        }
        ret = HAL_ESP8266_WaitForResponse(esp, NULL, NULL);
    }
    return ret;
}

ESP8266_ResponseType_t HAL_ESP8266_startServer(ESP8266_Config_t *restrict esp, uint16_t port) {
    ESP8266_ResponseType_t ret = ESP8266_Return_OK;

    if (esp == NULL) {
        ret = ESP8266_Return_ARG_ERROR;
    } else {
        // Enable Multi Connection Mode

        // Start Server
        uint32_t size = 0;
        size = sprintf((char *) ESP8266_TX_BUFF, ESP8266_CMD_SET_SERVER_ON_PORT(%d), port);
        _ESP8266_send(esp->usartNumber, (int8_t *) ESP8266_TX_BUFF, size);
        ret = HAL_ESP8266_WaitForResponse(esp, NULL, NULL);

    }
    return ret;
}


ESP8266_ResponseType_t HAL_ESP8266_enableUART_WIFI_PASSThroughMode(ESP8266_Config_t *esp) {
    ESP8266_ResponseType_t ret = ESP8266_Return_OK;

    if (esp == NULL) {
        ret = ESP8266_Return_ARG_ERROR;
    } else {
        _ESP8266_send(esp->usartNumber, (int8_t *) ESP8266_CMD_SET_TRANSFER_MODE_UART_WIFI_PASSTHROIGH,
                      sizeof(ESP8266_CMD_SET_TRANSFER_MODE_UART_WIFI_PASSTHROIGH));
        ret = HAL_ESP8266_WaitForResponse(esp, NULL, NULL);
    }
    return ret;
}

ESP8266_ResponseType_t HAL_ESP8266_test(ESP8266_Config_t *restrict esp) {
    ESP8266_ResponseType_t ret = ESP8266_Return_OK;

    if (esp == NULL) {
        ret = ESP8266_Return_ARG_ERROR;
    } else {
        _ESP8266_send(esp->usartNumber, (int8_t *) ESP8266_CMD_TEST,
                      sizeof(ESP8266_CMD_TEST));
        ret = HAL_ESP8266_WaitForResponse(esp, NULL, NULL);
    }
    return ret;
}


ESP8266_ResponseType_t HAL_ESP8266_reset(ESP8266_Config_t *restrict esp) {
    ESP8266_ResponseType_t ret = ESP8266_Return_OK;

    if (esp == NULL) {
        ret = ESP8266_Return_ARG_ERROR;
    } else {
        _ESP8266_send(esp->usartNumber, (int8_t *) ESP8266_CMD_RESET,
                      sizeof(ESP8266_CMD_RESET));
        ret = HAL_ESP8266_WaitForResponse(esp, NULL, NULL);
    }
    return ret;
}


ESP8266_ResponseType_t HAL_ESP8266_closeUART_WIFI_PassThroughConnection(ESP8266_Config_t *restrict esp) {

    ESP8266_ResponseType_t ret = ESP8266_Return_OK;

    if (esp == NULL) {
        ret = ESP8266_Return_ARG_ERROR;
    } else {
        _ESP8266_sendString(esp->usartNumber, ESP8266_CMD_UART_WIFI_PASSTHROUGH_BREAK,
                            sizeof(ESP8266_CMD_UART_WIFI_PASSTHROUGH_BREAK));
        HAL_Delay_ms(100);
        _ESP8266_sendString(esp->usartNumber, ESP8266_CMD_TEST, sizeof(ESP8266_CMD_TEST));
        HAL_Delay_ms(200);
    }
    return ret;

}

ESP8266_ResponseType_t
HAL_ESP8266_startUART_WIFI_PassThroughConnection(ESP8266_Config_t *restrict esp, ESP8266_ProtocolType_t protocolType,
                                                 int8_t *restrict ip, uint16_t port,
                                                 ESP8266_ProtocolOptions_t *restrict options) {
    ESP8266_ResponseType_t ret = ESP8266_Return_OK;
    if (esp == NULL) {
        ret = ESP8266_Return_ARG_ERROR;
    } else {

        ret = HAL_ESP8266_setMultiConnectionMode(esp, ESP8266_Connection_Multi_Disable);
        if (ret == ESP8266_Return_OK)
            ret = HAL_ESP8266_enableUART_WIFI_PASSThroughMode(esp);
        if (ret == ESP8266_Return_OK)
            ret = HAL_ESP8266_connStart(esp, ESP8266_LinkNumber_Default, protocolType, ip, port, options);
        if (ret == ESP8266_Return_OK) {

            _ESP8266_sendString(esp->usartNumber, (int8_t *) ESP8266_CMD_OPEN_SEND_COMMAND,
                                sizeof(ESP8266_CMD_OPEN_SEND_COMMAND));
            ret = HAL_ESP8266_WaitForResponse(esp, NULL, NULL);
            uint8_t res = 0;

            HAL_USART_waitForChar(esp->usartNumber, '>', TIMEOUT_INF_INT32_T);
            res = '>';
            ret = (res == '>') ? ESP8266_Return_OK : ESP8266_Return_ERROR;
        }
    }

    return ret;
}

ESP8266_ResponseType_t HAL_ESP8266_WaitForResponse(ESP8266_Config_t *esp, sint32_t *count,
                                                   ESP8266_ResponseType_t *espRespType) {

//	return ESP8266_Return_OK;
//	// TODO:
    ESP8266_ResponseType_t ret = ESP8266_Return_OK;
    uint8_t FLAG = 0;
    if (count == NULL) {
        FLAG |= 0b01;
        count = (sint32_t *) malloc(sizeof(sint32_t));
    }
    if (espRespType == NULL) {
        FLAG |= 0b10;
        espRespType = (ESP8266_ResponseType_t *) malloc(sizeof(ESP8266_ResponseType_t));
    }

    _ESP8266_WaitPattern(esp->usartNumber, (int8_t *) ESP8266_RX_BUFF, (sint32_t *) espRespType, count,
    			ESP8266_RX_BUFF_SIZE);
    if (*count == -1) {
        ret = ESP8266_Return_NotFound_OR_NotFinished;
    } else {
        ret = *espRespType;
    }
    if (FLAG & 0b01) {
        free(count);
    }
    if (FLAG & 0b10) {
        free(espRespType);
    }

    return ret;
}


ESP8266_ResponseType_t
HAL_ESP8266_sendUARTConfig(ESP8266_Config_t *restrict esp, ESP8266_UART_Config_t *restrict config) {
    ESP8266_ResponseType_t ret = ESP8266_Return_OK;
    if ((esp == NULL) || (config == NULL)) {
        ret = ESP8266_Return_ARG_ERROR;
    } else {
        uint32_t size = 0;
        size = sprintf((char *) ESP8266_TX_BUFF, ESP8266_CMD_SET_UART_CFG(%u, %u, %u, %u, %u), config->newBaudRate,
                       config->dataBits, config->stopBits, config->parityBits, config->flowControl);
        _ESP8266_send(esp->usartNumber, (int8_t *)ESP8266_TX_BUFF, size);
        ret = HAL_ESP8266_WaitForResponse(esp, NULL, NULL);
    }
    return ret;
}

ESP8266_ResponseType_t HAL_ESP8266_ReceiveByte(ESP8266_Config_t *restrict esp, uint8_t *data, uint32_t timeOut){
    ESP8266_ResponseType_t ret = ESP8266_Return_OK;
    if (esp == NULL) {
        ret = ESP8266_Return_ARG_ERROR;
    } else {
        HAL_USART_ReceiveByte(esp->usartNumber,data,timeOut);
    }
    return ret;
}

ESP8266_ResponseType_t HAL_ESP8266_ReceiveBytes(ESP8266_Config_t *restrict esp, uint8_t *data, uint32_t size, uint32_t timeOut){
    ESP8266_ResponseType_t ret = ESP8266_Return_OK;
    if (esp == NULL) {
        ret = ESP8266_Return_ARG_ERROR;
    } else {
       if (E_TIMEOUT == HAL_USART_ReceiveBytes(esp->usartNumber,data,size,timeOut)){
           ret = ESP8266_Return_TimeOut;
       }
    }
    return ret;
}



/**************	Section: Helper Methods Declarations  *************/
ESP8266_ResponseType_t _ESP8266_send(USART_Number_t usartNumber, int8_t *restrict data, uint32_t size) {
    return HAL_USART_SendBytes(usartNumber, (uint8_t *)data, size);
}

ESP8266_ResponseType_t _ESP8266_sendString(USART_Number_t usartNumber, int8_t *restrict data, uint32_t size) {
    return HAL_USART_SendBytes(usartNumber, (uint8_t *)data, size - 1);
}


ESP8266_ResponseType_t
_ESP8266_WaitPattern(USART_Number_t usartNumber, int8_t *restrict data, sint32_t *restrict foundPattern,
                     sint32_t *restrict const count, uint32_t maxSize) {

    return HAL_USART_ReceiveUntilPattern(usartNumber, (uint8_t *) data, foundPattern, count, maxSize, &patternManager,
                                         patternManager.count - ignorePatternsLength);
}


