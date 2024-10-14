


/**************	Section: Includes *********************************/
#include "usart.h"

/**************	Section: Local Variables Declarations *************/


/**************	Section: Local Methods Prototype Declarations *****/

void sendData(USART_Number_t usartNumber, uint32_t data, uint32_t MAX_TIME_OUT);

uint32_t receiveData(USART_Number_t usartNumber, uint32_t *timeout);

uint32_t receiveData_Block(USART_Number_t usartNumber);

uint32_t __HAL_USART_BaudRateCalculation(const USART_Number_t usartNumber, const uint32_t baudRate);

/**************	Section: Methods Declarations *********************/


Std_ReturnType HAL_USART_GPIOInit(const USART_Number_t usartNumber, const USART_Config_t *config) {

    Std_ReturnType ret = E_OK;

    if ((usartNumber > USART_Number_3) || (config == NULL)) {
        ret = E_NOT_OK;
    } else {

        GPIO_Pin_Config_t output = {0};
        output.mode = Pin_Mode_Output_10MHZ;
        output.config = Pin_Mode_Config_Output_PUSH_PULL_ALTERNATE_FUNCTION;

        GPIO_Pin_Config_t input = {0};
        input.mode = Pin_Mode_Input;
        input.config = Pin_Mode_Config_INPUT_FLOATING;

        GPIO_PORT_ID_t portId;
        uint16_t txPinId;
        uint16_t rxPinId;
        uint16_t ckPinId;
        uint16_t ctsPinId;
        uint16_t rtsPinId;
        switch (usartNumber) {


            case USART_Number_1:
                portId = PORT_ID_PORTA;
                txPinId = PIN_9;
                rxPinId = PIN_10;
                break;
            case USART_Number_2:
                txPinId = PIN_2;
                rxPinId = PIN_3;
                portId = PORT_ID_PORTA;
                break;
            case USART_Number_3:
                txPinId = PIN_10;
                rxPinId = PIN_11;
                portId = PORT_ID_PORTB;
                break;
        }

        switch (config->mode) {

            case USART_Mode_Async:
            case USART_Mode_Sync:
                if ((config->BasicConfig.dataDirectionMode & USART_Mode_ReceiverMode) > 0) {
                    HAL_GPIO_ConfigPins(portId, rxPinId, &input);
                }

                if ((config->BasicConfig.dataDirectionMode & USART_Mode_TransmitterMode) > 0) {
                    HAL_GPIO_ConfigPins(portId, txPinId, &output);
                }

                break;
            case USART_Mode_HalfDuplex:
                // TODO
                break;
            default:
                ret = E_NOT_OK;
        }
    }
    return ret;
}



Std_ReturnType
HAL_USART_ChangeBaudRate(const USART_Number_t usartNumber, USART_Config_t *config, const uint32_t baudRate) {
    Std_ReturnType ret = E_OK;

    if ((uint32_t) usartNumber > USART_Number_3) {
        ret = E_NOT_OK;
    } else {
        if (config != NULL) {
            config->BaudRate = baudRate;
        }
        USARTs[usartNumber]->BRR.REG = __HAL_USART_BaudRateCalculation(usartNumber, baudRate);
    }
    return ret;
}

Std_ReturnType HAL_USART_Init(const USART_Number_t usartNumber, const USART_Config_t *config) {
    Std_ReturnType ret = E_OK;

    if (((uint32_t) usartNumber > USART_Number_3) || (config == NULL)) {
        ret = E_NOT_OK;
    } else {
        USARTs[usartNumber]->CR1.UE = STD_OFF;

        USARTs[usartNumber]->CR1.REG = CONVERT_TYPE_INDX(uint32_t, config->BasicConfig, 0);
        USARTs[usartNumber]->CR2.REG = CONVERT_TYPE_INDX(uint32_t, config->BasicConfig, 1);
        USARTs[usartNumber]->CR3.REG = CONVERT_TYPE_INDX(uint32_t, config->BasicConfig, 2);
        USARTs[usartNumber]->BRR.REG = __HAL_USART_BaudRateCalculation(usartNumber, config->BaudRate);

        if (config->mode == USART_Mode_HalfDuplex) {
            USARTs[usartNumber]->CR3.HDSEL = pUSART_HDSEL_HALF_DUPLEX_SELECTED;
//            USARTs[usartNumber]->CR1.TE = USART_TE_TX_ENABLE;
//            USARTs[usartNumber]->CR1.RE = STD_OFF;
        }

        USARTs[usartNumber]->CR1.UE = STD_ON;

    }
    return ret;
}

Std_ReturnType HAL_USART_SendByte(const USART_Number_t usartNumber, const uint32_t data) {
    Std_ReturnType ret = E_OK;

    if ((uint32_t) usartNumber > USART_Number_3) {
        ret = E_NOT_OK;
    } else {
        USARTs[usartNumber]->SR.TC = 0;
        sendData(usartNumber, data, TIMEOUT_INF);


    }
    return ret;
}


Std_ReturnType HAL_USART_SendBytes(const USART_Number_t usartNumber, const uint8_t *data, uint16_t size) {
    Std_ReturnType ret = E_OK;
    if (((uint32_t) usartNumber > USART_Number_3) || (data == NULL) || (size <= 0)) {
        ret = E_NOT_OK;
    } else {
        USARTs[usartNumber]->SR.TC = 0;
        while (size-- > 0) {
            sendData(usartNumber, (uint32_t) (*(data++)), USART_CFG_MAX_TIMEOUT);
        }

    }
    return ret;
}


Std_ReturnType HAL_USART_SendString(const USART_Number_t usartNumber, const uint8_t *str, uint32_t maxSize) {

    Std_ReturnType ret = E_OK;
    if (((uint32_t) usartNumber > USART_Number_3) || (str == NULL)) {
        ret = E_NOT_OK;
    } else {
        USARTs[usartNumber]->SR.TC = 0;
        // TODO: Fix that it always sends \0
        do {
            sendData(usartNumber, *str, USART_CFG_MAX_TIMEOUT);
        } while ((*str++ != 0) && (maxSize-- != 0));


    }
    return ret;
}


Std_ReturnType HAL_USART_ReceiveByte(const USART_Number_t usartNumber, uint8_t *data, uint32_t timeOut) {
    Std_ReturnType ret = E_OK;
    if (((uint32_t) usartNumber > USART_Number_3) || (data == NULL)) {
        ret = E_NOT_OK;
    } else {
        *data = (uint8_t) receiveData(usartNumber, &timeOut);
    }
    return ret;
}

Std_ReturnType HAL_USART_waitForChar(const USART_Number_t usartNumber, uint8_t waitChar, uint32_t timeOut) {
    Std_ReturnType ret = E_OK;
    if (((uint32_t) usartNumber > USART_Number_3)) {
        ret = E_NOT_OK;
    } else {
        WAIT_CONDITION_OR_TIMEOUT_M(waitChar == receiveData(usartNumber, &timeOut), timeOut);

    }
    return ret;
}

Std_ReturnType
HAL_USART_ReceiveBytes(const USART_Number_t usartNumber, uint8_t *data, uint16_t size, uint32_t timeOut) {
    Std_ReturnType ret = E_OK;
    if (((uint32_t) usartNumber > USART_Number_3) || (data == NULL) || (size <= 0)) {
        ret = E_NOT_OK;
    } else {

        while ((size-- > 0) && (timeOut > 0)) {
            *data++ = (uint8_t) receiveData(usartNumber, &timeOut);
        }
        if (0 == timeOut) {
            ret = E_TIMEOUT;
        }
    }
    return ret;
}

Std_ReturnType
HAL_USART_ReceiveString(const USART_Number_t usartNumber, uint8_t *data, uint16_t maxSize, uint32_t timeOut) {
    Std_ReturnType ret = E_OK;
    if (((uint32_t) usartNumber > USART_Number_3) || (data == NULL)) {
        ret = E_NOT_OK;
    } else {
        while ((maxSize-- > 0) && (timeOut > 0)) {
            *data = (uint8_t) receiveData(usartNumber, &timeOut);
            if (*data++ == 0) {
                break;
            }
        }
    }
    return ret;
}


Std_ReturnType HAL_USART_ReceiveUntilPattern(const USART_Number_t usartNumber,
                                             uint8_t *restrict data, sint32_t *foundPattern,
                                             sint32_t *restrict const count, uint32_t maxSize,
                                             const PatternManager_t *restrict patternManager,
                                             uint32_t IGNORE_FLAGS_START) {

    Std_ReturnType ret = E_OK;

    if ((usartNumber > USART_Number_3) || (data == NULL) || (patternManager == NULL) || (count == NULL)) {
        ret = E_NOT_OK;
    } else {


        sint32_t timeout = 100;//100*USARTs[usartNumber]->BRR.REG;
        // Create PatternCounter
        uint32_t *patternCounter = (uint32_t *) calloc(patternManager->count, sizeof(uint32_t));
        *count = 0;
        *foundPattern = -1;
        uint8_t foundFlag = STD_LOW;

        while ((maxSize--) && (!foundFlag) && (timeout)) {

//            *data = *rxData;
            *data = (uint8_t) receiveData(usartNumber, &timeout);//, &timeout);
            (*count)++;
            for (sint32_t patternIndex = 0; patternIndex < patternManager->count; patternIndex++) {
                if (*data == patternManager->patterns[patternIndex].pattern[patternCounter[patternIndex]]) {
                    patternCounter[patternIndex]++;
                    if (patternCounter[patternIndex] == patternManager->patterns[patternIndex].size) {
                        if (patternIndex >= IGNORE_FLAGS_START) {
                            patternCounter[patternIndex] = 0;
                            data -= patternManager->patterns[patternIndex].size;
                        } else {

                            foundFlag = STD_HIGH;
                            *foundPattern = patternIndex;
                            break;
                        }
                    }
                } else {
                    patternCounter[patternIndex] = 0;
                }
            }
            data++;
        }
        if (foundFlag == STD_LOW) {
            *count = -1;
        }
        if (timeout == 0) {
            ret = E_NOT_OK;
        }
        free(patternCounter);
    }
    return ret;


}

InterruptCallback_t interruptCallbacks[3] = {0};

Std_ReturnType HAL_USART_RegisterInterruptCallback(const USART_Number_t usartNumber, InterruptCallback_t callback) {
    Std_ReturnType ret = E_OK;
    if ((uint32_t) usartNumber > USART_Number_3) {
        ret = E_NOT_OK;
    } else {
        interruptCallbacks[usartNumber] = callback;
    }
    return ret;
}


Std_ReturnType HAL_USART_SendBreakFrame(const USART_Number_t usartNumber) {
    Std_ReturnType ret = E_OK;
    if ((uint32_t) usartNumber > USART_Number_3) {
        ret = E_NOT_OK;
    } else {
        USARTs[usartNumber]->CR1.SBK = STD_ON;
    }
    return ret;
}


/**************	Section: Helper Methods Declarations  *************/
uint32_t inline __HAL_USART_BaudRateCalculation(const USART_Number_t usartNumber, const uint32_t baudRate) {
    uint32_t ret = 0;
    switch (usartNumber) {


        case USART_Number_1:
            ret = (uint32_t) System_PeripheralsClock.USART1 / (baudRate / 10);
            break;
        case USART_Number_2:
            ret = (uint32_t) System_PeripheralsClock.USART2 / (baudRate/10);
            break;
        case USART_Number_3:
            ret = (uint32_t) System_PeripheralsClock.USART3 / (baudRate/10);
            break;
    }

    if ((ret / 10) * 10 -ret >= 5){
    	ret +=10;
    }
    ret/=10;


    return ret;
}

void sendData(USART_Number_t usartNumber, uint32_t data, uint32_t MAX_TIME_OUT) {

    USARTs[usartNumber]->DR.DR = data;
    WAIT_CONDITION_OR_TIMEOUT(USARTs[usartNumber]->SR.TXE == STD_ON, MAX_TIME_OUT);
}

uint32_t receiveData(USART_Number_t usartNumber, uint32_t *timeout) {
    WAIT_CONDITION_OR_TIMEOUT_M(USARTs[usartNumber]->SR.RXNE == STD_ON, *timeout);
    return USARTs[usartNumber]->DR.REG;
}


uint32_t receiveData_Block(USART_Number_t usartNumber) {
    WAIT_CONDITION_OR_TIMEOUT(USARTs[usartNumber]->SR.RXNE == STD_ON, TIMEOUT_INF);
    return USARTs[usartNumber]->DR.REG;
}

void USART1_IRQHandler(void) {

    if (interruptCallbacks[USART_Number_1] != NULL) {
        interruptCallbacks[USART_Number_1](INTERRUPTS_NO_PARAMS);
    }
}


void USART2_IRQHandler(void) {

    if (interruptCallbacks[USART_Number_2] != NULL) {
        interruptCallbacks[USART_Number_2](INTERRUPTS_NO_PARAMS);
    }
}


void USART3_IRQHandler(void) {

    if (interruptCallbacks[USART_Number_3] != NULL) {
        interruptCallbacks[USART_Number_3](INTERRUPTS_NO_PARAMS);
    }
}
