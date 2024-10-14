


#ifndef STM32_DRIVERS_TIMERS_GENERALPUPRPOSE_H
#define STM32_DRIVERS_TIMERS_GENERALPUPRPOSE_H


/**************	Section: Includes ***************************/

#include "std_types.h"
#include "stm32f103c8t.h"
#include "interrupts.h"
#include "timers.h"

/**************	Section: Macro Definitions Declarations *****/
/**************	Section: Macro Functions Declarations *******/
/**************	Section: Data Types Declarations ************/

typedef enum {
    TIMERS_GP_TimerNumber_2 = (0),
    TIMERS_GP_TimerNumber_3 = (1),
    TIMERS_GP_TimerNumber_4 = (2),

} TIMERS_GP_TimerNumber_t;

typedef enum {
    TIMERS_GP_TimerChannel_1 = (0),
    TIMERS_GP_TimerChannel_2 = (1),
    TIMERS_GP_TimerChannel_3 = (2),
    TIMERS_GP_TimerChannel_4 = (3),
} TIMERS_GP_TimerChannel_t;

typedef enum {
    TIMERS_GP_ChannelMode_OutputCompare,
    TIMERS_GP_ChannelMode_PWM,
    TIMERS_GP_ChannelMode_InputCapture,
    TIMERS_GP_ChannelMode_Disable
}TIMERS_GP_ChannelMode_t;

typedef struct {

} TIMERS_GP_Channel_Config_t;

typedef enum {
    TIMERS_GP_TimerMode_CountUP,
    TIMERS_GP_TimerMode_CountDown,
    TIMERS_GP_TimerMode_CenterAligned1,
    TIMERS_GP_TimerMode_CenterAligned2,
    TIMERS_GP_TimerMode_CenterAligned3,
} TIMERS_GP_TimerMode_t;

typedef enum {
    TIMERS_GP_TimerClockSrc_TI2F,
    TIMERS_GP_TimerClockSrc_TI1F,
    TIMERS_GP_TimerClockSrc_Triggers,
    TIMERS_GP_TimerClockSrc_ETRF,
    TIMERS_GP_TimerClockSrc_InternalClock,
} TIMERS_GP_TimerClockSrc_t;
typedef enum {
    TIMERS_GP_TriggerSelection_InternalTrigger0,
    TIMERS_GP_TriggerSelection_InternalTrigger1,
    TIMERS_GP_TriggerSelection_InternalTrigger2,
    TIMERS_GP_TriggerSelection_InternalTrigger3,
    TIMERS_GP_TriggerSelection_TI1_ED,
    TIMERS_GP_TriggerSelection_TI1FP1,
    TIMERS_GP_TriggerSelection_TI2FP2,
    TIMERS_GP_TriggerSelection_ETRF
}TIMERS_GP_TriggerSelection_t;

typedef enum {
    TIMERS_GP_TI2FEdge_Rising,
    TIMERS_GP_TI2FEdge_Falling,
} TIMERS_GP_TI2FEdge_t;

typedef enum {
    TIMERS_GP_InputCaptureFilter_
//    0000: No filter, sampling is done at fDTS
//    0001: fSAMPLING=fCK_INT, N=2
//    0010: fSAMPLING=fCK_INT, N=4
//    0011: fSAMPLING=fCK_INT, N=8
//    0100: fSAMPLING=fDTS/2, N=6
//    0101: fSAMPLING=fDTS/2, N=8
//    0110: fSAMPLING=fDTS/4, N=6
//    0111: fSAMPLING=fDTS/4, N=8
//    1000: fSAMPLING=fDTS/8, N=6
//    1001: fSAMPLING=fDTS/8, N=8
//    1010: fSAMPLING=fDTS/16, N=5
//    1011: fSAMPLING=fDTS/16, N=6
//    1100: fSAMPLING=fDTS/16, N=8
//    1101: fSAMPLING=fDTS/32, N=5
//    1110: fSAMPLING=fDTS/32, N=6
//    1111: fSAMPLING=fDTS/32, N=8
} TIMERS_GP_InputCaptureFilter_t;

typedef struct {
    TIMERS_GP_TimerMode_t mode;
    uint16_t prescaller;
    uint16_t initValue ;
    uint16_t autoReload;

    uint32_t onePulseMode   :1;

} TIMERS_GP_Config_t;

/**************	Section: Methods Declarations  **************/

Std_ReturnType HAL_TIMERS_GP_Init(const TIMERS_GP_TimerNumber_t timerNumber, const TIMERS_GP_Config_t *config);

Std_ReturnType
HAL_TIMERS_GP_InitChannel(const TIMERS_GP_TimerNumber_t timerNumber, const TIMERS_GP_Channel_Config_t *config);

Std_ReturnType HAL_TIMERS_GP_ChangeState(const TIMERS_GP_TimerNumber_t timerNumber, const Timers_RunningState_t state);

Std_ReturnType HAL_TIMERS_GP_Wait(const TIMERS_GP_TimerNumber_t timerNumber, uint16_t count);

Std_ReturnType HAL_TIMERS_GP_ChangePrescaller(const TIMERS_GP_TimerNumber_t timerNumber, const uint16_t prescaller);

Std_ReturnType HAL_TIMERS_GP_ChangeAutoReload(const TIMERS_GP_TimerNumber_t timerNumber, const uint16_t autoreload);

Std_ReturnType HAL_TIMERS_GP_PWM(const TIMERS_GP_TimerNumber_t timerNumber, const TIMERS_GP_TimerChannel_t channel,
                                 const uint16_t freq, const uint16_t duty);

#endif //STM32_DRIVERS_TIMERS_GENERALPUPRPOSE_H
