
#ifndef STM32_DRIVERS_ESP8266_H
#define STM32_DRIVERS_ESP8266_H



/**************	Section: Includes ***************************/

#include "std_types.h"
#include <stdio.h>
#include <string.h>
#include "interrupts.h"
#include "patterns.h"
#include "usart.h"
#include "gpio.h"

#include "delay.h"
/**************	Section: Macro Definitions Declarations *****/


#define ESP8266_RX_BUFF_SIZE    (500)
#define ESP8266_TX_BUFF_SIZE    (100)


#define ESP8266_MSG_TERMINATION "\r\n"

#define ESP8266_CFG_BAUDRATE_DEFAULT 9600
#define ESP8266_CFG_PORT_DEFAULT 333

#define ESP8266_CMD_UART_WIFI_PASSTHROUGH_BREAK "+++"

#define ESP8266_CMD_TEST "AT\r\n"
#define ESP8266_CMD_RESET "AT+RST\r\n"
#define ESP8266_CMD_FACTORY_RESET "AT+RESTORE\r\n"

#define ESP8266_CMD_SLEEP_TIME(_TIME) "AT+GSLP="STR(_TIME)"\r\n"

#define ESP8266_CMD_GET_SLEEP_MODE "AT+SLEEP?\r\n"
#define ESP8266_CMD_SET_SLEEP_MODE_DISABLE "AT+SLEEP=0\r\n"
#define ESP8266_CMD_SET_SLEEP_MODE_LIGHT   "AT+SLEEP=1\r\n"
#define ESP8266_CMD_SET_SLEEP_MODE_MODEM   "AT+SLEEP=2\r\n"

#define ESP8266_CMD_GET_FIRMWAREVERSION "AT+GMR\r\n"

#define ESP8266_CMD_SET_ECHO_ON "ATE1\r\n"
#define ESP8266_CMD_SET_ECHO_OFF "ATE0\r\n"

// TODO: RF Power Options in Basic Commands


#define ESP8266_CMD_GET_WIFI_MODE       "AT+CWMODE_CUR?\r\n"
#define ESP8266_CMD_SET_WIFI_MODE_STA       "AT+CWMODE_CUR=1\r\n"
#define ESP8266_CMD_SET_WIFI_MODE_AP        "AT+CWMODE_CUR=2\r\n"
#define ESP8266_CMD_SET_WIFI_MODE_AP_STA    "AT+CWMODE_CUR=3\r\n"


#define ESP8266_CMD_GET_WIFI_DEF_MODE       "AT+CWMODE_DEF?\r\n"
#define ESP8266_CMD_SET_WIFI_DEF_MODE_STA       "AT+CWMODE_DEF=1\r\n"
#define ESP8266_CMD_SET_WIFI_DEF_MODE_AP        "AT+CWMODE_DEF=2\r\n"
#define ESP8266_CMD_SET_WIFI_DEF_MODE_AP_STA    "AT+CWMODE_DEF=3\r\n"


#define ESP8266_CMD_GET_IP_MAC "AT+CIFSR\r\n"


#define ESP8266_CMD_GET_DHCP_CFG "AT+CWDHCP_CUR?\r\n"

#define ESP8266_CMD_SET_DHCP_AP_ON "AT+CWDHCP_CUR=0,1\r\n"
#define ESP8266_CMD_SET_DHCP_AP_OFF "AT+CWDHCP_CUR=0,0\r\n"

#define ESP8266_CMD_SET_DHCP_STA_ON "AT+CWDHCP_CUR=1,1\r\n"
#define ESP8266_CMD_SET_DHCP_STA_OFF "AT+CWDHCP_CUR=1,0\r\n"

#define ESP8266_CMD_SET_DHCP_STA_AP_ON "AT+CWDHCP_CUR=2,1\r\n"
#define ESP8266_CMD_SET_DHCP_STA_AP_OFF "AT+CWDHCP_CUR=2,0\r\n"


#define ESP8266_CMD_GET_DHCP_CFG_DEF "AT+CWDHCP_DEF?\r\n"

#define ESP8266_CMD_SET_DHCP_AP_ON_DEF "AT+CWDHCP_DEF=0,1\r\n"
#define ESP8266_CMD_SET_DHCP_AP_OFF_DEF "AT+CWDHCP_DEF=0,0\r\n"

#define ESP8266_CMD_SET_DHCP_STA_ON_DEF "AT+CWDHCP_DEF=1,1\r\n"
#define ESP8266_CMD_SET_DHCP_STA_OFF_DEF "AT+CWDHCP_DEF=1,0\r\n"

#define ESP8266_CMD_SET_DHCP_STA_AP_ON_DEF "AT+CWDHCP_DEF=2,1\r\n"
#define ESP8266_CMD_SET_DHCP_STA_AP_OFF_DEF "AT+CWDHCP_DEF=2,0\r\n"


#define ESP8266_CMD_GET_DHCP_IP_RANGE   "AT+CWDHCPS_CUR?\r\n"
#define ESP8266_CMD_SET_DHCP_IP_RANGE_LEASETIME_STARTIP_ENDIP(_TIME_, _START_, _END_)   "AT+CWDHCPS_CUR="STR(_TIME_)","STR(#_START_)","STR(#_END_)"\r\n"
#define ESP8266_CMD_SET_DHCP_IP_RANGE_ENABLE_LEASETIME_STARTIP_ENDIP(_TIME_, _START_, _END_)   "AT+CWDHCPS_CUR=1"","STR(_TIME_)","STR(#_START_)","STR(#_END_)"\r\n"
#define ESP8266_CMD_SET_DHCP_IP_RANGE_DISABLE   "AT+CWDHCPS_CUR=0\r\n"


#define ESP8266_CMD_GET_DHCP_IP_RANGE_DEF   "AT+CWDHCPS_DEF?\r\n"
#define ESP8266_CMD_SET_DHCP_IP_RANGE_LEASETIME_STARTIP_ENDIP_DEF(_TIME_, _START_, _END_)   "AT+CWDHCPS_DEF="STR(_TIME_)","STR(#_START_)","STR(#_END_)"\r\n"
#define ESP8266_CMD_SET_DHCP_IP_RANGE_ENABLE_LEASETIME_STARTIP_ENDIP_DEF(_TIME_, _START_, _END_)   "AT+CWDHCPS_DEF=1"","STR(_TIME_)","STR(#_START_)","STR(#_END_)"\r\n"
#define ESP8266_CMD_SET_DHCP_IP_RANGE_DISABLE_DEF   "AT+CWDHCPS_DEF=0\r\n"

/****************** Station Commands *************/

#define ESP8266_CMD_STA_AP_CURRENT "AP+CWJAP?\r\n"

#define ESP8266_CMD_STA_JOIN_AP(_NAME_, _PASS_) "AT+CWJAP_CUR="STR(#_NAME_)","STR(#_PASS_)"\r\n"
#define ESP8266_CMD_STA_JOIN_AP_BSSID(_NAME_, _PASS_, _BSSID_) "AT+CWJAP_CUR="STR(#_NAME_)","STR(#_PASS_)","STR(#_BSSID_)"\r\n"

#define ESP8266_CMD_STA_JOIN_AP_DEF(_NAME_, _PASS_) "AT+CWJAP_DEF="STR(#_NAME_)","STR(_PASS_)"\r\n"
#define ESP8266_CMD_STA_JOIN_AP_BSSID_DEF(_NAME_, _PASS_, _BSSID_) "AT+CWJAP_DEF="STR(#_NAME_)","STR(#_PASS_)","STR(#_BSSID_)"\r\n"


#define ESP8266_CMD_STA_GET_AP_ALL "AT+CWLAP/r/n"
#define ESP8266_CMD_STA_GET_AP_NAME(_NAME_) "AT+CWLAP="STR(#_NAME_)"\r\n"
#define ESP8266_CMD_STA_GET_AP_NAME_BSSID_CHANNEL(_NAME_, _MAC_, _CHANNEL_) "AT+CWLAP="STR(#_NAME_)","STR(#_MAC_)","#_CHANNEL_"\r\n"

#define ESP8266_CMD_STA_SET_AP_LIST_OPTIONS(_SORT_ENABLE_, _MASK_) "AT+CWLAPOPT="#_SORT_ENABLE_","#_MASK_"\r\n"

#define ESP8266_CMD_STA_QUIT_AP "AT+CWQAP\r\n"

#define ESP8266_CMD_STA_GET_AUTO_AP_CONN "AT+CWAUTOCONN?\r\n"
#define ESP8266_CMD_STA_SET_AUTO_AP_CONN_ON "AT+CWAUTOCONN=1\r\n"
#define ESP8266_CMD_STA_SET_AUTO_AP_CONN_OFF "AT+CWAUTOCONN=0\r\n"

#define ESP8266_CMD_STA_GET_MAC "AT+CIPSTAMAC_CUR?\r\n"
#define ESP8266_CMD_STA_SET_MAC(_MAC_) "AT+CIPSTAMAC_CUR="STR(#_MAC_)"\r\n"

#define ESP8266_CMD_STA_GET_MAC_DEF "AT+CIPSTAMAC_DEF?\r\n"
#define ESP8266_CMD_STA_SET_MAC_DEF(_MAC_) "AT+CIPSTAMAC_DEF="STR(#_MAC_)"\r\n"

#define ESP8266_CMD_STA_GET_IP  "AT+CIPSTA_CUR?\r\n"
#define ESP8266_CMD_STA_SET_IP(_IP_)  "AT+CIPSTA_CUR="STR(#_IP_)"\r\n"
#define ESP8266_CMD_STA_SET_IP_GATE_MASK(_IP_, _GATE_, _MASK_)  "AT+CIPSTA_CUR="STR(#_IP_)","STR(#_GATE_)","STR(#_MASK_)"\r\n"

#define ESP8266_CMD_STA_GET_IP_DEF  "AT+CIPSTA_DEF?\r\n"
#define ESP8266_CMD_STA_SET_IP_DEF(_IP_)  "AT+CIPSTA_DEF="STR(#_IP_)"\r\n"
#define ESP8266_CMD_STA_SET_IP_GATE_MASK_DEF(_IP_, _GATE_, _MASK_)  "AT+CIPSTA_DEF="STR(#_IP_)","STR(#_GATE_)","STR(#_MASK_)"\r\n"

#define ESP8266_CMD_STA_SET_SMART_CFG_ESP_TOUCH "AT+CWSTOPSMART=1\r\n"
#define ESP8266_CMD_STA_SET_SMART_CFG_AIR_KISS "AT+CWSTOPSMART=2\r\n"
#define ESP8266_CMD_STA_SET_SMART_CFG_ESP_TOUCH_AND_AIR_KISS "AT+CWSTOPSMART=3\r\n"
#define ESP8266_CMD_STA_SET_SMART_CFG_OFF "AT+CWSTOPSMART\r\n"


#define ESP8266_CMD_STA_SET_WECHAT_DISCOVERY_ON(_WECHAT_NUM_, _DEV_TYPE_, _TIME_) "AT+CWSTARTDISCOVER="STR(#_WECHAT_NUM_)","STR(#_DEV_TYPE_)","STR(_TIME)"\r\n"
#define ESP8266_CMD_STA_SET_WECHAT_DISCOVERY_OFF "AT+CWSTOPDISCOVER\r\n"

#define ESP8266_CMD_STA_SET_WPS_MODE_ON "AT+WPS=1\r\n"
#define ESP8266_CMD_STA_SET_WPS_MODE_OFF "AT+WPS=0\r\n"

#define ESP8266_CMD_STA_SET_MDNS(_ENABLE_, _HOST_, _SERVER_NAME_, _PORT_)  "AT+MDNS+="STR(_ENABLE_)","STR(#_HOST_)","STR(#_SERVER_NAME_)","STR(_PORT)"\r\n"

/******************* AP Mode Commands *****************/
#define ESP8266_CMD_AP_GET_AP_CFG  "AT+CWSAP_CUR?\r\n"
#define ESP8266_CMD_AP_SET_AP_CFG_SSID_PWD_CH_ENC(_SSID_, _PWD_, _CH_, _ENC_)  "AT+CWSAP_CUR="STR(#_SSID_)","STR(#_PWD_)","STR(_CH_)","STR(_ENC_)"\r\n"
#define ESP8266_CMD_AP_SET_AP_CFG_SSID_PWD_CH_ENC_MAXCONN_HIDDEN(_SSID_, _PWD_, _CH_, _ENC_, _CON_, _HID_)  "AT+CWSAP_CUR="STR(#_SSID_)","STR(#_PWD_)","STR(_CH_)","STR(_ENC_)","STR(_CON_)","STR(_HID_)"\r\n"

#define ESP8266_CMD_AP_GET_AP_CFG_DEF  "AT+CWSAP_DEF?\r\n"
#define ESP8266_CMD_AP_SET_AP_CFG_SSID_PWD_CH_ENC_DEF(_SSID_, _PWD_, _CH_, _ENC_)  "AT+CWSAP_DEF="STR(#_SSID_)","STR(#_PWD_)","STR(_CH_)","STR(_ENC_)"\r\n"
#define ESP8266_CMD_AP_SET_AP_CFG_SSID_PWD_CH_ENC_MAXCONN_HIDDEN_DEF(_SSID_, _PWD_, _CH_, _ENC_, _CON_, _HID_)  "AT+CWSAP_DEF="STR(#_SSID_)","STR(#_PWD_)","STR(_CH_)","STR(_ENC_)","STR(_CON_)","STR(_HID_)"\r\n"

#define ESP8266_CMD_AP_GET_ALL_CONNECTED    "AT+CWLIF\r\n"


#define ESP8266_CMD_AP_GET_MAC "AT+CIPAPMAC_CUR?\r\n"
#define ESP8266_CMD_AP_SET_MAC(_MAC_) "AT+CIPAPMAC_CUR="STR(#_MAC_)"\r\n"

#define ESP8266_CMD_AP_GET_MAC_AP_DEF "AT+CIPAPMAC_DEF?\r\n"
#define ESP8266_CMD_AP_SET_MAC_AP_DEF(_MAC_) "AT+CIPAPMAC_DEF="STR(#_MAC_)"\r\n"

#define ESP8266_CMD_AP_GET_IP "AT+CIPAP_CUR?\r\n"
#define ESP8266_CMD_AP_SET_IP(_IP_)  "AT+CIPAP_CUR="STR(#_IP_)"\r\n"
#define ESP8266_CMD_AP_SET_IP_GATE_MASK(_IP_, _GATE_, _MASK_)  "AT+CIPAP_CUR="STR(#_IP_)","STR(#_GATE_)","STR(#_MASK_)"\r\n"

#define ESP8266_CMD_AP_GET_IP_AP_DEF  "AT+CIPAP_DEF?\r\n"
#define ESP8266_CMD_AP_SET_IP_AP_DEF(_IP_)  "AT+CIPAP_DEF="STR(#_IP_)"\r\n"
#define ESP8266_CMD_AP_SET_IP_GATE_MASK_DEF(_IP_, _GATE_, _MASK_)  "AT+CIPAP_DEF="STR(#_IP_)","STR(#_GATE_)","STR(#_MASK_)"\r\n"



/**************** TCP/UDP/IP Commands ******************/


#define ESP8266_CMD_GET_CON_STATUS "AT+CIPSTATUS\r\n"

#define ESP8266_CMD_SET_DNS_DOMAIN(_DOM_) "AT+CIPDOMAIN="STR(#_DOM_)"\r\n"

#define ESP8266_CMD_START_TCP_SINGLE(_IP_, _PORT_) "AT+CIPSTART="STR("TCP")","STR(#_IP_)","STR(_PORT_)"\r\n"
#define ESP8266_CMD_START_TCP_SINGLE_KEEPALIVE(_IP_, _PORT_, _ALIVE_) "AT+CIPSTART="STR("TCP")","STR(#_IP_)","STR(_PORT_)","STR(_ALIVE_)"\r\n"

#define ESP8266_CMD_START_TCP_MULTI(_LINK_, _IP_, _PORT_) "AT+CIPSTART="STR(_LINK_)","STR("TCP")","STR(#_IP_)","STR(_PORT_)"\r\n"
#define ESP8266_CMD_START_TCP_MULTI_KEEPALIVE(_LINK_, _IP_, _PORT_, _ALIVE_) "AT+CIPSTART="STR(_LINK_)","STR("TCP")","STR(#_IP_)","STR(_PORT_)","STR(_ALIVE_)"\r\n"


#define ESP8266_CMD_START_UDP_SINGLE(_IP_, _PORT_) "AT+CIPSTART="STR("UDP")","STR(#_IP_)","STR(_PORT_)"\r\n"
#define ESP8266_CMD_START_UDP_SINGLE_LPORT_MODE(_IP_, _PORT_, _LPORT_, _MODE_) "AT+CIPSTART="STR("UDP")","STR(#_IP_)","STR(_PORT_)","STR(_LPORT_)","STR(_MODE_)"\r\n"

#define ESP8266_CMD_START_UDP_MULTI(_LINK_, _IP_, _PORT_) "AT+CIPSTART="STR(_LINK_)","STR("UDP")","STR(#_IP_)","STR(_PORT_)"\r\n"
#define ESP8266_CMD_START_UDP_MULTI_LPORT_MODE(_LINK_, _IP_, _PORT_, _LPORT_, _MODE_) "AT+CIPSTART="STR(_LINK_)","STR("UDP")","STR(#_IP_)","STR(_PORT_)","STR(_LPORT_)","STR(_MODE_)

#define ESP8266_CMD_START_SSL_SINGLE(_IP_, _PORT_) "AT+CIPSTART="STR("SSL")","STR(#_IP_)","STR(_PORT_)"\r\n"
#define ESP8266_CMD_START_SSL_SINGLE_KEEPALIVE(_IP_, _PORT_, _ALIVE_) "AT+CIPSTART="STR("SSL")","STR(#_IP_)","STR(_PORT_)","STR(_ALIVE_)"\r\n"

#define ESP8266_CMD_START_SSL_MULTI(_LINK_, _IP_, _PORT_) "AT+CIPSTART="STR(_LINK_)","STR("SSL")","STR(#_IP_)","STR(_PORT_)"\r\n"
#define ESP8266_CMD_START_SSL_MULTI_KEEPALIVE(_LINK_, _IP_, _PORT_, _ALIVE_) "AT+CIPSTART="STR(_LINK_)","STR("SSL")","STR(#_IP_)","STR(_PORT_)","STR(_ALIVE_)"\r\n"

#define ESP8266_CMD_SET_SSL_BUFSIZE(_SIZE_) "AT+CIPSSLSIZE="STR(_SIZE_)"\r\n"

#define ESP8266_SSL_BUFSIZE_MAX 4096
#define ESP8266_SSL_BUFSIZE_MIN 2048


#define ESP8266_CMD_OPEN_SEND_COMMAND "AT+CIPSEND\r\n"

#define ESP8266_CMD_SEND_TCP_SINGLE(_LENGTH_) "AT+CIPSEND="STR(_LENGTH_)"\r\n"
#define ESP8266_CMD_SEND_TCP_MULTI(_LINK_, _LENGTH_) "AT+CIPSEND="STR(_LINK_)","STR(_LENGTH_)"\r\n"
#define ESP8266_CMD_SEND_UDP(_LINK_, _LENGTH_, _IP_, _PORT_) "AT+CIPSEND="STR(_LINK_)","STR(_LENGTH_)","STR(#_IP_)","STR(_PORT_)"\r\n"
// TODO: AT+CIPSEND With No Params


#define ESP8266_CMD_SEND_STRING_TCP_SINGLE(_MAX_LENGTH_) "AT+CIPSENDEX="STR(_MAX_LENGTH_)"\r\n"
#define ESP8266_CMD_SEND_STRING_TCP_MULTI(_LINK_, _MAX_LENGTH_) "AT+CIPSENDEX="STR(_LINK_)","STR(_MAX_LENGTH_)"\r\n"
#define ESP8266_CMD_SEND_STRING_UDP(_LINK_, _MAX_LENGTH_, _IP_, _PORT_) "AT+CIPSENDEX="STR(_LINK_)","STR(_MAX_LENGTH_)","STR(#_IP_)","STR(_PORT_)"\r\n"


// TODO: AT+CIPSENDBUF
// TODO: AT+CIPBUFSTATUS
// TODO: AT+CIPCHECKSEQ
// TODO: AT+CIPBUFRESET

#define ESP8266_CMD_CLOSE_CON  "AT+CIPCLOSE\r\n"
#define ESP8266_CMD_CLOSE_CON_LINK(_LINK_)  "AT+CIPCLOSE="STR(_LINK_)"\r\n"

#define ESP8266_CMD_GET_MULTIPLE_CON_MODE "AT+CIPMUX?"
#define ESP8266_CMD_SET_MULTIPLE_CON_ON "AT+CIPMUX=1\r\n"
#define ESP8266_CMD_SET_MULTIPLE_CON_OFF "AT+CIPMUX=0\r\n"

#define ESP8266_CMD_SET_SERVER_ON "AT+CIPSERVER=1\r\n"
#define ESP8266_CMD_SET_SERVER_OFF "AT+CIPSERVER=0\r\n"

#define ESP8266_CMD_SET_SERVER_ON_PORT(_PORT_) "AT+CIPSERVER=1,"STR(_PORT_)"\r\n"
#define ESP8266_CMD_SET_SERVER_OFF_PORT(_PORT_) "AT+CIPSERVER=0,"STR(_PORT_)"\r\n"

#define ESP8266_CMD_GET_TRANSFER_MODE   "AT+CIPMODE?\r\n"
#define ESP8266_CMD_SET_TRANSFER_MODE_NORMAL   "AT+CIPMODE=0\r\n"
#define ESP8266_CMD_SET_TRANSFER_MODE_UART_WIFI_PASSTHROIGH   "AT+CIPMODE=1\r\n"

#define ESP8266_CMD_SAVE_TCP_TRANSPARENT_TRANS_LINK_NORMAL(_IP_, _PORT_) "AT+SAVETRANSLINK=0,"STR(#_IP_)","STR(_PORT_)","STR("TCP")"\r\n"
#define ESP8266_CMD_SAVE_TCP_TRANSPARENT_TRANS_LINK_UART_WIFI_PASSTHROUGH(_IP_, _PORT_) "AT+SAVETRANSLINK=1,"STR(#_IP_)","STR(_PORT_)","STR("TCP")"\r\n"

#define ESP8266_CMD_SAVE_TCP_TRANSPARENT_TRANS_LINK_NORMAL_KEEPALIVE(_IP_, _PORT_, _ALIVE_) "AT+SAVETRANSLINK=0,"STR(#_IP_)","STR(_PORT_)","STR("TCP")","STR(_ALIVE_)"\r\n"
#define ESP8266_CMD_SAVE_TCP_TRANSPARENT_TRANS_LINK_UART_WIFI_PASSTHROUGH_KEEPALIVE(_IP_, _PORT_, _ALIVE_) "AT+SAVETRANSLINK=1,"STR(#_IP_)","STR(_PORT_)","STR("TCP")","STR(_ALIVE_)"\r\n"

#define ESP8266_CMD_SAVE_UDP_TRANSPARENT_TRANS_LINK_NORMAL(_IP_, _PORT_) "AT+SAVETRANSLINK=0,"STR(#_IP_)","STR(_PORT_)","STR("UDP")"\r\n"
#define ESP8266_CMD_SAVE_UDP_TRANSPARENT_TRANS_LINK_UART_WIFI_PASSTHROUGH(_IP_, _PORT_) "AT+SAVETRANSLINK=1,"STR(#_IP_)","STR(_PORT_)","STR("UDP")"\r\n"


#define ESP8266_CMD_SAVE_UDP_TRANSPARENT_TRANS_LINK_NORMAL_LPORT(_IP_, _PORT_, _LPORT_) "AT+SAVETRANSLINK=0,"STR(#_IP_)","STR(_PORT_)","STR("UDP")","STR(_LPORT_)"\r\n"
#define ESP8266_CMD_SAVE_UDP_TRANSPARENT_TRANS_LINK_UART_WIFI_PASSTHROUGH_LPORT(_IP_, _PORT_, _LPORT_) "AT+SAVETRANSLINK=1,"STR(#_IP_)","STR(_PORT_)","STR("UDP")","STR(_LPORT_)"\r\n"


#define ESP8266_CMD_GET_SERVER_TIMEOUT  "AT+CIPSTO?\r\n"
#define ESP8266_CMD_SET_SERVER_TIMEOUT(_TIME_)  "AT+CIPSTO="STR(_TIME_)"\r\n"
#define ESP8266_CMD_SERVER_TIMEOUT_MAX  7200
#define ESP8266_CMD_SERVER_TIMEOUT_MIN  1
#define ESP8266_CMD_SERVER_TIMEOUT_INF  0

#define ESP8266_CMD_PING(_TARGET_) "AT+PING="STR(#_TARGET_)"\r\n"

#define ESP8266_CMD_UPDATE_THROUGH_NETWORK  "AT+CIUPDATE\r\n"

#define ESP8266_CMD_SHOW_REMOTE_IP_WITHOUT_PORT  "AT+CIPDINF=O\r\n"
#define ESP8266_CMD_SHOW_REMOTE_IP_WITH_PORT  "AT+CIPDINF=1\r\n"


/**************	Section: Macro Functions Declarations *******/



// TODO: Fix STR with multi params

#define ESP8266_CMD_SET_UART_CFG(baud, databits, stopbits, parity, flowcontrol)  "AT+UART_CUR="STR(baud)"," STR(databits)"," STR(stopbits)"," STR(parity)"," STR(flowcontrol)"\r\n"
#define ESP8266_CMD_SET_UART_CFG_DEF(baud, databits, stopbits, parity, flowcontrol)  "AT+UART_DEF="STR(baud)"," STR(databits)"," STR(stopbits)"," STR(parity)"," STR(flowcontrol)"\r\n"

#define ESP8266_UART_CFG_DATABITS_5 5
#define ESP8266_UART_CFG_DATABITS_6 6
#define ESP8266_UART_CFG_DATABITS_7 7
#define ESP8266_UART_CFG_DATABITS_8 8

#define ESP8266_UART_CFG_STOPBITS_1     1
#define ESP8266_UART_CFG_STOPBITS_1_5   1.5
#define ESP8266_UART_CFG_STOPBITS_2     2


#define ESP8266_UART_CFG_PARITY_NONE   0
#define ESP8266_UART_CFG_PARITY_ODD    1
#define ESP8266_UART_CFG_PARITY_EVEN   2


#define ESP8266_UART_CFG_FLOWCONTROL_DISABLE    0
#define ESP8266_UART_CFG_FLOWCONTROL_RTS        1
#define ESP8266_UART_CFG_FLOWCONTROL_CTS        2
#define ESP8266_UART_CFG_FLOWCONTROL_RTS_CTS    3


#define ESP8266_CMD_SET_RF_TXPOWER_MAX(_POWER_) "AT+RFPOWER="STR(_POWER_)"\r\n"
#define ESP8266_RF_TXPOWER_MAX 82
#define ESP8266_RF_TXPOWER_MIN 0

#define ESP8266_CMD_SET_RF_TXPOWER_VDD "AT+RFVDD\r\n"


/**************	Section: Data Types Declarations ************/

extern uint8_t ESP8266_TX_BUFF[];
extern uint8_t ESP8266_RX_BUFF[];

typedef enum {
    ESP8266_Return_UnValid = -2,
    ESP8266_Return_NotFound_OR_NotFinished = -1,
    ESP8266_Return_OK = 0,
    ESP8266_Return_ERROR = 1,
	ESP8266_Return_FAIL = 2,
    ESP8266_Return_ResetCompleted = 3,
    ESP8266_Return_TimeOut = 4,
    ESP8266_Return_ARG_ERROR = 99,
} ESP8266_ResponseType_t;

typedef enum {
    ESP8266_ProtocolType_TCP = 0,
    ESP8266_ProtocolType_UDP = 1,
    ESP8266_ProtocolType_SSL = 2
} ESP8266_ProtocolType_t;

typedef union {

    struct {
        uint16_t alive;
    } TCP;

    struct {
        uint16_t localPort;
        uint8_t localIP[16];
    } UDP;
    struct {
        uint16_t alive;
    } SSL;
} ESP8266_ProtocolOptions_t;

typedef enum {
    ESP8266_Wifi_WorkingMode_StationMode = 1,
    ESP8266_Wifi_WorkingMode_AccessPointMode = 2,
    ESP8266_Wifi_WorkingMode_StationAndAccessPointMode = (ESP8266_Wifi_WorkingMode_StationMode |
                                                          ESP8266_Wifi_WorkingMode_AccessPointMode),

} ESP8266_WiFi_WorkingMode_t;


typedef enum {
    ESP8266_DHCP_State_Disable = 0,
    ESP8266_DHCP_State_Enable = 1
} ESP8266_DHCP_State_t;

typedef enum {
    ESP8266_LinkNumber_Default = -1,
    ESP8266_LinkNumber_0 = 0,
    ESP8266_LinkNumber_1 = 1,
    ESP8266_LinkNumber_2 = 2,
    ESP8266_LinkNumber_3 = 3,
    ESP8266_LinkNumber_4 = 4,

} ESP8266_LinkNumber_t;
typedef enum {
    ESP8266_UART_WiFi_PassThroughMode_On ,
    ESP8266_UART_WiFi_PassThroughMode_Off
} ESP8266_UART_WiFi_PassThroughMode_t;
typedef enum {
    ESP8266_SelectedConfigs_None = 0,
    ESP8266_SelectedConfigs_BasicConfigs = 1,
    ESP8266_SelectedConfigs_UARTConfigs = 2,
    ESP8266_SelectedConfigs_WifiConfigs = 4,
    ESP8266_SelectedConfigs_ConnectionConfigs = 8
} ESP8266_SelectedConfigs_t;

typedef enum {
    ESP8266_SleepMode_Disable = 0,
    ESP8266_SleepMode_Light = 1,
    ESP8266_SleepMode_Modem = 2,
} ESP8266_SleepMode_t;
typedef enum {
    ESP8266_UART_dataBits_5 = 5,
    ESP8266_UART_dataBits_6 = 6,
    ESP8266_UART_dataBits_7 = 7,
    ESP8266_UART_dataBits_8 = 8,
} ESP8266_UART_dataBits_t;

typedef enum {
    ESP8266_UART_parityBits_None = 0,
    ESP8266_UART_parityBits_ODD = 1,
    ESP8266_UART_parityBits_EVEN = 2
} ESP8266_UART_parityBits_t;
typedef enum {
    ESP8266_UART_stopBits_1 = 1,
    ESP8266_UART_stopBits_1_5 = 2,
    ESP8266_UART_stopBits_2 = 3,
} ESP8266_UART_stopBits_t;

typedef enum {
    ESP8266_UART_flowControl_Disable = 0,
    ESP8266_UART_flowControl_RTS = 1,
    ESP8266_UART_flowControl_CTS = 2,
    ESP8266_UART_flowControl_RTS_CTS = 3,
} ESP8266_UART_flowControl_t;


typedef enum {
    ESP8266_ServerState_OFF = 0,
    ESP8266_ServerState_ON = 1,
} ESP8266_ServerState_t;


typedef enum {
    ESP8266_EchoMode_Disable = 0,
    ESP8266_EchoMode_Enable = 1,
} ESP8266_EchoMode_t;

typedef struct {
//        uint32_t POWER;
    ESP8266_SleepMode_t sleepMode;
    ESP8266_EchoMode_t echoMode;
} ESP8266_BasicConfig_t;

typedef enum {
    ESP8266_UART_BaudRate_MIN = 110,
    ESP8266_UART_BaudRate_MAX = 115200 * 40, // 4608000
} ESP8266_UART_BaudRate_t;

typedef struct {
    ESP8266_UART_BaudRate_t newBaudRate;
    ESP8266_UART_dataBits_t dataBits;
    ESP8266_UART_parityBits_t parityBits;
    ESP8266_UART_stopBits_t stopBits;
    ESP8266_UART_flowControl_t flowControl;

} ESP8266_UART_Config_t;



typedef struct {

    ESP8266_WiFi_WorkingMode_t workingMode;

} ESP8266_WiFi_Config_t;


typedef enum {
    ESP8266_Connection_Multi_Disable = 0,
    ESP8266_Connection_Multi_Enable = 1,
} ESP8266_Connection_Multi_t;

typedef struct {
    ESP8266_Connection_Multi_t multiConnection;
} ESP8266_Connection_Config_t;


typedef struct {

    USART_Number_t usartNumber;
    struct {
        uint8_t enableHardReset;
        GPIO_PORT_ID_t port;
        GPIO_Pin_ID_t pin;
    }resetPinConfig;
    ESP8266_SelectedConfigs_t selectedConfigs;
    ESP8266_BasicConfig_t basicConfig;
    ESP8266_UART_Config_t uartConfig;
    ESP8266_WiFi_Config_t wifiConfig;
    ESP8266_Connection_Config_t connectionConfig;

} ESP8266_Config_t;


typedef struct {
    uint8_t IPAddress[16];
    uint8_t MACAddress[18];
} ESP8266_IdentityUnit_t;

typedef enum {
    ESP8266_EncryptionType_Open = 0,
//    ESP8266_EncryptionType_WEP = 1, // Removed Because it gives an error
    ESP8266_EncryptionType_WPA_PSK = 2,
    ESP8266_EncryptionType_WPA2_PSK = 3,
    ESP8266_EncryptionType_WPA_WPA2_PSK = 4,
} ESP8266_EncryptionType_t;

typedef enum {
    ESP8266_ChannelNumber_1 = 1,
    ESP8266_ChannelNumber_2 = 2,
    ESP8266_ChannelNumber_3 = 3,
    ESP8266_ChannelNumber_4 = 4,
    ESP8266_ChannelNumber_5 = 5,
    ESP8266_ChannelNumber_6 = 6,
    ESP8266_ChannelNumber_7 = 7,
    ESP8266_ChannelNumber_8 = 8,
} ESP8266_ChannelNumber_t;

typedef enum {
    ESP8266_MaxConnection_1 = 1,
    ESP8266_MaxConnection_2 = 2,
    ESP8266_MaxConnection_3 = 3,
    ESP8266_MaxConnection_4 = 4,
} ESP8266_MaxConnection_t;

typedef enum {
    ESP8266_HiddenState_UnHidden = 0,
    ESP8266_HiddenState_Hidden = 1,
} ESP8266_HiddenState_t;
typedef struct {
    ESP8266_EncryptionType_t encryptionType;
    uint8_t SSID[16 + 1];
    sint16_t signalStrength;
    uint8_t MACAddress[18];
    ESP8266_ChannelNumber_t channel;
    sint16_t frequencyOffset;
    sint16_t frequencyCalibration;
} ESP8266_AccessPoint_t;

typedef ESP8266_IdentityUnit_t ESP8266_ConnectedDevice_t;

/**************	Section: Methods Declarations  **************/

ESP8266_ResponseType_t HAL_ESP8266_resetHard(ESP8266_Config_t *restrict esp);

ESP8266_ResponseType_t HAL_ESP8266_GPIOInit(ESP8266_Config_t *restrict esp);

ESP8266_ResponseType_t HAL_ESP8266_test(ESP8266_Config_t *restrict esp);

ESP8266_ResponseType_t HAL_ESP8266_setEchoMode(ESP8266_Config_t *restrict config, ESP8266_EchoMode_t mode);

ESP8266_ResponseType_t HAL_ESP8266_setSleepMode(ESP8266_Config_t *restrict config, ESP8266_SleepMode_t sleepMode);

ESP8266_ResponseType_t HAL_ESP8266_send(ESP8266_Config_t *restrict esp, uint8_t *restrict data, uint32_t size);

ESP8266_ResponseType_t HAL_ESP8266_sendString(ESP8266_Config_t *restrict esp, uint8_t *restrict data, uint32_t maxSize);

ESP8266_ResponseType_t
HAL_ESP8266_joinAccessPoint(ESP8266_Config_t *restrict esp, int8_t *restrict name, int8_t *restrict pass);

ESP8266_ResponseType_t
HAL_ESP8266_joinAccessPoint_BSSID(ESP8266_Config_t *restrict esp, uint8_t *restrict name, uint8_t *restrict pass,
                                  uint8_t *restrict bssid);

ESP8266_ResponseType_t
HAL_ESP8266_sendUARTConfig(ESP8266_Config_t *restrict esp, ESP8266_UART_Config_t *restrict config);


ESP8266_ResponseType_t
HAL_ESP8266_WaitForResponse(ESP8266_Config_t *restrict esp, sint32_t *restrict count,
                            ESP8266_ResponseType_t *espRespType);


ESP8266_ResponseType_t
HAL_ESP8266_setIP_Gateway_Mask(ESP8266_Config_t *restrict esp, ESP8266_WiFi_WorkingMode_t targetMode,
                               const uint8_t *restrict ip,
                               const uint8_t *restrict gateway, const uint8_t *restrict mask);


ESP8266_ResponseType_t HAL_ESP8266_Init(ESP8266_Config_t *restrict esp);

ESP8266_ResponseType_t HAL_ESP8266_disconnectAccessPoint(ESP8266_Config_t *restrict esp);

ESP8266_ResponseType_t
HAL_ESP8266_listAvailableAccessPoints(ESP8266_Config_t *restrict esp, ESP8266_AccessPoint_t *restrict accessPoints,
                                      uint32_t *restrict count,
                                      uint32_t maxCount);

ESP8266_ResponseType_t
HAL_ESP8266_setMACAddress(ESP8266_Config_t *restrict esp, ESP8266_WiFi_WorkingMode_t targetMode,
                          const uint8_t *restrict mac);


ESP8266_ResponseType_t
HAL_ESP8266_setIPAddress(ESP8266_Config_t *restrict esp, ESP8266_WiFi_WorkingMode_t targetMode, const uint8_t *restrict ip);

ESP8266_ResponseType_t
HAL_ESP8266_getIP_MAC(ESP8266_Config_t *restrict esp, uint8_t *restrict stationIP, uint8_t *restrict stationMAC,
                      uint8_t *restrict APIP, uint8_t *restrict APMAC);

ESP8266_ResponseType_t
HAL_ESP8266_getAPConnectedDevices(ESP8266_Config_t *restrict esp, ESP8266_ConnectedDevice_t *restrict connectedDevices,
                                  uint32_t *restrict count, uint32_t max);

ESP8266_ResponseType_t
HAL_ESP8266_configDHCP(ESP8266_Config_t *restrict esp, ESP8266_WiFi_WorkingMode_t targetMode, ESP8266_DHCP_State_t dhcpState,
                       uint8_t *restrict startIP, uint8_t *restrict endIP);


ESP8266_ResponseType_t
HAL_ESP8266_connStart(ESP8266_Config_t *restrict esp, ESP8266_LinkNumber_t linkNumber,
                      ESP8266_ProtocolType_t protocolType,
                      int8_t *restrict ip, uint16_t port, ESP8266_ProtocolOptions_t *restrict options);

ESP8266_ResponseType_t HAL_ESP8266_connClose(ESP8266_Config_t *restrict esp, ESP8266_LinkNumber_t linkNumber);


ESP8266_ResponseType_t
HAL_ESP8266_connSendBytes(ESP8266_Config_t *restrict esp, ESP8266_LinkNumber_t linkNumber, uint8_t *restrict data,
                          uint32_t size, ESP8266_UART_WiFi_PassThroughMode_t mode);

ESP8266_ResponseType_t
HAL_ESP8266_connSendString(ESP8266_Config_t *restrict esp, ESP8266_LinkNumber_t linkNumber, int8_t *restrict data,
                           sint32_t maxSize);


ESP8266_ResponseType_t HAL_ESP8266_closeServer(ESP8266_Config_t *restrict esp);


ESP8266_ResponseType_t
HAL_ESP8266_setMultiConnectionMode(ESP8266_Config_t *restrict esp, ESP8266_Connection_Multi_t mode);

ESP8266_ResponseType_t HAL_ESP8266_startServer(ESP8266_Config_t *restrict esp, uint16_t port);

ESP8266_ResponseType_t HAL_ESP8266_enableUART_WIFI_PASSThroughMode(ESP8266_Config_t *esp);


ESP8266_ResponseType_t
HAL_ESP8266_startUART_WIFI_PassThroughConnection(ESP8266_Config_t *restrict esp, ESP8266_ProtocolType_t protocolType,
                                                 int8_t *restrict ip, uint16_t port,
                                                 ESP8266_ProtocolOptions_t *restrict options);

ESP8266_ResponseType_t HAL_ESP8266_closeUART_WIFI_PassThroughConnection(ESP8266_Config_t *restrict esp);

ESP8266_ResponseType_t
HAL_ESP8266_configAP(ESP8266_Config_t *esp, int8_t *name, int8_t *pass, ESP8266_ChannelNumber_t channelNumber,
                     ESP8266_EncryptionType_t encryptionType);

ESP8266_ResponseType_t
HAL_ESP8266_configAP_Full(ESP8266_Config_t *esp, int8_t *name, int8_t *pass, ESP8266_ChannelNumber_t channelNumber,
                          ESP8266_EncryptionType_t encryptionType, ESP8266_MaxConnection_t maxConnection,
                          ESP8266_HiddenState_t hiddenState);


ESP8266_ResponseType_t HAL_ESP8266_setWiFiWorkingMode(ESP8266_Config_t *esp, ESP8266_WiFi_WorkingMode_t mode);


ESP8266_ResponseType_t HAL_ESP8266_reset(ESP8266_Config_t *restrict esp);


ESP8266_ResponseType_t HAL_ESP8266_ReceiveByte(ESP8266_Config_t *restrict esp, uint8_t *data, uint32_t timeOut);
ESP8266_ResponseType_t HAL_ESP8266_ReceiveBytes(ESP8266_Config_t *restrict esp, uint8_t *data, uint32_t size, uint32_t timeOut);


#endif //STM32_DRIVERS_ESP8266_H
