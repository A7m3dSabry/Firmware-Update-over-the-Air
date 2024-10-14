
#ifndef STM32_DRIVERS_TIMERS_BASIC_H
#define STM32_DRIVERS_TIMERS_BASIC_H


/**************	Section: Includes ***************************/
#include "std_types.h"
#include "interrupts.h"
#include "stm32f103c8t.h"
#include "timers.h"

/**************	Section: Macro Definitions Declarations *****/
/**************	Section: Macro Functions Declarations *******/
/**************	Section: Data Types Declarations ************/


typedef enum {
    TIMERS_Basic_UpdateEvent_EnableUpdateEvent = (TIMERS_BASIC_UDIS_ENABLE_UPDATES),
    TIMERS_Basic_UpdateEvent_DisableUpdateEvent = (TIMERS_BASIC_UDIS_DISABLE_UPDATES),

} TIMERS_Basic_UpdateEvent_t;

typedef enum {
    TIMERS_Basic_UpdateRequestSource_Counter_UG_SlaveMode = (TIMERS_BASIC_URS_ALL),
    TIMERS_Basic_UpdateRequestSource_Counter_Only = (TIMERS_BASIC_URS_ONLY_COUNTER),
} TIMERS_Basic_UpdateRequestSource_t;

typedef enum {
    TIMERS_Basic_CountingMode_Continous = (TIMERS_BASIC_OPM_DISABLE),
    TIMERS_Basic_CountingMode_OneShot = (TIMERS_BASIC_OPM_ENABLE),
} TIMERS_Basic_CountingMode_t;

typedef enum {
    TIMERS_Basic_AutoReloadRegBuffer_Enable = (TIMERS_BASIC_ARPE_BUFFER_ENABLE),
    TIMERS_Basic_AutoReloadRegBuffer_Disable = (TIMERS_BASIC_ARPE_BUFFER_DISABLE),
} TIMERS_Basic_AutoReloadRegBuffer_t;


typedef enum {
    TIMERS_Basic_MasterModeSelection_Reset = (TIMERS_BASIC_MMS_RESET),
    TIMERS_Basic_MasterModeSelection_Enable = (TIMERS_BASIC_MMS_ENABLE),
    TIMERS_Basic_MasterModeSelection_Update = (TIMERS_BASIC_MMS_UPDATE),
} TIMERS_Basic_MasterModeSelection_t;

typedef enum {
    TIMERS_Basic_UpdateInterrupt_Enable = (TIMERS_BASIC_UIE_ENABLE),
    TIMERS_Basic_UpdateInterrupt_Disable = (TIMERS_BASIC_UIE_DISABLE),
} TIEMRS_Basic_UpdateInterrupt_t;

typedef enum {
    TIEMRS_Basic_DMAOnEvent_Enable = (TIMERS_BASIC_UDE_ENABLE),
    TIEMRS_Basic_DMAOnEvent_Disable = (TIMERS_BASIC_UDE_DISABLE),
} TIEMRS_Basic_DMAOnEvent_t;
typedef enum {
    TIMERS_Basic_TimerNumber_6 = (0),
    TIMERS_Basic_TimerNumber_7 = (1)
} TIMERS_Basic_TimerNumber_t;
typedef struct {
    struct {
        Timers_RunningState_t runImmediately;
        TIMERS_Basic_UpdateEvent_t updateEvent: 1;
        TIMERS_Basic_UpdateRequestSource_t updateRequestSource: 1;
        TIMERS_Basic_CountingMode_t countingMode: 1;
        const uint32_t                  : 3;
        TIMERS_Basic_AutoReloadRegBuffer_t autoReloadRegBuffer: 1;
    };

    struct {
        const uint32_t      : 4;
        TIMERS_Basic_MasterModeSelection_t masterModeSelection: 3;
    };
    struct {
        TIEMRS_Basic_UpdateInterrupt_t interrupt: 1;
        const uint32_t : 6;
        TIEMRS_Basic_DMAOnEvent_t dmaOnEvent: 1;
    };

    uint16_t prescaller;
    uint16_t autoReload;
    uint16_t initValue;

} TIMERS_Basic_Config_t;


/**************	Section: Methods Declarations  **************/
Std_ReturnType HAL_TIMERS_BASIC_Init(const TIMERS_Basic_TimerNumber_t timerNumber, const TIMERS_Basic_Config_t *config);

Std_ReturnType HAL_TIMERS_BASIC_ChangeState(const TIMERS_Basic_TimerNumber_t timerNumber, const Timers_RunningState_t state);

Std_ReturnType
HAL_TIMERS_BASIC_ChangePrescaller(const TIMERS_Basic_TimerNumber_t timerNumber, const uint16_t prescaller);

Std_ReturnType
HAL_TIMERS_BASIC_ChangeAutoReload(const TIMERS_Basic_TimerNumber_t timerNumber, const uint16_t autoreload);

Std_ReturnType  HAL_TIMERS_BASIC_TriggerUpdateEvent(const TIMERS_Basic_TimerNumber_t timerNumber);

Std_ReturnType HAL_TIMERS_BASIC_RegisterInterruptCallback(const TIMERS_Basic_TimerNumber_t timerNumber, const InterruptCallback_t interruptCallback);

#endif //STM32_DRIVERS_TIMERS_BASIC_H
