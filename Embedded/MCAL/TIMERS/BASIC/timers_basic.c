
#include "timers_basic.h"


/**************	Section: Includes *********************************/
/**************	Section: Local Variables Declarations *************/
/**************	Section: Local Methods Prototype Declarations *****/
/**************	Section: Methods Declarations *********************/

Std_ReturnType
HAL_TIMERS_BASIC_Init(const TIMERS_Basic_TimerNumber_t timerNumber, const TIMERS_Basic_Config_t *config) {
    Std_ReturnType ret = E_OK;

    if (((uint32_t) timerNumber > TIMERS_Basic_TimerNumber_7) || (config == NULL)) {
        ret = E_NOT_OK;
    } else {
        TIMERS_BASIC->Timers[timerNumber].timer.CR2.REG = CONVERT_TYPE_INDX(uint32_t, *config, 1);
        TIMERS_BASIC->Timers[timerNumber].timer.DIER.REG = CONVERT_TYPE_INDX(uint32_t, *config, 2);
        TIMERS_BASIC->Timers[timerNumber].timer.CNT.REG = config->initValue;
        TIMERS_BASIC->Timers[timerNumber].timer.ARR.REG = config->autoReload;
        TIMERS_BASIC->Timers[timerNumber].timer.PSC.REG = config->prescaller;
        TIMERS_BASIC->Timers[timerNumber].timer.CR1.REG = CONVERT_TYPE_INDX(uint32_t, *config, 0);
    }
    return ret;
}

Std_ReturnType
HAL_TIMERS_BASIC_ChangeState(const TIMERS_Basic_TimerNumber_t timerNumber, const Timers_RunningState_t state) {

    Std_ReturnType ret = E_OK;

    if (((uint32_t) timerNumber > TIMERS_Basic_TimerNumber_7)) {
        ret = E_NOT_OK;
    } else {
        TIMERS_BASIC->Timers[timerNumber].timer.CR1.CEN = state;
    }
    return ret;
}

Std_ReturnType
HAL_TIMERS_BASIC_ChangePrescaller(const TIMERS_Basic_TimerNumber_t timerNumber, const uint16_t prescaller) {

    Std_ReturnType ret = E_OK;

    if (((uint32_t) timerNumber > TIMERS_Basic_TimerNumber_7)) {
        ret = E_NOT_OK;
    } else {
        TIMERS_BASIC->Timers[timerNumber].timer.PSC.REG = prescaller;
    }
    return ret;
}

Std_ReturnType
HAL_TIMERS_BASIC_ChangeAutoReload(const TIMERS_Basic_TimerNumber_t timerNumber, const uint16_t autoreload) {
    Std_ReturnType ret = E_OK;

    if (((uint32_t) timerNumber > TIMERS_Basic_TimerNumber_7)) {
        ret = E_NOT_OK;
    } else {
        TIMERS_BASIC->Timers[timerNumber].timer.ARR.REG = autoreload;
    }
    return ret;
}


Std_ReturnType HAL_TIMERS_BASIC_TriggerUpdateEvent(const TIMERS_Basic_TimerNumber_t timerNumber) {
    Std_ReturnType ret = E_OK;

    if (((uint32_t) timerNumber > TIMERS_Basic_TimerNumber_7)) {
        ret = E_NOT_OK;
    } else {
        TIMERS_BASIC->Timers[timerNumber].timer.EGR.UG = STD_ON;
    }
    return ret;
}


static InterruptCallback_t interruptCallbacks[2] = {0};

Std_ReturnType HAL_TIMERS_BASIC_RegisterInterruptCallback(const TIMERS_Basic_TimerNumber_t timerNumber,
                                                          const InterruptCallback_t interruptCallback) {
    Std_ReturnType ret = E_OK;

    if (((uint32_t) timerNumber > TIMERS_Basic_TimerNumber_7)) {
        ret = E_NOT_OK;
    } else {
        interruptCallbacks[timerNumber] = interruptCallback;
    }
    return ret;
}

/**************	Section: Helper Methods Declarations  *************/


void TIM6_IRQHandler(void) {
    TIMERS_BASIC->Timers[TIMERS_Basic_TimerNumber_6].timer.SR.UIF = 1;
    if (interruptCallbacks[TIMERS_Basic_TimerNumber_6] != NULL) {
        interruptCallbacks[TIMERS_Basic_TimerNumber_6](INTERRUPTS_NO_PARAMS);
    }
}


void TIM7_IRQHandler(void) {
    TIMERS_BASIC->Timers[TIMERS_Basic_TimerNumber_7].timer.SR.UIF = 1;
    if (interruptCallbacks[TIMERS_Basic_TimerNumber_7] != NULL) {
        interruptCallbacks[TIMERS_Basic_TimerNumber_7](INTERRUPTS_NO_PARAMS);
    }
}