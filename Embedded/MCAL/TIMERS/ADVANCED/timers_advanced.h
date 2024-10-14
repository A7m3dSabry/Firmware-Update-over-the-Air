
#ifndef STM32_DRIVERS_TIMERS_ADVANCED_H
#define STM32_DRIVERS_TIMERS_ADVANCED_H

/**************	Section: Includes ***************************/
#include "std_types.h"
#include "stm32f103c8t.h"
#include "timers.h"
#include "interrupts.h"
#include "rcc_cfg.h"
#include <stdlib.h>
/**************	Section: Macro Definitions Declarations *****/
/**************	Section: Macro Functions Declarations *******/
/**************	Section: Data Types Declarations ************/
typedef enum {
    Timers_A_TimerNumber_1 = (0)
} Timers_A_TimerNumber_t;

typedef enum {
    Timers_A_ChannelNumber_1 = (0),
    Timers_A_ChannelNumber_2 = (1),
    Timers_A_ChannelNumber_3 = (2),
    Timers_A_ChannelNumber_4 = (3)
} Timers_A_ChannelNumber_t;

typedef enum {
    Timers_A_State_ON = (STD_ON),
    Timers_A_State_OFF = (STD_OFF),
} Timers_A_ChannelState_t;


typedef enum {

    Timers_A_ClockSourceMode_InternalClock = (TIMERS_SMS_INTERNAL_CLK),
    Timers_A_ClockSourceMode_Encoder_TI2FP1_CLK_TI1FP2_DIR = (TIMERS_SMS_ENCODER_1_TI1FP2),
    Timers_A_ClockSourceMode_Encoder_TI1FP2_CLK_TI2FP1_DIR = (TIMERS_SMS_ENCODER_2_TI2FP1),
    Timers_A_ClockSourceMode_Encoder_TIxFPy_CLK_TIyFPx_DIR = (TIMERS_SMS_ENCODER_3_TI1FP1_TI1FP2),
    Timers_A_ClockSourceMode_Encoder_Both_CLK_Both_DIR = (TIMERS_SMS_ENCODER_3_TI1FP1_TI1FP2),

    Timers_A_ClockSourceMode_Trigger_ResetOnRising = (TIMERS_SMS_RESET_ON_TRIGGER),
    Timers_A_ClockSourceMode_Trigger_GatedOnHighLevel = (TIMERS_SMS_GATED_COUNT_ON_HIGH_LEVEL),
    Timers_A_ClockSourceMode_Trigger_Start = (TIMERS_SMS_TRIGGER_START),
    Timers_A_ClockSourceMode_Trigger_Clock = (TIMERS_SMS_TRIGGER_IS_CLK),
    Timers_A_ClockSourceMode_ExternalClock1 = (TIMERS_SMS_TRIGGER_IS_CLK),

    // NOTE External Clock Mode 2 enabled by ETRF bit
} Timers_A_ClockSourceMode_t;

typedef enum {
    Timers_A_TriggerSource_InternalTrigger0 = (TIMERS_TS_ITR0),
    Timers_A_TriggerSource_InternalTrigger1 = (TIMERS_TS_ITR1),
    Timers_A_TriggerSource_InternalTrigger2 = (TIMERS_TS_ITR2),
    Timers_A_TriggerSource_InternalTrigger3 = (TIMERS_TS_ITR3),

    Timers_A_TriggerSource_TI1_BothEdges = (TIMERS_TS_TI1_ED),
    Timers_A_TriggerSource_TI1_OneEdge = (TIMERS_TS_TI1FP1),
    Timers_A_TriggerSource_TI2_OneEdge = (TIMERS_TS_TI2FP2),

    Timers_A_TriggerSource_ExternalTriggerPin = (TIMERS_TS_ETRF),


} Timers_A_TriggerSourceMode_t;

typedef enum {
    Timers_A_SlavesSync_OFF = (TIMERS_MSM_NO_ACTION),
    Timers_A_SlavesSync_ON = (TIMERS_MSM_DELAY_TO_SYNC),
} Timers_A_SlavesSync_t;

typedef enum {
    Timers_A_ExternalTriggerFilterFREQ_DTS = (TIMERS_ETF_DTS_NO_FILTER),

    Timers_A_ExternalTriggerFilterFREQ_CK_INT_2 = (TIMERS_ETF_CK_INT_N2),
    Timers_A_ExternalTriggerFilterFREQ_CK_INT_4 = (TIMERS_ETF_CK_INT_N4),
    Timers_A_ExternalTriggerFilterFREQ_CK_INT_8 = (TIMERS_ETF_CK_INT_N8),

    Timers_A_ExternalTriggerFilterFREQ_DTS_2_N6 = (TIMERS_ETF_DTS_2_N6),
    Timers_A_ExternalTriggerFilterFREQ_DTS_2_N8 = (TIMERS_ETF_DTS_2_N8),

    Timers_A_ExternalTriggerFilterFREQ_DTS_4_N6 = (TIMERS_ETF_DTS_4_N6),
    Timers_A_ExternalTriggerFilterFREQ_DTS_4_N8 = (TIMERS_ETF_DTS_4_N8),

    Timers_A_ExternalTriggerFilterFREQ_DTS_8_N6 = (TIMERS_ETF_DTS_8_N6),
    Timers_A_ExternalTriggerFilterFREQ_DTS_8_N8 = (TIMERS_ETF_DTS_8_N8),

    Timers_A_ExternalTriggerFilterFREQ_DTS_16_N5 = (TIMERS_ETF_DTS_16_N5),
    Timers_A_ExternalTriggerFilterFREQ_DTS_16_N6 = (TIMERS_ETF_DTS_16_N6),
    Timers_A_ExternalTriggerFilterFREQ_DTS_16_N8 = (TIMERS_ETF_DTS_16_N8),

    Timers_A_ExternalTriggerFilterFREQ_DTS_32_N5 = (TIMERS_ETF_DTS_32_N5),
    Timers_A_ExternalTriggerFilterFREQ_DTS_32_N6 = (TIMERS_ETF_DTS_32_N6),
    Timers_A_ExternalTriggerFilterFREQ_DTS_32_N8 = (TIMERS_ETF_DTS_32_N8),

} Timers_A_ExternalTriggerFilterFreq_t;

typedef enum {
    Timers_A_ExternalTriggerPrescaller_1 = (TIMERS_ETPS_DIV_1),
    Timers_A_ExternalTriggerPrescaller_2 = (TIMERS_ETPS_DIV_2),
    Timers_A_ExternalTriggerPrescaller_4 = (TIMERS_ETPS_DIV_4),
    Timers_A_ExternalTriggerPrescaller_8 = (TIMERS_ETPS_DIV_8),
} Timers_A_ExternalTriggerPrescaller_t;

typedef enum {
    Timers_A_ExternalTriggerPinForce_ON = (TIMERS_ECE_CLK_SRC_ETRF_ENABLE),
    Timers_A_ExternalTriggerPinForce_OFF = (TIMERS_ECE_CLK_SRC_ETRF_DISABLE),

} Timers_A_ExternalTriggerPinForce_t;
typedef enum {
    Timers_A_ExternalTriggerPolarity_HIGH = (TIMERS_ETP_POLARITY_NON_INV),
    Timers_A_ExternalTriggerPolarity_LOW = (TIMERS_ETP_POLARITY_INV)

} Timers_A_ExternalTriggerPolarity_t;

typedef enum {
    Timers_A_UpdateEvent_Enable = (TIMERS_BASIC_UDIS_ENABLE_UPDATES),
    Timers_A_UpdateEvent_Disable = (TIMERS_BASIC_UDIS_DISABLE_UPDATES),
} Timers_A_UpdateEvent_t;

typedef enum {
    Timers_A_UpdateEventSource_ALL = (TIMERS_BASIC_URS_ALL),
    Timers_A_UpdateEventSource_OnlyCounter = (TIMERS_BASIC_URS_ONLY_COUNTER),
} Timers_A_UpdateEventSource_t;

typedef enum {
    Timers_A_OneShotMode_Enable = (TIMERS_BASIC_OPM_ENABLE),
    Timers_A_OneShotMode_Disable = (TIMERS_BASIC_OPM_DISABLE),
} Timers_A_OneShotMode_t;

typedef enum {
    Timers_A_CountingMode_CountingUp = (TIMERS_CMS_EDGE_ALIGNED << 1 | TIMERS_DIR_UP),
    Timers_A_CountingMode_CountingDown = (TIMERS_CMS_EDGE_ALIGNED << 1 | TIMERS_DIR_DOWN),
    Timers_A_CountingMode_CountingUpDown_UpdateAfterDown = (TIMERS_CMS_CENTER_ALIGNED_MODE1 << 1),
    Timers_A_CountingMode_CountingUpDown_UpdateAfterUp = (TIMERS_CMS_CENTER_ALIGNED_MODE2 << 1),
    Timers_A_CountingMode_CountingUpDown_UpdateAfterUpDown = (TIMERS_CMS_CENTER_ALIGNED_MODE3 << 1),
} Timers_A_CountingMode_t;

typedef enum {
    Timers_A_AutoReloadPreload_Enable = (TIMERS_ARPE_BUFFER_ENABLE),
    Timers_A_AutoReloadPreload_Disable = (TIMERS_ARPE_BUFFER_DISABLE),
} Timers_A_AutoReloadPreload_t;


typedef enum {
    Timers_A_Interrupts_UpdateInterrupt = (TIMERS_UIE_ENABLE << TIMERS_BASIC_UIE_POS),
    Timers_A_Interrupts_CaptureCompare_1 = (TIMERS_CC1IE_ENABLE << TIMERS_CC1IE_POS),
    Timers_A_Interrupts_CaptureCompare_2 = (TIMERS_CC2IE_ENABLE << TIMERS_CC2IE_POS),
    Timers_A_Interrupts_CaptureCompare_3 = (TIMERS_CC3IE_ENABLE << TIMERS_CC3IE_POS),
    Timers_A_Interrupts_CaptureCompare_4 = (TIMERS_CC4IE_ENABLE << TIMERS_CC4IE_POS),
    Timers_A_Interrupts_COMInterrupt = (TIMERS_COMIE_ENABLE << TIMERS_COMIE_POS),
    Timers_A_Interrupts_TriggerInterrupt = (TIMERS_TIE_ENABLE << TIMERS_TIE_POS),
    Timers_A_Interrupts_BreakInterrupt = (TIMERS_BIE_ENABLE << TIMERS_BIE_POS),
} Timers_A_Interrupts_t;

typedef enum {
    Timers_A_DMARequests_onUpdateEvent = (TIMERS_UDE_ENABLE << 0),
    Timers_A_DMARequests_onCaptureCompare1 = (TIMERS_CC1DE_ENABLE << 1),
    Timers_A_DMARequests_onCaptureCompare2 = (TIMERS_CC2DE_ENABLE << 2),
    Timers_A_DMARequests_onCaptureCompare3 = (TIMERS_CC3DE_ENABLE << 3),
    Timers_A_DMARequests_onCaptureCompare4 = (TIMERS_CC4DE_ENABLE << 4),
    Timers_A_DMARequests_onCOMEvent = (TIMERS_COMDE_ENABLE << 5),
    Timers_A_DMARequests_onTrigger = (TIMERS_TDE_ENABLE << 6),
} Timers_A_DMARequests_t;

typedef enum {
    Timers_A_CaptureCompareSelection_CompareMode = (TIMERS_CCxS_OUTPUT),
    Timers_A_CaptureCompareSelection_Capture_Same_TIFxP = (TIMERS_CCxS_INPUT_SAME_TIFxP),
    Timers_A_CaptureCompareSelection_Capture_Alternate_TIFxP = (TIMERS_CCxS_INPUT_ALTERNATE_TIFxP),
    Timers_A_CaptureCompareSelection_Capture_TRC = (TIMERS_CCxS_INPUT_TRC),

} Timers_A_CaptureCompareSelection_t;

typedef enum {
    Timers_A_CompareFastMode_Enable = (TIMERS_OCxFE_ENABLE),
    Timers_A_CompareFastMode_Disable = (TIMERS_OCxFE_DISABLE),
} Timers_A_PWMFastMode_t;

typedef enum {
    Timers_A_CompareOutputPreloaded_Enable = (TIMERS_OCxPE_ENABLE),
    Timers_A_CompareOutputPreloaded_Disable = (TIMERS_OCxPE_DISABLE),
} Timers_A_CompareOutputPreloaded_t;

typedef enum {
    Timers_A_CompareOutputMode_NoOutput = (TIMERS_OCxM_FROZEN),
    Timers_A_CompareOutputMode_OCxREFSetHigh = (TIMERS_OCxM_OCxREF_HIGH),
    Timers_A_CompareOutputMode_OCxREFSetLow = (TIMERS_OCxM_OCxREF_LOW),
    Timers_A_CompareOutputMode_OCxREFToggle = (TIMERS_OCxM_OCxREF_TOGGLE),
    Timers_A_CompareOutputMode_ForceLow = (TIMERS_OCxM_OCxREF_FORCE_LOW),
    Timers_A_CompareOutputMode_ForceHigh = (TIMERS_OCxM_OCxREF_FORCE_HIGH),
    Timers_A_CompareOutputMode_PWMNormal = (TIMERS_OCxM_OCxREF_PWM_NORMAL),
    Timers_A_CompareOutputMode_PWMInverted = (TIMERS_OCxM_OCxREF_PWM_INVERTED),
} Timers_A_CompareOutputMode_t;

typedef enum {
    Timers_A_CompareOutputClearOnExternalTrigger_Enable = (TIMERS_OCxCE_ETRF_CLEAR),
    Timers_A_CompareOutputClearOnExternalTrigger_Disable = (TIMERS_OCxCE_ETRF_NOT_AFFECT),
} Timers_A_CompareOutputClearOnExternalTrigger_t;

typedef enum {
    Timers_A_InputCapturePrescaller_NoPrescalling = (TIMERS_ICxPSC_DIV_1),
    Timers_A_InputCapturePrescaller_DIV_1 = (TIMERS_ICxPSC_DIV_1),
    Timers_A_InputCapturePrescaller_DIV_2 = (TIMERS_ICxPSC_DIV_2),
    Timers_A_InputCapturePrescaller_DIV_4 = (TIMERS_ICxPSC_DIV_4),
    Timers_A_InputCapturePrescaller_DIV_8 = (TIMERS_ICxPSC_DIV_8),
} Timers_A_InputCapturePrescaller_t;

typedef enum {
    Timers_CaptureMode_CaptureEdge_Rising = 0,
    Timers_CaptureMode_CaptureEdge_Falling = 1,
} Timers_CaptureMode_CaptureEdge_t;

typedef enum {
    Timers_A_InputCaptureFilterFreq_NoFilter = (TIMERS_ICxF_NO_FILTER),
    Timers_A_InputCaptureFilterFreq_CK_INT_N2 = (TIMERS_ICxF_CK_INT_N2),
    Timers_A_InputCaptureFilterFreq_CK_INT_N4 = (TIMERS_ICxF_CK_INT_N4),
    Timers_A_InputCaptureFilterFreq_CK_INT_N8 = (TIMERS_ICxF_CK_INT_N8),

    Timers_A_InputCaptureFilterFreq_DTS_2_N6 = (TIMERS_ICxF_DTS_2_N6),
    Timers_A_InputCaptureFilterFreq_DTS_2_N8 = (TIMERS_ICxF_DTS_2_N8),

    Timers_A_InputCaptureFilterFreq_DTS_4_N6 = (TIMERS_ICxF_DTS_4_N6),
    Timers_A_InputCaptureFilterFreq_DTS_4_N8 = (TIMERS_ICxF_DTS_4_N8),

    Timers_A_InputCaptureFilterFreq_DTS_8_N6 = (TIMERS_ICxF_DTS_8_N6),
    Timers_A_InputCaptureFilterFreq_DTS_8_N8 = (TIMERS_ICxF_DTS_8_N8),

    Timers_A_InputCaptureFilterFreq_DTS_16_N5 = (TIMERS_ICxF_DTS_16_N5),
    Timers_A_InputCaptureFilterFreq_DTS_16_N6 = (TIMERS_ICxF_DTS_16_N6),
    Timers_A_InputCaptureFilterFreq_DTS_16_N8 = (TIMERS_ICxF_DTS_16_N8),

    Timers_A_InputCaptureFilterFreq_DTS_32_N5 = (TIMERS_ICxF_DTS_32_N5),
    Timers_A_InputCaptureFilterFreq_DTS_32_N6 = (TIMERS_ICxF_DTS_32_N6),
    Timers_A_InputCaptureFilterFreq_DTS_32_N8 = (TIMERS_ICxF_DTS_32_N8),

} Timers_A_InputCaptureFilterFreq_t;


typedef enum {
    Timers_A_CaptureInputPolarity_RisingEdge = (TIMERS_CCxP_CAPTURE_RISING_EDGE),
    Timers_A_CaptureInputPolarity_FallingEdge = (TIMERS_CCxP_CAPTURE_FALLING_EDGE),
    Timers_A_CompareOutputPolarity_NonInverted = (TIMERS_CCxP_COMPARE_OCxREF_NON_INVERTED),
    Timers_A_CompareOutputPolarity_Inverted = (TIMERS_CCxP_COMPARE_OCxREF_INVERTED),
} Timers_A_CaptureCompareInputOutputPolarity_t;


typedef struct {

    union {
        Timers_A_CaptureCompareSelection_t mode: 2;
        struct {
            uint32_t         : 2;
            Timers_A_PWMFastMode_t pwmFastMode: 1;
            Timers_A_CompareOutputPreloaded_t compareOutputPreload: 1;
            Timers_A_CompareOutputMode_t outputMode: 3;
            Timers_A_CompareOutputClearOnExternalTrigger_t compareClearOnExternalTrigger: 1;
            const uint32_t : 0;

            const uint32_t : 1;
            Timers_A_CaptureCompareInputOutputPolarity_t polarity: 1;
            const uint32_t : 1;
            Timers_A_CaptureCompareInputOutputPolarity_t complementaryPolarity: 1;

        } CompareOptions;
        struct {
            const uint32_t : 2;
            Timers_A_InputCapturePrescaller_t inputCapturePrescaller: 2;
            Timers_A_InputCaptureFilterFreq_t inputCaptureFilter: 4;
            const uint32_t  : 0;
            const uint32_t : 1;
            Timers_CaptureMode_CaptureEdge_t captureEdge: 1;

        } CaptureOptions;

    } Options;

    uint16_t captureCompareValue;

} Timers_A_Channel_Config_t;

typedef enum {
    d
} Timers_A_CaptureMode_;

typedef enum {
    Timers_CaptureCompare_PinsPreload_Disabled = 0,
    Timers_CaptureCompare_PinsPreload_Enabled = 1,
} Timers_CaptureCompare_PinsPreload_t;

typedef enum {
    Timers_CaptureCompare_UpdateSource_COMG_bit_Only = 0,
    Timers_CaptureCompare_UpdateSource_COMG_bit_And_Rise_TRGO = 0,
} Timers_CaptureCompare_UpdateSource_t;


/**
 * @brief DMA Capture Compare Requests Trigger
 */
typedef enum {
    Timers_DMARequestTrigger_CaptureCompareEvents = 0,
    Timers_DMARequestTrigger_TimerUpdateEvent = 1,

} Timers_DMARequestTrigger_t;


/**
 * @brief Timer Trigger Output (TRGO) Triggered on:
 */
typedef enum {
    Timers_MasterMode_Trigger_ON_Reset = 0,
    Timers_MasterMode_Trigger_On_Enable = 1,
    Timers_MasterMode_Trigger_On_Update = 2,
    Timers_MasterMode_Trigger_On_Channel1_CC_Flag = 3,
    Timers_MasterMode_Trigger_On_Channel1_CC = 4,
    Timers_MasterMode_Trigger_On_Channel2_CC = 5,
    Timers_MasterMode_Trigger_On_Channel3_CC = 6,
    Timers_MasterMode_Trigger_On_Channel4_CC = 7,
} Timers_MasterMode_t;

typedef enum {
    Timers_SlaveMode_Disabled = 0,
    Timers_SlaveMode_EncoderMode_1 = (TIMERS_SMS_ENCODER_1_TI1FP2),
    Timers_SlaveMode_EncoderMode_2 = (TIMERS_SMS_ENCODER_2_TI2FP1),
    Timers_SlaveMode_EncoderMode_3 = (TIMERS_SMS_ENCODER_3_TI1FP1_TI1FP2),
    Timers_SlaveMode_CountOn_TI2FP1_EdgeOn_TI1FP2 = (Timers_SlaveMode_EncoderMode_1),
    Timers_SlaveMode_CountOn_TI1FP2_EdgeOn_TI2FP1 = (Timers_SlaveMode_EncoderMode_2),
    Timers_SlaveMode_CountOn_TI1FP1_and_TI2FP2_Edges_UpOrDownOn_TheOtherInputLevel = (Timers_SlaveMode_EncoderMode_3),
    Timers_SlaveMode_Reset_Mode = (TIMERS_SMS_RESET_ON_TRIGGER),
    Timers_SlaveMode_Gated_Mode = (TIMERS_SMS_GATED_COUNT_ON_HIGH_LEVEL),
    Timers_SlaveMode_Trigger_Mode = (TIMERS_SMS_TRIGGER_START),
    Timers_SlaveMode_ExternalClock1_Mode = (TIMERS_SMS_TRIGGER_IS_CLK),
} Timers_SlaveMode_t;

typedef enum {
    Timers_InternalTriggers_Timer1_Timer5_TRGO = (TIMERS_TS_ITR0),
    Timers_InternalTriggers_Timer1_Timer2_TRGO = (TIMERS_TS_ITR1),
    Timers_InternalTriggers_Timer1_Timer3_TRGO = (TIMERS_TS_ITR2),
    Timers_InternalTriggers_Timer1_Timer4_TRGO = (TIMERS_TS_ITR3),


    Timers_InternalTriggers_Timer8_Timer1_TRGO = (TIMERS_TS_ITR0),
    Timers_InternalTriggers_Timer8_Timer2_TRGO = (TIMERS_TS_ITR1),
    Timers_InternalTriggers_Timer8_Timer4_TRGO = (TIMERS_TS_ITR2),
    Timers_InternalTriggers_Timer8_Timer5_TRGO = (TIMERS_TS_ITR3),
} Timers_InternalTriggers_t;


typedef enum {
    Timers_Channel1InputSelection_CH1 = 0,
    Timers_Channel1InputSelection_XOR_CH1_CH2_CH3 = 1,
} Timers_Channel1InputSelection_t;


typedef enum {
    Timers_OutputIdleState_AfterDeadTime_LOW = 0,
    Timers_OutputIdleState_AfterDeadTime_HIGH = 1,
} Timers_OutputIdleState_t;

typedef enum {
    Timers_MasterSlaveSync_Off = (TIMERS_MSM_NO_ACTION),
    Timers_MasterSlaveSync_On = (TIMERS_MSM_DELAY_TO_SYNC),
} Timers_MasterSlaveSync_t;
typedef struct {

    union {
        struct {
            Timers_A_ClockSourceMode_t clockSourceMode: 3;
            const uint32_t              : 1;
            Timers_A_TriggerSourceMode_t triggerSourceMode: 3;
            Timers_A_SlavesSync_t slavesSync: 1;
            const uint32_t      : 0;

        };
        struct {
            Timers_SlaveMode_t slaveModeSelection: 3;
            const uint32_t : 1;
            Timers_InternalTriggers_t internalTriggers: 3;
            Timers_MasterSlaveSync_t masterSlaveSync: 1;
            Timers_A_ExternalTriggerFilterFreq_t filterFrequency: 4;
            Timers_A_ExternalTriggerPrescaller_t prescaller: 2;
            Timers_A_ExternalTriggerPinForce_t overrideTimerClockSource: 1;
            Timers_A_ExternalTriggerPolarity_t polarity: 1;
            const uint32_t      : 0;
        } ExternalTriggerPin;

    } ClockBasicConfigurations;


    struct {

        Timers_RunningState_t runImmediately: 1;
        Timers_A_UpdateEvent_t updateEvent: 1;
        Timers_A_UpdateEventSource_t updateEventSource: 1;
        Timers_A_OneShotMode_t oneShotMode: 1;
        Timers_A_CountingMode_t countingMode: 3;
        Timers_A_AutoReloadPreload_t autoReloadPreload: 1;
        const uint32_t          : 24;

        // TODO: Timers_A_Config Add CR2 Options


        uint16_t prescaller;
        uint16_t initialValue;
        uint16_t autoReload;
        uint16_t repetitions: 8;

    } BasicConfigurations;

    struct {
        Timers_CaptureCompare_PinsPreload_t pinsPreload: 1;
        const uint32_t : 1;
        Timers_CaptureCompare_UpdateSource_t preloadedPinsUpdateSource: 1;
        Timers_DMARequestTrigger_t dmaTriggerSource: 1; // DMA Options f
        Timers_MasterMode_t outputTriggerOn: 3;
        Timers_Channel1InputSelection_t channel1_input: 1;
        Timers_OutputIdleState_t output1_Normal_idleState: 1;
        Timers_OutputIdleState_t output1_Negative_idleState: 1;

        Timers_OutputIdleState_t output2_Normal_idleState: 1;
        Timers_OutputIdleState_t output2_Negative_idleState: 1;

        Timers_OutputIdleState_t output3_Normal_idleState: 1;
        Timers_OutputIdleState_t output3_Negative_idleState: 1;

        Timers_OutputIdleState_t output4_Normal_idleState: 1;
        Timers_OutputIdleState_t output4_Negative_idleState: 1;

    } CaptureCompareOptions;
    union {
        Timers_A_Interrupts_t interrupts: 8;
        struct {
            const uint32_t      : 8;
            Timers_A_DMARequests_t dmaRequests: 7;
            const uint32_t      : 0;
            // TODO: Timers_A_Config_t Complete DMAOptions
        } DMAOptions;
    };
} Timers_A_Config_t;


/**************	Section: Methods Declarations  **************/

Std_ReturnType HAL_TIMERS_A_Init(const Timers_A_TimerNumber_t timerNumber, const Timers_A_Config_t *config);

Std_ReturnType
HAL_TIMERS_A_ChannelInit(const Timers_A_ChannelNumber_t channelNumber, const Timers_A_Channel_Config_t *config);

Std_ReturnType
HAL_TIMERS_A_ChangeTimerState(const Timers_A_TimerNumber_t timerNumber, const Timers_RunningState_t state);

Std_ReturnType
HAL_TIMERS_A_ChangeChannelState(const Timers_A_ChannelNumber_t channelNumber, const Timers_A_ChannelState_t state);

Std_ReturnType HAL_TIMERS_A_ChangeAutoReloadValue(const Timers_A_TimerNumber_t timerNumber, const uint16_t value);

Std_ReturnType HAL_TIMERS_A_ChangeCounterValue(const Timers_A_TimerNumber_t timerNumber, const uint16_t value);

Std_ReturnType HAL_TIMERS_A_ReadCounterValue(const Timers_A_TimerNumber_t timerNumber, uint16_t *value);

Std_ReturnType HAL_TIMERS_A_ChangeCompareValue(const Timers_A_ChannelNumber_t channelNumber, const uint16_t value);

Std_ReturnType HAL_TIMERS_A_ReadCapturedValue(const Timers_A_ChannelNumber_t channelNumber, uint16_t *value);

Std_ReturnType
HAL_TIMERS_A_ChangePWM(const Timers_A_ChannelNumber_t channelNumber, const uint16_t frequency, const uint16_t duty);

Std_ReturnType HAL_TIMERS_A_ChangePWMDuty(const Timers_A_ChannelNumber_t channelNumber, const uint16_t duty);

Std_ReturnType HAL_TIMERS_A_Delay(const Timers_A_TimerNumber_t timerNumber, uint16_t delay);

uint16_t HAL_TIMERS_A_CalculateAutoReloadValue(uint32_t busFrequency, uint32_t requiredFreq, uint16_t requiredFreqScale,
                                               uint16_t prescaller, sint32_t *error);


Std_ReturnType HAL_TIMERS_A_getChannelRegisterAddress(Timers_A_ChannelNumber_t channelNumber, uint32_t *address);

Std_ReturnType HAL_TIMERS_ChannelCapture_toggleCaptureEdge(const Timers_A_ChannelNumber_t channelNumber);

Std_ReturnType HAL_TIMERS_ChannelCapture_toggleCaptureEdge_Fast(const Timers_A_ChannelNumber_t channelNumber);

Std_ReturnType
HAL_TIMERS_A_GPIO_Init(const Timers_A_TimerNumber_t timerNumber, const Timers_A_ChannelNumber_t channelNumber,
                       const Timers_A_Channel_Config_t *config);


Std_ReturnType
HAL_TIMERS_ChannelCapture_readCaptureValue(const Timers_A_ChannelNumber_t channelNumber, uint16_t *value);


Std_ReturnType
HAL_TIMERS_ChannelCapture_readCaptureValue_Fast(const Timers_A_ChannelNumber_t channelNumber, uint16_t *value);

Std_ReturnType HAL_TIMERS_ChannelCapture_setCaptureEdge_Fast(const Timers_A_ChannelNumber_t channelNumber,
                                                             Timers_CaptureMode_CaptureEdge_t edge);

Std_ReturnType HAL_TIMERS_ChannelCapture_setCaptureEdge(const Timers_A_ChannelNumber_t channelNumber,
                                                        Timers_CaptureMode_CaptureEdge_t edge);


Std_ReturnType HAL_TIMERS_A_registerInterruptCallback(InterruptCallback_t callback, Timers_A_Interrupts_t interruptID);


#endif //STM32_DRIVERS_TIMERS_A_H
