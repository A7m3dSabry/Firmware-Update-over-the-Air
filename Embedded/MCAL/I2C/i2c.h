

#ifndef STM32_DRIVERSpI2C_H
#define STM32_DRIVERSpI2C_H

/**************	Section: Includes ***************************/

#include "std_types.h"
#include "stm32f103c8t.h"
#include "interrupts.h"
#include "gpio.h"

/**************	Section: Macro Definitions Declarations *****/

/**************	Section: Macro Functions Declarations *******/

#define I2C_CheckAckFailure(i2cNumber)           (pI2C->All.I2Cs[i2cNumber].I2C.SR1.AF == 1)
#define I2C_CheckTxEmpty(i2cNumber)              (pI2C->All.I2Cs[i2cNumber].I2C.SR1.TxE == 1)
#define I2C_CheckRxEmpty(i2cNumber)              (pI2C->All.I2Cs[i2cNumber].I2C.SR1.RxNE == 0)
#define I2C_CheckAddressMatched(i2cNumber)       (pI2C->All.I2Cs[i2cNumber].I2C.SR1.ADDR == 1)
#define I2C_CheckIsBusNotBusy(i2cNumber)         (pI2C->All.I2Cs[i2cNumber].I2C.SR2.BUSY == 0)

#define I2C_CheckIsStartSent(i2cNumber)          (pI2C->All.I2Cs[i2cNumber].I2C.SR1.SB == 1)
#define I2C_CheckIsStopSent(i2cNumber)          (pI2C->All.I2Cs[i2cNumber].I2C.SR1.STOPF == 1)

#define I2C_Data(i2cNumber) (pI2C->All.I2Cs[i2cNumber].I2C.DR.REG)

/**************	Section: Data Types Declarations ************/

typedef enum {
    I2C_Number1 = (0),
    I2C_Number2 = (1),

} I2C_Number_t;


typedef enum {
    I2C_RunningState_Running = (pI2C_PE_ENABLE),
    I2C_RunningState_NotRunning = (pI2C_PE_DISABLE),
} I2C_RunningState_t;

typedef enum {
    I2C_GeneralCallDetection_Enabled = (pI2C_ENGC_ENABLE),
    I2C_GeneralCallDetection_Disabled = (pI2C_ENGC_DISABLE),
} I2C_GeneralCallDetection_t;
typedef enum {
    I2C_ClockStretching_EnableStretching = (pI2C_NOSTRETCH_ENABLE_STRETCHING),
    I2C_ClockStretching_DisableStretching = (pI2C_NOSTRETCH_DISABLE_STRETCHING),
} I2C_ClockStretching_t;

typedef enum {
    I2C_ACKState_ACK = (pI2C_ACK_ACK_ENABLED),
    I2C_ACKState_NACK = (pI2C_ACK_ACK_DISABLED),
} I2C_ACKState_t;


typedef enum {
    I2C_Interrupts_ErrorInterrupts = (pI2C_ITERREN_INTERRUPT_ENABLE),
    I2C_Interrupts_EventInterrupts = (pI2C_ITEVTEN_INTERRUPT_ENABLE << 1),
    I2C_Interrupts_BufferInterrupts = (pI2C_ITBUFEN_INTERRUPT_ENABLE << 2),
} I2C_Interrupts_t;

typedef enum {
    I2C_DMAState_Enabled = (pI2C_DMAEN_ENABLE),
    I2C_DMAState_Disabled = (pI2C_DMAEN_DISABLE),
} I2C_DMAState_t;


typedef enum {
    I2C_AddressingMode_7Bit = (pI2C_ADDMODE_7BIT),
    I2C_AddressingMode_10Bit = (pI2C_ADDMODE_10BIT)
} I2C_AddressingMode_t;

typedef enum {
    I2C_DualAddressing_Enabled = (pI2C_ENDUAL_ENABLE),
    I2C_DualAddressing_Disabled = (pI2C_ENDUAL_DISABLE),
} I2C_DualAddressing_t;

typedef enum {
    I2C_ClockDuty_50Percent = (pI2C_DUTY_FM_tLOW_tHIGH_2),
    I2C_ClockDuty_tLOW_tHIGH_16_9 = (pI2C_DUTY_FM_tLOW_tHIGH_16_9)
} I2C_ClockDuty_t;

typedef enum {
    I2C_MasterSpeedMode_StandardMode_100KHz = (pI2C_F_S_STANDARD_MODE),
    I2C_MasterSpeedMode_FastMode_400KHz = (pI2C_F_S_FAST_MODE),
} I2C_MasterSpeedMode_t;


typedef enum {
    I2C_ReadWriteMode_Write = (0),
    I2C_ReadWriteMode_Read = (1),
} I2C_ReadWriteMode_t;
typedef struct {

    union {


        struct {
            I2C_RunningState_t runImmediately: 1;
            const uint32_t      : 5;
            I2C_GeneralCallDetection_t generalCallDetection: 1;
            I2C_ClockStretching_t slaveClockStretching: 1;
            const uint32_t      : 2;
            I2C_ACKState_t ackState: 1;
            const uint32_t        : 0;

            const uint32_t        : 32;

            const uint32_t : 15;
            I2C_MasterSpeedMode_t masterSpeedMode: 1;


        } BasicOptions;
        struct {
            const uint32_t    : 32;

            //I2C_BusFrequency_t busFrequency: 6;
            const uint32_t : 6;
            const uint32_t    : 0;
            const uint32_t      : 14;
            I2C_ClockDuty_t clockDuty: 1;
            const uint32_t      : 0;
            uint16_t requiredBusClock;


        } ClockOptions;

        struct {
            const uint32_t    : 32;
            const uint32_t    : 8;
            I2C_Interrupts_t interrupts: 3;
            const uint32_t  : 0;
        } InterruptsOptions;

        struct {
            const uint32_t    : 32;
            const uint32_t    : 11;
            I2C_DMAState_t dmaState: 1;
            const uint32_t  : 0;
        } DMAOptions;


    };
    struct {
        union {
            struct {
                const uint32_t      : 1;
                uint32_t Address1_7bit: 7;
            };

            struct {
                uint32_t Address1_10bit: 10;
                const uint32_t      : 5;
                I2C_AddressingMode_t addressingMode: 1;
                const uint32_t : 0;
                I2C_DualAddressing_t dualAddressing: 1;
                uint32_t Address2: 7;
                const uint32_t  : 0;


            };
        };
    } AddressOptions;
} I2C_Config_t;

/**************	Section: Methods Declarations  **************/




Std_ReturnType HAL_I2C_Init(const I2C_Number_t i2cNumber, const I2C_Config_t *config);

Std_ReturnType HAL_I2C_ChangePeripheralState(const I2C_Number_t i2cNumber, const I2C_RunningState_t state);

Std_ReturnType HAL_I2C_InitGPIO(const I2C_Number_t i2cNumber);

//Std_ReturnType HAL_I2C_AcquireBus(const I2C_Number_t i2cNumber);

Std_ReturnType HAL_I2C_SendStart(const I2C_Number_t i2cNumber, sint32_t timeOut);

Std_ReturnType HAL_I2C_SendStop(const I2C_Number_t i2cNumber);

Std_ReturnType HAL_I2C_ChangeAcknowledgementState(const I2C_Number_t i2cNumber, I2C_ACKState_t state);

Std_ReturnType HAL_I2C_ChangeAddressingMode(const I2C_Number_t i2cNumber, I2C_AddressingMode_t mode);

Std_ReturnType HAL_I2C_SelectAddress(const I2C_Number_t i2cNumber, const uint16_t adrs, const I2C_ReadWriteMode_t mode,
                                     sint32_t timeOut);


Std_ReturnType HAL_I2C_SendByte(const I2C_Number_t i2cNumber, const uint8_t data, sint32_t timeOut);

Std_ReturnType HAL_I2C_SendByteLast(const I2C_Number_t i2cNumber, const uint8_t data, sint32_t timeOut);

Std_ReturnType HAL_I2C_SendBytes(const I2C_Number_t i2cNumber, const uint8_t *data, uint16_t size, sint32_t timeOut);

Std_ReturnType HAL_I2C_SendString(const I2C_Number_t i2cNumber, const uint8_t *data, sint32_t);

Std_ReturnType HAL_I2C_ReceiveByte(const I2C_Number_t i2cNumber, uint8_t *data, sint32_t timeOut);

Std_ReturnType HAL_I2C_ReceiveBytes(const I2C_Number_t i2cNumber, uint8_t *data, uint16_t size, sint32_t timeOut);

Std_ReturnType HAL_I2C_ReceiveString(const I2C_Number_t i2cNumber, uint8_t *data, uint16_t maxSize, sint32_t timeOut);

Std_ReturnType HAL_I2C_ResetPeripheral(const I2C_Number_t i2cNumber, sint32_t delay);

#endif //STM32_DRIVERSpI2C_H
