


#ifndef STM32_DRIVERS_USART_H
#define STM32_DRIVERS_USART_H


/**************	Section: Includes ***************************/
#include "usart_cfg.h"
#include "std_types.h"
#include "stm32f103c8t.h"
#include "interrupts.h"
#include "gpio.h"
#include "patterns.h"

/**************	Section: Macro Definitions Declarations *****/
/**************	Section: Macro Functions Declarations *******/



/**************	Section: Data Types Declarations ************/


typedef enum {
    USART_Number_1 = (0),
    USART_Number_2 = (1),
    USART_Number_3 = (2),

} USART_Number_t;

typedef enum {
    USART_Mode_NotActive = (0),
    USART_Mode_ReceiverMode = (1 << 0),
    USART_Mode_TransmitterMode = (1 << 1),
    USART_Mode_TransmitterAndReceiver = (USART_Mode_ReceiverMode | USART_Mode_TransmitterMode),

} USART_DataDirectionMode_t;

typedef enum {
    USART_Interrupts_None = (0),
    USART_Interrupts_Idle = (1),
    USART_Interrupts_DataReceived = (2),
    USART_Interrupts_TransmissionComplete = (4),
    USART_Interrupts_DataTransmitted = (8),
    USART_Interrupts_ParityError = (16),

} USART_Interrupts_t;


typedef enum {
    USART_Parity_None = (0),
    USART_Parity_Even = (pUSART_PCE_ENABLE << 1 | pUSART_PS_EVEN),
    USART_Parity_Odd = (pUSART_PCE_ENABLE << 1 | pUSART_PS_ODD),
} USART_Parity_t;

typedef enum {
    USART_ParityControl_Disable = (pUSART_PCE_DISABLE),
    USART_ParityControl_Enable = (pUSART_PCE_ENABLE)
} USART_ParityControl_t;

typedef enum {
    USART_WakeUpMethod_IdleLine = (pUSART_WAKE_IDLE_LINE),
    USART_WakeUpMethod_AddressMark = (pUSART_WAKE_ADDRESS_MARK)
} USART_WakeUpMethod_t;

typedef enum {
    USART_WordLength_7BITs_Data = (pUSART_M_8BITS),
    USART_WordLength_8BITs_Data = (pUSART_M_9BITS),
    USART_FullPacket_8Bits = USART_WordLength_7BITs_Data,
    USART_FullPacket_9Bits = USART_WordLength_8BITs_Data,
} USART_WordLength_t;

typedef enum {
    USART_SyncClockPhase_FirstEdge = (pUSART_CPHA_FIRST_EDGE),
    USART_SyncClockPhase_SecondEdge = (pUSART_CPHA_SECOND_EDGE)
} USART_SyncClockPhase_t;

typedef enum {
    USART_SyncClockPolarity_WorkOnHighLevel = (pUSART_CPOL_IDLE_LOW_VOLTAGE),
    USART_SyncClockPolarity_WorkOnLowLevel = (pUSART_CPOL_IDLE_HIGH_VOLTAGE)
} USART_SyncClockPolarity_t;

typedef enum {
    USART_StopBits_1Bit = (pUSART_STOP_ONE_STOP_BIT),
    USART_StopBits_1_5Bits = (pUSART_STOP_ONE_AND_HALF_STOP_BIT),
    USART_StopBits_0_5Bits = (pUSART_STOP_HALF_STOP_BIT),
    USART_StopBits_2Bits = (pUSART_STOP_TWO_STOP_BIT)
} USART_StopBits_t;


typedef enum {
    USART_SyncClockEnable_Enable = (pUSART_CLKEN_CLK_ENABLE),
    USART_SyncClockEnable_Disable = (pUSART_CLKEN_CLK_DISABLE)
} USART_SyncClockEnable_t;

typedef enum {
    USART_Mode_Async = (0),
    USART_Mode_Sync = (1),
    USART_Mode_HalfDuplex = (2),

} USART_Mode_t;

typedef enum {
    USART_HardwareFlowControl_None = (0),
    USART_HardwareFlowControl_RTS = (pUSART_RTSE_RTS_ENABLE << 0),
    USART_HardwareFlowControl_CTS = (pUSART_CTSE_CTS_ENABLE << 1),
    USART_HardwareFlowControl_RTSAndCTS = (USART_HardwareFlowControl_RTS | USART_HardwareFlowControl_CTS)
} USART_HardwareFlowControl_t;

typedef enum {
    USART_HardwareFlowControlInterrupts_None = (0),
    USART_HardwareFlowControlInterrupts_onCTSChange = (pUSART_CTSIE_CTS_INTERRUPT_ENABLE)
} USART_HardwareFlowControlInterrupts_t;

typedef enum {
    USART_DMAOptions_Disable = (0),
    USART_DMAOptions_onReceive = (pUSART_DMAR_DMA_RX_ENABLE << 0),
    USART_DMAOptions_onTransmit = (pUSART_DMAT_DMA_TX_ENABLE << 1)
} USART_DMAOptions_t;

typedef enum {
    USART_ErrorInterrupts_Disable = (STD_OFF),
    USART_ErrorInterrupts_Enable = (STD_ON)
} USART_ErrorInterrupts_t;
typedef struct {


    union {
        struct {

            const uint32_t          : 32;
            const uint32_t          : 9;
            USART_SyncClockPhase_t clockPhase: 1;
            USART_SyncClockPolarity_t clockPolarity: 1;
            USART_SyncClockEnable_t clockEnable: 1;

        } SyncModeOptions;

        struct {
            const uint32_t          : 32;
            const uint32_t          : 32;
            const uint32_t          : 8;
            USART_HardwareFlowControl_t hardwareFlowControl: 2;
            USART_HardwareFlowControlInterrupts_t hardwareFlowControlInterrupts: 1;
        } AsyncModeOptions;
        struct {
            /* NOTHING */
        } HalfDuplexModeOptions;


        union {


            struct {

                const uint32_t                          : 2;
                USART_DataDirectionMode_t dataDirectionMode: 2;
                uint32_t interrupts: 5;

                USART_Parity_t parity: 2;
                const uint32_t                           : 1;
                USART_WordLength_t wordLength: 1;
                const uint32_t                      : 19;        // Align to 4 bytes
            };

            struct {

                const uint32_t      : 32;
                const uint32_t       : 12;
                USART_StopBits_t stopBits: 2;
                const uint32_t          : 18;


            };
            struct {
                const uint32_t      : 32;
                const uint32_t      : 32;
                USART_ErrorInterrupts_t errorInterrupts: 1;
                const uint32_t          : 5;
                USART_DMAOptions_t dmaOptions: 2;
                const uint32_t          : 24;
            };
        } BasicConfig;
    };

    uint32_t BaudRate;
    USART_Mode_t mode: 4;
} USART_Config_t;


/**************	Section: Methods Declarations  **************/

Std_ReturnType HAL_USART_GPIOInit(const USART_Number_t usartNumber, const USART_Config_t *config);

Std_ReturnType HAL_USART_Init(const USART_Number_t usartNumber, const USART_Config_t *config);

Std_ReturnType HAL_USART_ChangeBaudRate(const USART_Number_t usartNumber,USART_Config_t  *config, const uint32_t baudRate) ;

Std_ReturnType HAL_USART_SendByte(const USART_Number_t usartNumber, const uint32_t data);

Std_ReturnType HAL_USART_SendBytes(const USART_Number_t usartNumber, const uint8_t *data, uint16_t size);

Std_ReturnType HAL_USART_SendString(const USART_Number_t usartNumber, const uint8_t *str, uint32_t maxSize);


Std_ReturnType HAL_USART_ReceiveByte(const USART_Number_t usartNumber, uint8_t *data, uint32_t timeOut);

Std_ReturnType HAL_USART_ReceiveBytes(const USART_Number_t usartNumber, uint8_t *data, uint16_t size, uint32_t timeOut);

Std_ReturnType
HAL_USART_ReceiveString(const USART_Number_t usartNumber, uint8_t *data, uint16_t maxSize, uint32_t timeOut);

Std_ReturnType HAL_USART_ReceiveUntilPattern(const USART_Number_t usartNumber,
                                             uint8_t *restrict data, sint32_t *foundPattern,
                                             sint32_t *restrict const count, uint32_t maxSize,
                                             const PatternManager_t *restrict patternManager,
                                             uint32_t IGNORE_FLAGS_START);

Std_ReturnType HAL_USART_RegisterInterruptCallback(const USART_Number_t usartNumber, InterruptCallback_t callback);

Std_ReturnType HAL_USART_SendBreakFrame(const USART_Number_t usartNumber);

//uint32_t __HAL_USART_BaudRateCalculation(const uint32_t baudRate);

Std_ReturnType HAL_USART_waitForChar(const USART_Number_t usartNumber, uint8_t waitChar, uint32_t timeOut);

#endif //STM32_DRIVERS_USART_H
