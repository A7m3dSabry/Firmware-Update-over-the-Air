

/**************	Section: Includes *********************************/

#include "i2c.h"
#include "rcc.h"

/**************	Section: Local Variables Declarations *************/
/**************	Section: Local Methods Prototype Declarations *****/

static Std_ReturnType send(I2C_Number_t i2cNumber, uint8_t data, sint32_t timeOut);

static Std_ReturnType receive(I2C_Number_t i2cNumber, uint8_t *data, uint16_t timeOut);

/**************	Section: Methods Declarations *********************/



Std_ReturnType HAL_I2C_Init(const I2C_Number_t i2cNumber, const I2C_Config_t *config) {
    Std_ReturnType ret = E_OK;

    if (((uint32_t) i2cNumber > I2C_Number2) || (config == NULL)) {
        ret = E_NOT_OK;
    } else {

        pI2C->All.I2Cs[i2cNumber].I2C.OAR1.REG = CONVERT_TYPE_INDX(uint32_t, config->AddressOptions, 0) | (1 << 14);
        pI2C->All.I2Cs[i2cNumber].I2C.OAR2.REG = CONVERT_TYPE_INDX(uint32_t, config->AddressOptions, 1);

        pI2C->All.I2Cs[i2cNumber].I2C.CCR.REG = CONVERT_TYPE_INDX(uint32_t, config->ClockOptions, 2);


        /* Configuring Required Clock */
        const uint32_t requiredClock = (config->BasicOptions.masterSpeedMode == I2C_MasterSpeedMode_FastMode_400KHz)
                                       ? 400000
                                       : 100000;


        uint8_t constants = (config->ClockOptions.clockDuty == I2C_ClockDuty_50Percent) ? 2 : 25;
        pI2C->All.I2Cs[i2cNumber].I2C.CCR.CCR = System_PeripheralsClock.I2C / (requiredClock * constants);

        uint32_t actualClock = System_PeripheralsClock.I2C / (pI2C->All.I2Cs[i2cNumber].I2C.CCR.CCR * constants);
        if (actualClock > requiredClock) {
            pI2C->All.I2Cs[i2cNumber].I2C.CCR.CCR += 1;
            actualClock = System_PeripheralsClock.I2C / (pI2C->All.I2Cs[i2cNumber].I2C.CCR.CCR * constants);
        }

        /* Configuring Rise Time */


        uint8_t maxRiseTime = (config->BasicOptions.masterSpeedMode == I2C_MasterSpeedMode_StandardMode_100KHz) ? 3
                                                                                                                : 10; // *e-7
        pI2C->All.I2Cs[i2cNumber].I2C.TRISE.TRISE =
                ((maxRiseTime * System_PeripheralsClock.I2C) / 10000000) + 1; // Truncation error may occur ??
        uint8_t actualRiseTime =
                (pI2C->All.I2Cs[i2cNumber].I2C.TRISE.TRISE - 1) * 10000000 / System_PeripheralsClock.I2C;
        if (actualRiseTime > maxRiseTime) {
            pI2C->All.I2Cs[i2cNumber].I2C.TRISE.TRISE -= 1;
        }

        pI2C->All.I2Cs[i2cNumber].I2C.CR2.REG = CONVERT_TYPE_INDX(uint32_t, config->BasicOptions, 1);
        pI2C->All.I2Cs[i2cNumber].I2C.CR2.FREQ = System_PeripheralsClock.I2C / 1000000;


        pI2C->All.I2Cs[i2cNumber].I2C.CR1.REG = CONVERT_TYPE_INDX(uint32_t, config->BasicOptions, 0);

    }
    return ret;
}

Std_ReturnType HAL_I2C_ChangePeripheralState(const I2C_Number_t i2cNumber, const I2C_RunningState_t state) {
    Std_ReturnType ret = E_OK;

    if (((uint32_t) i2cNumber > I2C_Number2) || ((uint32_t) state > I2C_RunningState_Running)) {
        ret = E_NOT_OK;
    } else {
        pI2C->All.I2Cs[i2cNumber].I2C.CR1.PE = state;
    }
    return ret;
}

Std_ReturnType HAL_I2C_InitGPIO(const I2C_Number_t i2cNumber) {
    Std_ReturnType ret = E_OK;

    if ((uint32_t) i2cNumber > I2C_Number2) {
        ret = E_NOT_OK;
    } else {

        uint16_t sdaPin = 0;
        uint16_t sclPin = 0;
        GPIO_PORT_ID_t port = PORT_ID_PORTB;

        switch (i2cNumber) {

            case I2C_Number1:

                // TODO: i2c Consider Mapping
                sdaPin = PIN_7;
                sclPin = PIN_6;
                break;
            case I2C_Number2:
                sdaPin = PIN_11;
                sclPin = PIN_10;
                break;
        }


        HAL_GPIO_ConfigPinsDirect(port, sdaPin | sclPin, Pin_Mode_Output_2MHZ,
                                  Pin_Mode_Config_Output_OPEN_DRAIN_ALTERNATE_FUNCTION);
    }
    return ret;
}

//Std_ReturnType HAL_I2C_AcquireBus(const I2C_Number_t i2cNumber);

Std_ReturnType HAL_I2C_SendStart(const I2C_Number_t i2cNumber, sint32_t timeOut) {
    Std_ReturnType ret = E_OK;

    if ((uint32_t) i2cNumber > I2C_Number2) {
        ret = E_NOT_OK;
    } else {
        /* Send Start Condition */

        WAIT_CONDITION_OR_TIMEOUT_M(I2C_CheckIsBusNotBusy(i2cNumber), timeOut)



        if (timeOut == 0) {
            pI2C->All.I2Cs[i2cNumber].I2C.CR1.START = pI2C_START_NOTHING;
            ret = E_NOT_OK;
        } else {
            pI2C->All.I2Cs[i2cNumber].I2C.CR1.START = pI2C_START_SEND_START;
        }

        // TODO: Define the timout to indicate failure in sending start condition
        /* Checking if Start Condition was Sent */
        WAIT_CONDITION_OR_TIMEOUT_M(I2C_CheckIsStartSent(i2cNumber) || (ret == E_NOT_OK), timeOut);


        (void) pI2C->All.I2Cs[i2cNumber].I2C.SR1.REG;
        (void) pI2C->All.I2Cs[i2cNumber].I2C.SR2.REG;
    }


    return ret;
}

Std_ReturnType HAL_I2C_SendStop(const I2C_Number_t i2cNumber) {
    Std_ReturnType ret = E_OK;

    if ((uint32_t) i2cNumber > I2C_Number2) {
        ret = E_NOT_OK;
    } else {
        pI2C->All.I2Cs[i2cNumber].I2C.CR1.STOP = pI2C_STOP_SEND_STOP;
    }
    return ret;
}

Std_ReturnType HAL_I2C_ChangeAcknowledgementState(const I2C_Number_t i2cNumber, I2C_ACKState_t state) {

    Std_ReturnType ret = E_OK;

    if (((uint32_t) i2cNumber > I2C_Number2) || ((uint32_t) state > I2C_ACKState_ACK)) {
        ret = E_NOT_OK;
    } else {
        pI2C->All.I2Cs[i2cNumber].I2C.CR1.ACK = state;
    }
    return ret;

}

Std_ReturnType HAL_I2C_ChangeAddressingMode(const I2C_Number_t i2cNumber, I2C_AddressingMode_t mode) {
    Std_ReturnType ret = E_OK;

    if (((uint32_t) i2cNumber > I2C_Number2) || ((uint32_t) mode > I2C_AddressingMode_10Bit)) {
        ret = E_NOT_OK;
    } else {
        pI2C->All.I2Cs[i2cNumber].I2C.OAR1.ADDMODE = mode;
    }
    return ret;
}

Std_ReturnType
HAL_I2C_SelectAddress(const I2C_Number_t i2cNumber, const uint16_t adrs, const I2C_ReadWriteMode_t mode,
                      sint32_t timeOut) {
    Std_ReturnType ret = E_OK;

    if (((uint32_t) i2cNumber > I2C_Number2) || ((adrs & ~0x3FF) != 0) ||
        ((uint32_t) mode > I2C_ReadWriteMode_Read)) {
        ret = E_NOT_OK;
    } else {

        if ((adrs & ~0x7F) == 0) {
            /* 7bit addressing mode*/

            /* Transmitting Byte */

            I2C_Data(i2cNumber) = (uint8_t) (adrs << 1 | mode);
            WAIT_CONDITION_OR_TIMEOUT_M(
                    (I2C_CheckAddressMatched(i2cNumber) || I2C_CheckAckFailure(i2cNumber)), timeOut);

            if ((timeOut == 0) || I2C_CheckAckFailure(i2cNumber)) {
                ret = E_NOT_OK;
            }
            (void) pI2C->All.I2Cs[i2cNumber].I2C.SR1.REG;
            (void) pI2C->All.I2Cs[i2cNumber].I2C.SR2.REG;
        }
    }
    return ret;
}


Std_ReturnType HAL_I2C_SendByte(const I2C_Number_t i2cNumber, const uint8_t data, sint32_t timeOut) {
    Std_ReturnType ret = E_OK;

    if ((uint32_t) i2cNumber > I2C_Number2) {
        ret = E_NOT_OK;
    } else {

        /* Transmitting Byte */
        ret = send(i2cNumber, data, timeOut);
    }
    return ret;
}

Std_ReturnType HAL_I2C_SendByteLast(const I2C_Number_t i2cNumber, const uint8_t data, sint32_t timeOut) {
    Std_ReturnType ret = E_OK;

    if ((uint32_t) i2cNumber > I2C_Number2) {
        ret = E_NOT_OK;
    } else {


        /* Transmitting Byte */
        ret = send(i2cNumber, data, timeOut);
        WAIT_CONDITION_OR_TIMEOUT(I2C_CheckTxEmpty(i2cNumber) || (ret == E_NOT_OK), timeOut);
    }

    return ret;
}

Std_ReturnType HAL_I2C_SendBytes(const I2C_Number_t i2cNumber, const uint8_t *data, uint16_t size, sint32_t timeOut) {

    Std_ReturnType ret = E_OK;

    if (((uint32_t) i2cNumber > I2C_Number2) || (data == NULL) || (size == 0)) {
        ret = E_NOT_OK;
    } else {

        /* Transmitting Byte by Byte till the remaining size become 0 */
        while ((size-- > 0) && (ret == E_OK)) {
            /* Transmitting Byte */
            ret = send(i2cNumber, *data++, timeOut);
        }

        WAIT_CONDITION_OR_TIMEOUT(
                (I2C_CheckTxEmpty(i2cNumber) || I2C_CheckAckFailure(i2cNumber) ||
                 (ret == E_NOT_OK)), timeOut);

    }
    return ret;
}

Std_ReturnType HAL_I2C_SendString(const I2C_Number_t i2cNumber, const uint8_t *data, sint32_t timeOut) {
    Std_ReturnType ret = E_OK;

    if (((uint32_t) i2cNumber > I2C_Number2) || (data == NULL)) {
        ret = E_NOT_OK;
    } else {
        /* Transmitting Byte by Byte till the null byte of the String */
        while ((*data != 0) && (ret == E_OK)) {

            /* Transmitting the data */
            ret = send(i2cNumber, *data++, timeOut);
        }
        /* Send Null Termination */
        if (ret == E_OK) {

            ret = send(i2cNumber, *data, timeOut);
            WAIT_CONDITION_OR_TIMEOUT_M(
                    (I2C_CheckTxEmpty(i2cNumber) || I2C_CheckAckFailure(i2cNumber)),
                    timeOut);
        }

    }
    return ret;
}

Std_ReturnType HAL_I2C_ReceiveByte(const I2C_Number_t i2cNumber, uint8_t *data, sint32_t timeOut) {
    Std_ReturnType ret = E_OK;

    if (((uint32_t) i2cNumber > I2C_Number2) || (data == NULL)) {
        ret = E_NOT_OK;
    } else {
        /* Receive Byte */
        ret = receive(i2cNumber, data, timeOut);
    }
    return ret;
}

Std_ReturnType HAL_I2C_ReceiveBytes(const I2C_Number_t i2cNumber, uint8_t *data, uint16_t size, sint32_t timeOut) {
    Std_ReturnType ret = E_OK;

    if (((uint32_t) i2cNumber > I2C_Number2) || (data == NULL)) {
        ret = E_NOT_OK;
    } else {
        /* Receive Byte by Byte*/
        while ((size-- > 0) && (ret == E_OK)) {

            /* Receive Byte */
            ret = receive(i2cNumber, data, timeOut);
            // TODO: Check Where the Failure Happen to resend it again
        }
    }
    return ret;
}

Std_ReturnType
HAL_I2C_ReceiveString(const I2C_Number_t i2cNumber, uint8_t *data, uint16_t maxSize, sint32_t timeOut) {

    Std_ReturnType ret = E_OK;
    if (((uint32_t) i2cNumber > I2C_Number2) || (data == NULL)) {
        ret = E_NOT_OK;
    } else {
        /* Receive Byte by Byte*/
        do {

            /* Receive Byte */
            ret = receive(i2cNumber, data, timeOut);
        } while ((*data != 0) && (ret == E_OK));
    }
    return ret;
}


Std_ReturnType HAL_I2C_ResetPeripheral(const I2C_Number_t i2cNumber, sint32_t delay) {
    Std_ReturnType ret = E_OK;
    if ((uint32_t) i2cNumber > I2C_Number2) {
        ret = E_NOT_OK;
    } else {
        pI2C->All.I2Cs[i2cNumber].I2C.CR1.SWRST = STD_ON;
        WAIT_CONDITION_OR_TIMEOUT_M(0, delay);
        pI2C->All.I2Cs[i2cNumber].I2C.CR1.SWRST = STD_OFF;
    }
    return ret;
}

/**************	Section: Helper Methods Declarations  *************/


Std_ReturnType send(I2C_Number_t i2cNumber, uint8_t data, sint32_t timeOut) {

    /* checking that the transmitter is empty*/
    Std_ReturnType ret = E_OK;
    if (I2C_CheckAckFailure(i2cNumber) || I2C_CheckIsStopSent(i2cNumber)) {
        ret = E_NOT_OK;
    } else {
        WAIT_CONDITION_OR_TIMEOUT_M(I2C_CheckTxEmpty(i2cNumber), timeOut);


        if (timeOut != 0) {
            I2C_Data(i2cNumber) = data;

        } else {
            ret = E_NOT_OK;
        }

    }
    return ret;
}

Std_ReturnType receive(I2C_Number_t i2cNumber, uint8_t *data, uint16_t timeOut) {

    Std_ReturnType ret = E_OK;
    /* checking that the data arrived*/
    WAIT_CONDITION_OR_TIMEOUT_M(~I2C_CheckRxEmpty(i2cNumber), timeOut);

    if (timeOut == 0) {
        *data = 0;
        ret = E_NOT_OK; // Invalid data
    } else {
        *data = I2C_Data(i2cNumber);
    }
    return ret;

}





void I2C1_EV_IRQHandler(void){


}

void I2C1_ER_IRQHandler(void){

}

void I2C2_EV_IRQHandler(void){

}

void I2C2_ER_IRQHandler(void){

}