

#ifndef STM32_DRIVERS_DMA_H
#define STM32_DRIVERS_DMA_H



/**************	Section: Includes ***************************/

#include "std_types.h"
#include "stm32f103c8t.h"
#include "interrupts.h"

/**************	Section: Macro Definitions Declarations *****/
/**************	Section: Macro Functions Declarations *******/
/**************	Section: Data Types Declarations ************/



typedef enum {
    DMA_Channel_1 = (0),
    DMA_Channel_2 = (1),
    DMA_Channel_3 = (2),
    DMA_Channel_4 = (3),
    DMA_Channel_5 = (4),
    DMA_Channel_6 = (5),
    DMA_Channel_7 = (6)
} DMA_ChannelNumber_t;


typedef enum {
    ChannelPriority_Low = (DMA_PL_PRIORITY_LEVEL_LOW),
    ChannelPriority_Medium = (DMA_PL_PRIORITY_LEVEL_MEDIUM),
    ChannelPriority_High = (DMA_PL_PRIORITY_LEVEL_HIGH),
    ChannelPriority_VeryHigh = (DMA_PL_PRIORITY_LEVEL_VERYHIGH),


} DMA_ChannelPriority_t;

typedef enum {
    DataSize_8bits = (DMA_MSIZE_PERPH_SIZE_8BITS),
    DataSize_16bits = (DMA_MSIZE_PERPH_SIZE_16BITS),
    DataSize_32bits = (DMA_MSIZE_PERPH_SIZE_32BITS)

} DMA_DataSize_t;

typedef enum {
    IncrementMode_Enabled = (STD_ON),
    IncrementMode_Disabled = (STD_OFF)
} DMA_IncrementMode_t;

typedef enum {
    CircularMode_Enabled = (STD_ON),
    CircularMode_Disabled = (STD_OFF)
} DMA_CircularMode_t;

typedef enum {
    DataTransferDirection_PeripheralToMemory = (STD_LOW),
    DataTransferDirection_MemoryToPeripheral = (STD_HIGH),
} DMA_DataTransferDirection_t;

typedef enum {
    MemoryToMemory_Enable   = (STD_ON),
    MemoryToMemory_Disable = (STD_OFF)
}DMA_MemoryToMemory_t;
typedef enum {
    DMA_Interrupts_None = (0),
    DMA_Interrupts_TransferComplete = (1),
    DMA_Interrupts_HalfTransferComplete = (2),
    DMA_Interrupts_ErrorOccurred = (4),
} DMA_Interrupts_t;


typedef enum {
    DMA_PeripheralRequest_ADC    =(DMA_Channel_1),
    DMA_PeripheralRequest_Timer2_Channel3   = (DMA_Channel_1),
    DMA_PeripheralRequest_Timer4_Channel1   = (DMA_Channel_1),

    DMA_PeripheralRequest_USART3_TX   = (DMA_Channel_2),
    DMA_PeripheralRequest_Timer1_Channel1   = (DMA_Channel_2),
    DMA_PeripheralRequest_Timer2_UP   = (DMA_Channel_2),
    DMA_PeripheralRequest_Timer3_Channel3   = (DMA_Channel_2),
    DMA_PeripheralRequest_SPI1_RX   = (DMA_Channel_2),

    DMA_PeripheralRequest_USART3_RX   = (DMA_Channel_3),
    DMA_PeripheralRequest_Timer1_Channel2   = (DMA_Channel_3),
    DMA_PeripheralRequest_Timer3_Channel4   = (DMA_Channel_3),
    DMA_PeripheralRequest_Timer3_UP   = (DMA_Channel_3),
    DMA_PeripheralRequest_SPI1_TX   = (DMA_Channel_3),

    DMA_PeripheralRequest_USART1_TX   = (DMA_Channel_4),
    DMA_PeripheralRequest_Timer1_Channel4   = (DMA_Channel_4),
    DMA_PeripheralRequest_Timer1_TRIG   = (DMA_Channel_4),
    DMA_PeripheralRequest_Timer1_COM   = (DMA_Channel_4),
    DMA_PeripheralRequest_Timer4_Channel2   = (DMA_Channel_4),
    DMA_PeripheralRequest_SPI2_RX   = (DMA_Channel_4),
    DMA_PeripheralRequest_I2S2_RX   = (DMA_PeripheralRequest_SPI2_RX),
    DMA_PeripheralRequest_I2C_TX   = (DMA_Channel_4),

    DMA_PeripheralRequest_USART1_RX   = (DMA_Channel_5),
    DMA_PeripheralRequest_Timer1_UP   = (DMA_Channel_5),
    DMA_PeripheralRequest_SPI2_TX   = (DMA_Channel_5),
    DMA_PeripheralRequest_I2S2_TX   = (DMA_PeripheralRequest_SPI2_TX),
    DMA_PeripheralRequest_Timer2_Channel1   = (DMA_Channel_5),
    DMA_PeripheralRequest_Timer4_Channel3   = (DMA_Channel_5),
    DMA_PeripheralRequest_I2C2_RX   = (DMA_Channel_5),
    
    
    DMA_PeripheralRequest_USART2_RX   = (DMA_Channel_6),
    DMA_PeripheralRequest_Timer1_Channel3   = (DMA_Channel_6),
    DMA_PeripheralRequest_Timer3_Channel1   = (DMA_Channel_6),
    DMA_PeripheralRequest_Timer3_TRIG   = (DMA_Channel_6),
    DMA_PeripheralRequest_I2C1_TX   = (DMA_Channel_6),

    DMA_PeripheralRequest_USART2_TX   = (DMA_Channel_7),
    DMA_PeripheralRequest_Timer2_Channel2   = (DMA_Channel_7),
    DMA_PeripheralRequest_Timer2_Channel4   = (DMA_Channel_7),
    DMA_PeripheralRequest_Timer4_UP   = (DMA_Channel_7),
    DMA_PeripheralRequest_I2C1_RX   = (DMA_Channel_7),
    
    
    

} DMA_PeripheralRequest_t;
typedef struct {
    struct {
        uint32_t runImmediately: 1;
        DMA_Interrupts_t interrupts: 3;
        DMA_DataTransferDirection_t direction: 1;
        DMA_CircularMode_t circularMode: 1;
        DMA_IncrementMode_t peripheralIncrementMode: 1;
        DMA_IncrementMode_t memoryIncrementMode: 1;
        DMA_DataSize_t peripheralDataSize: 2;
        DMA_DataSize_t memoryDataSize: 2;
        DMA_ChannelPriority_t priority: 2;
        DMA_MemoryToMemory_t memoryToMemory :1;

        uint32_t        : 0;
    } ChannelConfigurations;
    uint16_t operationsCount;
    uint32_t peripheralAddress;
    uint32_t memoryAddress;
} DMA_ChannelConfig_t;

/**************	Section: Methods Declarations  **************/

Std_ReturnType HAL_DMA_Init(const DMA_ChannelNumber_t  channelNumber,const DMA_ChannelConfig_t *config);

Std_ReturnType  HAL_DMA_InitPeripheral(DMA_PeripheralRequest_t peripheralRequest, const DMA_ChannelConfig_t *config );

Std_ReturnType HAL_DMA_StartTransfer(const DMA_ChannelNumber_t channelNumber);

Std_ReturnType HAL_DMA_StartTransferCount(const DMA_ChannelNumber_t channelNumber, const uint16_t NumberOfTransfers) ;

Std_ReturnType HAL_DMA_StartBlockingTransfer(const DMA_ChannelNumber_t channelNumber, const uint16_t NumberOfTransfers , uint32_t maxTime);

Std_ReturnType HAL_DMA_RegisterInterruptCallback(const DMA_PeripheralRequest_t channel, const InterruptCallback_t callback);

#endif //STM32_DRIVERS_DMA_H
