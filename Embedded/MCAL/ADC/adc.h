
#ifndef STM32_DRIVERS_ADC_H
#define STM32_DRIVERS_ADC_H

/**************	Section: Includes ***************************/
#include "std_types.h"
#include "stm32f103c8t.h"
#include "interrupts.h"
#include "gpio.h"




/**************	Section: Macro Definitions Declarations *****/
/**************	Section: Macro Functions Declarations *******/
/**************	Section: Data Types Declarations ************/


typedef enum {
    ADC_Number_1 = (0),
    ADC_Number_2 = (1)
} ADC_Number_t;

typedef enum {
    ADC_Channel_Regular_Number_0 = (0),
    ADC_Channel_Regular_Number_1 = (1),
    ADC_Channel_Regular_Number_2 = (2),
    ADC_Channel_Regular_Number_3 = (3),
    ADC_Channel_Regular_Number_4 = (4),
    ADC_Channel_Regular_Number_5 = (5),
    ADC_Channel_Regular_Number_6 = (6),
    ADC_Channel_Regular_Number_7 = (7),
    ADC_Channel_Regular_Number_8 = (8),
    ADC_Channel_Regular_Number_9 = (9),
    ADC_Channel_Regular_Number_10 = (10),
    ADC_Channel_Regular_Number_11 = (11),
    ADC_Channel_Regular_Number_12 = (12),
    ADC_Channel_Regular_Number_13 = (13),
    ADC_Channel_Regular_Number_14 = (14),
    ADC_Channel_Regular_Number_15 = (15),
    ADC_Channel_Regular_Number_16 = (16),
    ADC_Channel_Regular_Number_17 = (17),
    ADC_Channel_Injected_Number_1 = (18 + 0),
    ADC_Channel_Injected_Number_2 = (18 + 1),
    ADC_Channel_Injected_Number_3 = (18 + 2),
    ADC_Channel_Injected_Number_4 = (18 + 3)
} ADC_ChannelType_Number_t;

typedef enum {
    ADC_Channel_Number_0 = (0),
    ADC_Channel_Number_1 = (1),
    ADC_Channel_Number_2 = (2),
    ADC_Channel_Number_3 = (3),
    ADC_Channel_Number_4 = (4),
    ADC_Channel_Number_5 = (5),
    ADC_Channel_Number_6 = (6),
    ADC_Channel_Number_7 = (7),
    ADC_Channel_Number_8 = (8),
    ADC_Channel_Number_9 = (9),
} ADC_Channel_Number;
typedef enum {
    ADC_Interrupts_None = (0),
    ADC_Interrupts_EndOfConversion = (pADC_EOCIE_ENABLE << 0),
    ADC_Interrupts_EndOfConversion_Injected = (pADC_JEOCIE_ENABLE << 2),
    ADC_Interrupts_AnalogWatchDog = (pADC_AWDIE_ENABLE << 1)
} ADC_Interrupts_t;

typedef enum {
    ADC_AutoInject_Disable = (pADC_JAUTO_DISABLE),
    ADC_AutoInject_Enable = (pADC_JAUTO_ENABLE)
} ADC_AutoInject_t;

typedef enum {
    ADC_Calibrations_None = (0),
    ADC_Calibrations_Calibration = (pADC_CAL_ENABLE_CALIBRATION << 0),
    ADC_Calibrations_ResetCalibration = (pADC_RSTCAL_CALIBRATION_REG_START_INIT << 1),
    ADC_Calibrations_Both = (ADC_Calibrations_Calibration | ADC_Calibrations_ResetCalibration)
} ADC_Calibrations_t;
typedef enum {
    ADC_DMAOptions_Disable = (pADC_DMA_DISABLE),
    ADC_DMAOptions_Enable = (pADC_DMA_ENABLE)
} ADC_DMAOptions_t;

typedef enum {
    ADC_DataAlignment_Right = (pADC_ALIGN_RIGHT),
    ADC_DataAlignment_Left = (pADC_ALIGN_LEFT)
} ADC_DataAlignment_t;
typedef enum {
    ADC_InjectedExternalTriggerSelection_Timer1_TRGO = (pADC_JEXTSEL_TIMER1_TRGO),
    ADC_InjectedExternalTriggerSelection_Timer1_CC4 = (pADC_JEXTSEL_TIMER1_CC4),
    ADC_InjectedExternalTriggerSelection_Timer2_TRGO = (pADC_JEXTSEL_TIMER2_TRGO),
    ADC_InjectedExternalTriggerSelection_Timer2_CC1 = (pADC_JEXTSEL_TIMER2_CC1),
    ADC_InjectedExternalTriggerSelection_Timer3_CC4 = (pADC_JEXTSEL_TIMER3_CC4),
    ADC_InjectedExternalTriggerSelection_Timer4_TRGO = (pADC_JEXTSEL_TIMER4_TRGO),

    ADC_InjectedExternalTriggerSelection_Timer8_CC4_OR_EXTI15 = (pADC_JEXTSEL_EXTI15_TIMER8_CC4),
    ADC_InjectedExternalTriggerSelection_SoftwareStart = (pADC_JEXTSEL_JSWSTART),
} ADC_InjectedExternalTriggerSelection_t;

typedef enum {
    ADC_ExternalTriggerState_Disable = (pADC_JEXTTRIG_INJ_CONV_ON_EXT_EVENT_DISABLE),
    ADC_ExternalTriggerState_Enable = (pADC_JEXTTRIG_INJ_CONV_ON_EXT_EVENT_ENABLE)
} ADC_ExternalTriggerState_t;
typedef enum {
    ADC_RegularExternalTriggerSelection_Timer1_CC1 = (pADC_EXTSEL_TIMER1_CC1),
    ADC_RegularExternalTriggerSelection_Timer1_CC2 = (pADC_EXTSEL_TIMER1_CC2),
    ADC_RegularExternalTriggerSelection_Timer1_CC3 = (pADC_EXTSEL_TIMER1_CC3),
    ADC_RegularExternalTriggerSelection_Timer2_CC2 = (pADC_EXTSEL_TIMER2_CC2),
    ADC_RegularExternalTriggerSelection_Timer3_TRGO = (pADC_EXTSEL_TIMER3_TRGO),
    ADC_RegularExternalTriggerSelection_Timer4_CC4 = (pADC_EXTSEL_TIMER4_CC4),
    ADC_RegularExternalTriggerSelection_Timer8_TRGO_OR_EXTI11 = (pADC_EXTSEL_EXTI11_TIM8_TRGO),
    ADC_RegularExternalTriggerSelection_SoftwareStart = (pADC_EXTSEL_SWSTART),
} ADC_RegularExternalTriggerSelection_t;

typedef enum {
    ADC_TemperatureSensor_Vref_Enable = (pADC_TSVREFE_TEMP_SENSOR_VREF_ENABLE),
    ADC_TemperatureSensor_Vref_Disable = (pADC_TSVREFE_TEMP_SENSOR_VREF_DISABLE)
} ADC_TemperatureSensor_Vref_t;

typedef enum {
    ADC_ScanMode_ScanAllChannels = (pADC_SCAN_ENABLE),
    ADC_ScanMode_ScanDisable = (pADC_SCAN_DISABLE),
} ADC_ScanMode_t;
typedef enum {
    ADC_DiscontinuousMode_Disable = (0),
    ADC_DiscontinuousMode_RegularChannels = (pADC_DISCEN_ENABLE << 0),
    ADC_DiscontinuousMode_InjectedChannels = (pADC_JDISCEN_ENABLE << 1),
    ADC_DiscontinuousMode_Both = (ADC_DiscontinuousMode_RegularChannels | ADC_DiscontinuousMode_InjectedChannels)
} ADC_DiscontinuousMode_t;

typedef enum {
    ADC_DiscontinuousNumber_1_Channel = (pADC_DISCNUM_1_CHANNEL),
    ADC_DiscontinuousNumber_2_Channels = (pADC_DISCNUM_2_CHANNELS),
    ADC_DiscontinuousNumber_3_Channels = (pADC_DISCNUM_3_CHANNELS),
    ADC_DiscontinuousNumber_4_Channels = (pADC_DISCNUM_4_CHANNELS),
    ADC_DiscontinuousNumber_5_Channels = (pADC_DISCNUM_5_CHANNELS),
    ADC_DiscontinuousNumber_6_Channels = (pADC_DISCNUM_6_CHANNELS),
    ADC_DiscontinuousNumber_7_Channels = (pADC_DISCNUM_7_CHANNELS),
    ADC_DiscontinuousNumber_8_Channels = (pADC_DISCNUM_8_CHANNELS)

} ADC_DiscontinuousNumber_t;

typedef enum {
    ADC_ContinuousMode_Enabled = (pADC_CONT_CONTINUOUS_MODE),
    ADC_ContinuousMode_Disabled = (pADC_CONT_SINGLE_MODE)
} ADC_ContinuousMode_t;
typedef enum {
    ADC_DualMode_Independent = (pADC_DUALMOD_INDEPENDENT_MODE),
    ADC_DualMode_RegularSimultaneous_InjectedSimultaneous = (pADC_DUALMOD_REG_SIM_INJ_SIM),
    ADC_DualMode_RegularSimultaneous_InjectedAlternateTrigger = (pADC_DUALMOD_REG_SIM_INJ_ALTR_TRIGERR),
    ADC_DualMode_InjectedSimultaneous_FastInterleaved = (pADC_DUALMOD_INJ_SIM_INTRLV_FAST),
    ADC_DualMode_InjectedSimultaneous_SlowInterleaved = (pADC_DUALMOD_INJ_SIM_INTRLV_SLOW),

    ADC_DualMode_InjectedSimultaneous_Only = (pADC_DUALMOD_INJ_SIM_ONLY),
    ADC_DualMode_RegularSimultaneous_Only = (pADC_DUALMOD_REG_SIM_ONLY),

    ADC_DualMode_FastInterleaved_Only = (pADC_DUALMOD_INTRLV_FAST_ONLY),
    ADC_DualMode_SlowInterleaved_Only = (pADC_DUALMOD_INTRLV_SLOW_ONLY),
    ADC_DualMode_AlternateTrigger_Only = (pADC_DUALMOD_ALTR_TRIGGER_ONLY),
} ADC_DualMode_t;

typedef enum {
    ADC_WatchDogChannelNumber_0 = (pADC_AWDCH_CHANNEL_0),
    ADC_WatchDogChannelNumber_1 = (pADC_AWDCH_CHANNEL_1),
    ADC_WatchDogChannelNumber_2 = (pADC_AWDCH_CHANNEL_2),
    ADC_WatchDogChannelNumber_3 = (pADC_AWDCH_CHANNEL_3),
    ADC_WatchDogChannelNumber_4 = (pADC_AWDCH_CHANNEL_4),
    ADC_WatchDogChannelNumber_5 = (pADC_AWDCH_CHANNEL_5),
    ADC_WatchDogChannelNumber_6 = (pADC_AWDCH_CHANNEL_6),
    ADC_WatchDogChannelNumber_7 = (pADC_AWDCH_CHANNEL_7),
    ADC_WatchDogChannelNumber_8 = (pADC_AWDCH_CHANNEL_8),
    ADC_WatchDogChannelNumber_9 = (pADC_AWDCH_CHANNEL_9),
    ADC_WatchDogChannelNumber_10 = (pADC_AWDCH_CHANNEL_10),
    ADC_WatchDogChannelNumber_11 = (pADC_AWDCH_CHANNEL_11),
    ADC_WatchDogChannelNumber_12 = (pADC_AWDCH_CHANNEL_12),
    ADC_WatchDogChannelNumber_13 = (pADC_AWDCH_CHANNEL_13),
    ADC_WatchDogChannelNumber_14 = (pADC_AWDCH_CHANNEL_14),
    ADC_WatchDogChannelNumber_15 = (pADC_AWDCH_CHANNEL_15),
    ADC_WatchDogChannelNumber_16 = (pADC_AWDCH_CHANNEL_16),
    ADC_WatchDogChannelNumber_17 = (pADC_AWDCH_CHANNEL_17),

} ADC_WatchDogChannelNumber_t;

typedef enum {
    ADC_WatchDogMultiChannelType_None = (0),
    ADC_WatchDogMultiChannelType_InjectedChannels = (pADC_JAWDEN_ANALOG_WATCHDG_INJ_CHANNELS_ENABLE << 0),
    ADC_WatchDogMultiChannelType_RegularChannels = (pADC_AWDEN_ANALOG_WATCHDG_REG_CHANNELS_ENABLE << 1),
    ADC_WatchDogMultiChannelType_Both = (ADC_WatchDogMultiChannelType_InjectedChannels |
                                         ADC_WatchDogMultiChannelType_RegularChannels)
} ADC_WatchDogMultiChannelType_t;
typedef enum {
    ADC_WatchDogSingleMode_SingleChannel = (pADC_AWDSGL_ANALOG_WATCHDG_ONE_CHANNEL),
    ADC_WatchDogSingleMode_AllChannels = (pADC_AWDSGL_ANALOG_WATCHDG_ALL_CHANNELS),

} ADC_WatchDogSingleMode_t;

typedef enum {
    ADC_RegularChannelSampleTime_1_5_Cycles = (pADC_SMPx_1_5_CYCLES),
    ADC_RegularChannelSampleTime_7_5_Cycles = (pADC_SMPx_7_5_CYCLES),
    ADC_RegularChannelSampleTime_13_5_Cycles = (pADC_SMPx_13_5_CYCLES),
    ADC_RegularChannelSampleTime_28_5_Cycles = (pADC_SMPx_28_5_CYCLES),
    ADC_RegularChannelSampleTime_41_5_Cycles = (pADC_SMPx_41_5_CYCLES),
    ADC_RegularChannelSampleTime_55_5_Cycles = (pADC_SMPx_55_5_CYCLES),
    ADC_RegularChannelSampleTime_71_5_Cycles = (pADC_SMPx_71_5_CYCLES),
    ADC_RegularChannelSampleTime_239_5_Cycles = (pADC_SMPx_239_5_CYCLES),
} ADC_RegularChannelSampleTime_t;

typedef enum {
    ADC_RegularChannelsConversionLength_1 = (pADC_L_1_CONVERSION),
    ADC_RegularChannelsConversionLength_2 = (pADC_L_2_CONVERSION),
    ADC_RegularChannelsConversionLength_3 = (pADC_L_3_CONVERSION),
    ADC_RegularChannelsConversionLength_4 = (pADC_L_4_CONVERSION),
    ADC_RegularChannelsConversionLength_5 = (pADC_L_5_CONVERSION),
    ADC_RegularChannelsConversionLength_6 = (pADC_L_6_CONVERSION),
    ADC_RegularChannelsConversionLength_7 = (pADC_L_7_CONVERSION),
    ADC_RegularChannelsConversionLength_8 = (pADC_L_8_CONVERSION),
    ADC_RegularChannelsConversionLength_9 = (pADC_L_9_CONVERSION),
    ADC_RegularChannelsConversionLength_10 = (pADC_L_10_CONVERSION),
    ADC_RegularChannelsConversionLength_11 = (pADC_L_11_CONVERSION),
    ADC_RegularChannelsConversionLength_12 = (pADC_L_12_CONVERSION),
    ADC_RegularChannelsConversionLength_13 = (pADC_L_13_CONVERSION),
    ADC_RegularChannelsConversionLength_14 = (pADC_L_14_CONVERSION),
    ADC_RegularChannelsConversionLength_15 = (pADC_L_15_CONVERSION),
    ADC_RegularChannelsConversionLength_16 = (pADC_L_16_CONVERSION),
} ADC_RegularChannelsConversionLength_t;

typedef enum {

    ADC_InjectedChannelsConversionLength_1 = (pADC_JL_1_CONVERSION),
    ADC_InjectedChannelsConversionLength_2 = (pADC_JL_2_CONVERSION),
    ADC_InjectedChannelsConversionLength_3 = (pADC_JL_3_CONVERSION),
    ADC_InjectedChannelsConversionLength_4 = (pADC_JL_4_CONVERSION),

} ADC_InjectedChannelsConversionLength_t;


typedef enum {
    ADC_ChannelReadType_Regular = (0),
    ADC_ChannelReadType_Injected_1 = (1),
    ADC_ChannelReadType_Injected_2 = (2),
    ADC_ChannelReadType_Injected_3 = (3),
    ADC_ChannelReadType_Injected_4 = (4),
} ADC_ChannelReadType_t;

typedef enum {
    ADC_ChannelType_Regular = (0),
    ADC_ChannelType_Injected = (1)
} ADC_ChannelType_t;
typedef union {
    struct {
        ADC_RegularChannelSampleTime_t SampleTime: 3;
        uint32_t SequenceNumber: 4;
    } RegularChannel;
    struct {
        const uint32_t : 3;
        uint32_t SequenceNumber: 4;
        uint32_t negativeOffset: 11;
    } InjectedChannel;
} ADC_Channel_Config_t;
typedef union {

    struct {
        const uint32_t                  : 5;
        ADC_Interrupts_t interrupts: 3;
        const uint32_t                  : 0;

        const uint32_t : 2;
        ADC_Calibrations_t calibrations: 2;
        const uint32_t          : 4;
        ADC_DMAOptions_t dmaOptions: 1;
        const uint32_t : 2;
        ADC_DataAlignment_t dataAlignment: 1;
        const uint32_t : 11;
        ADC_TemperatureSensor_Vref_t temperatureSensorAndVREF: 1;
    } BasicOptions;

    struct {
        const uint32_t      : 10;
        ADC_AutoInject_t autoInject: 1;
        const uint32_t  : 0;

        const uint32_t  : 12;
        ADC_InjectedExternalTriggerSelection_t triggerSelection: 3;
//        ADC_ExternalTriggerState_t externalTriggerState: 1;
        const uint32_t : 0;
        ADC_InjectedChannelsConversionLength_t conversionLength: 2;


    } InjectedChannelsOptions;

    struct {
        const uint32_t : 32;

        const uint32_t : 17;
        ADC_RegularExternalTriggerSelection_t triggerSelection: 3;
//        ADC_ExternalTriggerState_t externalTriggerState: 1;
        const uint32_t : 0;

        const uint32_t : 2;
        ADC_RegularChannelsConversionLength_t conversionLength: 4;

    } RegularChannelsOptions;

    union {
        struct {
            const uint32_t : 8;
            ADC_ScanMode_t scanMode: 1;
            const uint32_t : 7;
            ADC_DualMode_t dualMode: 4;
            const uint32_t : 0;

            const uint32_t : 1;
            ADC_ContinuousMode_t continuousMode: 1;


        };
        struct {
            const uint32_t : 11;
            ADC_DiscontinuousMode_t mode: 2;
            ADC_DiscontinuousNumber_t count: 3;
        } DiscontinuousMode;


    } Modes;

    struct {
        ADC_WatchDogChannelNumber_t channelNumber: 5;
        const uint32_t      : 4;
        ADC_WatchDogSingleMode_t channelMode: 1;
        const uint32_t   : 12;
        ADC_WatchDogMultiChannelType_t multiChannelType: 2;
        const uint32_t : 0;

        const uint32_t : 32;

        const uint32_t : 6;
        uint16_t highLevelThreshold: 11;
        uint16_t lowLevelThreshold: 11;

    } WatchDogOptions;
} ADC_Config_t;

/**************	Section: Methods Declarations  **************/

Std_ReturnType HAL_ADC_Init(const ADC_Number_t adcNumber, const ADC_Config_t *config);

Std_ReturnType HAL_ADC_DeInit(const ADC_Number_t adcNumber);

Std_ReturnType HAL_ADC_TriggerRegularConv(const ADC_Number_t adcNumber);

Std_ReturnType HAL_ADC_TriggerRegularConvChannel(const ADC_Number_t adcNumber, const ADC_ChannelType_Number_t channelNumber,
                                                 const ADC_RegularChannelSampleTime_t sampleTime);

Std_ReturnType HAL_ADC_TriggerInjectedConversion(const ADC_Number_t adcNumber);

Std_ReturnType
HAL_ADC_Channel_Init(const ADC_Number_t adcNumber, ADC_ChannelType_Number_t channelNumber,
                     const ADC_Channel_Config_t config);

Std_ReturnType
HAL_ADC_ReadChannel(const ADC_Number_t adcNumber, ADC_ChannelReadType_t channelNumber, uint16_t *value);

Std_ReturnType
HAL_ADC_ReadChannelFloat(const ADC_Number_t adcNumber, ADC_ChannelReadType_t channelNumber, float *value);

Std_ReturnType HAL_ADC_ChannelGPIOInit(const ADC_Number_t adcNumber, ADC_Channel_Number channelNumber);

Std_ReturnType HAL_ADC_RegisterInterruptCallback(const ADC_Number_t adcNumber, const InterruptCallback_t callback);

#endif //STM32_DRIVERS_ADC_H
