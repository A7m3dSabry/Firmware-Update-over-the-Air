


/**************	Section: Includes *********************************/
#include "timers_advanced.h"


/**************	Section: Local Variables Declarations *************/
/**************	Section: Local Methods Prototype Declarations *****/
/**************	Section: Methods Declarations *********************/

Std_ReturnType HAL_TIMERS_A_Init(const Timers_A_TimerNumber_t timerNumber, const Timers_A_Config_t *config) {
    Std_ReturnType ret = E_OK;

    if (((uint32_t) timerNumber > Timers_A_TimerNumber_1) || (config == NULL)) {
        ret = E_NOT_OK;
    } else {

        pTIMER1->CR1.REG = 0; // Disable Timer and update disable option
        pTIMER1->SR.REG = 0;
        /* Wait Until Timer Stops for Safe Modification */
        WAIT_CONDITION_OR_TIMEOUT(pTIMER1->CR1.CEN == STD_OFF, TIMEOUT_INF);

        /* Clock Configurations __ NOTE: Using External Sources You must Configure The Channels Also */
        pTIMER1->SMCR.REG = CONVERT_TYPE(uint32_t, config->ClockBasicConfigurations);
        /* Configure Prescaller */
        pTIMER1->PSC.REG = config->BasicConfigurations.prescaller;
        /* Configure AutoReload Value __ Also Known as Max Value */
        pTIMER1->ARR.REG = config->BasicConfigurations.autoReload;
        /* Configure Counter Initial Value */
        pTIMER1->CNT.REG = config->BasicConfigurations.initialValue;
        /* Configure Repetition Counter */
        pTIMER1->RCR.REG = config->BasicConfigurations.repetitions;

        /* DMA Options struct is union with interrupts*/
        pTIMER1->DIER.REG = CONVERT_TYPE(uint32_t, config->DMAOptions);

        pTIMER1->CR1.REG = CONVERT_TYPE_INDX(uint32_t, config->BasicConfigurations, 1);
        pTIMER1->CR2.REG = CONVERT_TYPE(uint16_t, config->CaptureCompareOptions);

        pTIMER1->EGR.UG = 1;
        pTIMER1->CR1.REG = CONVERT_TYPE_INDX(uint32_t, config->BasicConfigurations, 0);

    }
    return ret;
}


Std_ReturnType
HAL_TIMERS_ChannelCapture_readCaptureValue(const Timers_A_ChannelNumber_t channelNumber, uint16_t *value) {

    Std_ReturnType ret = E_OK;

    if (value == NULL) {
        ret = E_NOT_OK;
    } else {
        *value = pTIMER1->All_CCRs[channelNumber].CC;
    }
    return ret;
}

Std_ReturnType
HAL_TIMERS_ChannelCapture_readCaptureValue_Fast(const Timers_A_ChannelNumber_t channelNumber, uint16_t *value) {


    *value = pTIMER1->All_CCRs[channelNumber].CC;

    return E_OK;
}

Std_ReturnType HAL_TIMERS_ChannelCapture_setCaptureEdge_Fast(const Timers_A_ChannelNumber_t channelNumber,
                                                             Timers_CaptureMode_CaptureEdge_t edge) {
    FORCE_BIT(pTIMER1->CCER.REG, (4 * (uint32_t) channelNumber) + 1, (uint32_t) edge);
    return E_OK;
}

Std_ReturnType HAL_TIMERS_ChannelCapture_setCaptureEdge(const Timers_A_ChannelNumber_t channelNumber,
                                                        Timers_CaptureMode_CaptureEdge_t edge) {
    Std_ReturnType ret = E_OK;

    if (((uint32_t) channelNumber > Timers_A_ChannelNumber_4) ||
        ((uint32_t) edge > Timers_CaptureMode_CaptureEdge_Falling)) {
        ret = E_NOT_OK;
    } else {

        FORCE_BIT(pTIMER1->CCER.REG, (4 * (uint32_t) channelNumber) + 1, (uint32_t) edge);

    }
    return ret;
}


Std_ReturnType HAL_TIMERS_ChannelCapture_toggleCaptureEdge(const Timers_A_ChannelNumber_t channelNumber) {
    Std_ReturnType ret = E_OK;

    if (((uint32_t) channelNumber > Timers_A_ChannelNumber_4)) {
        ret = E_NOT_OK;
    } else {

        TOGGLE_BIT(pTIMER1->CCER.REG, (4 * (uint32_t) channelNumber) + 1);

    }
    return ret;

}

Std_ReturnType HAL_TIMERS_ChannelCapture_toggleCaptureEdge_Fast(const Timers_A_ChannelNumber_t channelNumber) {


    TOGGLE_BIT(pTIMER1->CCER.REG, (4 * (uint32_t) channelNumber) + 1);

    return E_NOT_OK;
}

Std_ReturnType
HAL_TIMERS_A_ChannelInit(const Timers_A_ChannelNumber_t channelNumber, const Timers_A_Channel_Config_t *config) {

    Std_ReturnType ret = E_OK;

    if (((uint32_t) channelNumber > Timers_A_ChannelNumber_4) || (config == NULL)) {
        ret = E_NOT_OK;
    } else {

        /* Stop Channel and it's Complementary*/
        CLEAR_MASK(pTIMER1->CCER.REG, 0b101 << (channelNumber * 4));
        /* Wait for Channel To Stop for Safe Modification */
        //  WAIT_CONDITION_OR_TIMEOUT(READ_BIT(pTIMER1->CCER.REG, 1 << (channelNumber * 4)) == 1, TIMEOUT_INF);

        /* Configure Channel Configurations */
        pTIMER1->ALL_CCMR[channelNumber].CCM = CONVERT_TYPE(uint32_t, config->Options);
        /* Configure Channel CaptureCompare Register*/
        pTIMER1->All_CCRs[channelNumber].REG = config->captureCompareValue;
        pTIMER1->CCER.REG |= 1 << (channelNumber * 4);

        switch (config->Options.mode) {

            case Timers_A_CaptureCompareSelection_CompareMode:
                pTIMER1->BDTR.MOE = 1;
                break;
            case Timers_A_CaptureCompareSelection_Capture_Same_TIFxP:
            case Timers_A_CaptureCompareSelection_Capture_Alternate_TIFxP:
                /* Enable Capture Compare Mode */
                FORCE_BIT(pTIMER1->CCER.REG, 4 * (uint32_t) channelNumber, STD_ON);

                /* Set Polarity */
                FORCE_BIT(pTIMER1->CCER.REG, (4 * (uint32_t) channelNumber) + 1,
                          config->Options.CaptureOptions.captureEdge);
                break;
            case Timers_A_CaptureCompareSelection_Capture_TRC:


                break;

        }


        pTIMER1->EGR.UG = 1;


    }
    return ret;
}

Std_ReturnType
HAL_TIMERS_A_ChangeTimerState(const Timers_A_TimerNumber_t timerNumber, const Timers_RunningState_t state) {
    Std_ReturnType ret = E_OK;

    if (((uint32_t) timerNumber > Timers_A_TimerNumber_1)) {
        ret = E_NOT_OK;
    } else {
        pTIMER1->CR1.CEN = state;
    }
    return ret;

}

Std_ReturnType
HAL_TIMERS_A_ChangeChannelState(const Timers_A_ChannelNumber_t channelNumber, const Timers_A_ChannelState_t state) {
    Std_ReturnType ret = E_OK;

    if (((uint32_t) channelNumber > Timers_A_ChannelNumber_4)) {
        ret = E_NOT_OK;
    } else {

        FORCE_MASK(pTIMER1->CCER.REG, 0b101 << channelNumber, state | state << 2);

    }
    return ret;
}

Std_ReturnType HAL_TIMERS_A_ChangeAutoReloadValue(const Timers_A_TimerNumber_t timerNumber, const uint16_t value) {
    Std_ReturnType ret = E_OK;

    if (((uint32_t) timerNumber > Timers_A_TimerNumber_1)) {
        ret = E_NOT_OK;
    } else {
        pTIMER1->ARR.REG = value;
    }
    return ret;

}

Std_ReturnType HAL_TIMERS_A_ChangeCounterValue(const Timers_A_TimerNumber_t timerNumber, const uint16_t value) {
    Std_ReturnType ret = E_OK;

    if (((uint32_t) timerNumber > Timers_A_TimerNumber_1)) {
        ret = E_NOT_OK;
    } else {
        pTIMER1->CNT.REG = value;
    }
    return ret;
}

Std_ReturnType HAL_TIMERS_A_ReadCounterValue(const Timers_A_TimerNumber_t timerNumber, uint16_t *value) {
    Std_ReturnType ret = E_OK;

    if (((uint32_t) timerNumber > Timers_A_TimerNumber_1)) {
        ret = E_NOT_OK;
    } else {
        *value = pTIMER1->CNT.REG;
    }
    return ret;
}


Std_ReturnType HAL_TIMERS_A_ChangeCompareValue(const Timers_A_ChannelNumber_t channelNumber, const uint16_t value) {
    Std_ReturnType ret = E_OK;

    if (((uint32_t) channelNumber > Timers_A_ChannelNumber_4)) {
        ret = E_NOT_OK;
    } else {
        pTIMER1->All_CCRs[channelNumber].REG = value;
    }
    return ret;
}

Std_ReturnType HAL_TIMERS_A_ReadCapturedValue(const Timers_A_ChannelNumber_t channelNumber, uint16_t *value) {
    Std_ReturnType ret = E_OK;

    if (((uint32_t) channelNumber > Timers_A_ChannelNumber_4)) {
        ret = E_NOT_OK;
    } else {
        *value = pTIMER1->All_CCRs[channelNumber].REG;
    }
    return ret;
}

Std_ReturnType
HAL_TIMERS_A_ChangePWM(const Timers_A_ChannelNumber_t channelNumber, const uint16_t frequency, const uint16_t duty) {
    Std_ReturnType ret = E_OK;

    if (((uint32_t) channelNumber > Timers_A_ChannelNumber_4)) {
        ret = E_NOT_OK;
    } else {
        pTIMER1->ARR.REG = frequency;
        pTIMER1->All_CCRs[channelNumber].REG = duty;
    }
    return ret;
}

Std_ReturnType HAL_TIMERS_A_ChangePWMDuty(const Timers_A_ChannelNumber_t channelNumber, const uint16_t duty) {
    Std_ReturnType ret = E_OK;

    if (((uint32_t) channelNumber > Timers_A_ChannelNumber_4)) {
        ret = E_NOT_OK;
    } else {
        pTIMER1->All_CCRs[channelNumber].REG = duty;
    }
    return ret;
}

Std_ReturnType HAL_TIMERS_A_Delay(const Timers_A_TimerNumber_t timerNumber, uint16_t delay) {
    Std_ReturnType ret = E_OK;

    if (((uint32_t) timerNumber > Timers_A_TimerNumber_1)) {
        ret = E_NOT_OK;
    } else {

        pTIMER1->ARR.REG = delay + 2; // Setting delay + 2 just in case
        pTIMER1->CR1.OPM = TIMERS_BASIC_OPM_ENABLE;
        pTIMER1->CR1.CEN = TIMERS_CEN_ENABLE;
        WAIT_CONDITION_OR_TIMEOUT_M(pTIMER1->SR.UIF == TIMERS_UIF_ON, delay);
    }
    return ret;
}


Std_ReturnType
HAL_TIMERS_A_GPIO_Init(const Timers_A_TimerNumber_t timerNumber, const Timers_A_ChannelNumber_t channelNumber,
                       const Timers_A_Channel_Config_t *config) {
    Std_ReturnType ret = E_OK;

    if ((timerNumber > Timers_A_TimerNumber_1) || (channelNumber > Timers_A_ChannelNumber_4) || (config == NULL)) {
        ret = E_NOT_OK;
    } else {
        // TODO: Timers Advanced, implement auto gpio init for capture,compare

    }
    return ret;
}


uint16_t HAL_TIMERS_A_CalculateAutoReloadValue(uint32_t busFrequency, uint32_t requiredFreq, uint16_t requiredFreqScale,
                                               uint16_t prescaller, sint32_t *error) {

    uint16_t ret = 0;
    if ((busFrequency != 0) && (requiredFreq != 0) && (prescaller != 0)) {
        ret = (busFrequency * requiredFreqScale) / (prescaller * requiredFreq);
        if (error != NULL) {
            *error = (sint32_t) requiredFreq - (sint32_t) ((ret * prescaller * requiredFreq) / busFrequency);
        }
    }

    return ret;
}


Std_ReturnType HAL_TIMERS_A_getChannelRegisterAddress(Timers_A_ChannelNumber_t channelNumber,uint32_t *address) {

    Std_ReturnType ret = E_OK;

    if (address == NULL) {
        ret = E_NOT_OK;
    } else {
        switch (channelNumber) {

            case Timers_A_ChannelNumber_1:
                *address = (uint32_t) &pTIMER1->CCR1.REG;
                break;
            case Timers_A_ChannelNumber_2:
                *address = (uint32_t) &pTIMER1->CCR2.REG;
                break;
            case Timers_A_ChannelNumber_3:
                *address = (uint32_t) &pTIMER1->CCR3.REG;
                break;
            case Timers_A_ChannelNumber_4:
                *address = (uint32_t) &pTIMER1->CCR4.REG;
                break;
        }
    }
    return ret;

}


static InterruptCallback_t TIMERS_callbacks[8] = {0};

Std_ReturnType HAL_TIMERS_A_registerInterruptCallback(InterruptCallback_t callback, Timers_A_Interrupts_t interruptID) {

    switch (interruptID) {

        case Timers_A_Interrupts_UpdateInterrupt:
            TIMERS_callbacks[0] = callback;
            break;
        case Timers_A_Interrupts_CaptureCompare_1:
            TIMERS_callbacks[1] = callback;
            break;
        case Timers_A_Interrupts_CaptureCompare_2:
            TIMERS_callbacks[2] = callback;
            break;
        case Timers_A_Interrupts_CaptureCompare_3:
            TIMERS_callbacks[3] = callback;
            break;
        case Timers_A_Interrupts_CaptureCompare_4:
            TIMERS_callbacks[4] = callback;
            break;
        case Timers_A_Interrupts_COMInterrupt:
            TIMERS_callbacks[5] = callback;
            break;
        case Timers_A_Interrupts_TriggerInterrupt:
            TIMERS_callbacks[6] = callback;
            break;
        case Timers_A_Interrupts_BreakInterrupt:
            TIMERS_callbacks[7] = callback;
            break;
    }

    return E_OK;
}

/**************	Section: Helper Methods Declarations  *************/

void TIM1_CC_IRQHandler(void) {

    if (pTIMER1->SR.CC1IF == STD_ON) {
        /* Clear Flag to prevent looping in interrupts */
        pTIMER1->SR.CC1IF = STD_OFF;

        /* Calling the Interrupt Registered Callback if Valid */
        if (TIMERS_callbacks[1] != NULL) {
            TIMERS_callbacks[1](0);
        }
    } else if (pTIMER1->SR.CC2IF == STD_ON) {

        /* Clear Flag to prevent looping in interrupts */
        pTIMER1->SR.CC2IF = STD_OFF;

        /* Calling the Interrupt Registered Callback if Valid */
        if (TIMERS_callbacks[2] != NULL) {
            TIMERS_callbacks[2](1);
        }
    } else if (pTIMER1->SR.CC3IF == STD_ON) {

        /* Clear Flag to prevent looping in interrupts */
        pTIMER1->SR.CC3IF = STD_OFF;

        /* Calling the Interrupt Registered Callback if Valid */
        if (TIMERS_callbacks[3] != NULL) {
            TIMERS_callbacks[3](2);
        }
    } else if (pTIMER1->SR.CC4IF == STD_ON) {

        /* Clear Flag to prevent looping in interrupts */
        pTIMER1->SR.CC4IF = STD_OFF;

        /* Calling the Interrupt Registered Callback if Valid */
        if (TIMERS_callbacks[4] != NULL) {
            TIMERS_callbacks[4](3);
        }

        // TODO: Where is the TIF ISR????
    } else if (pTIMER1->SR.TIF == STD_ON) {

        /* Clear Flag to prevent looping in interrupts */
        pTIMER1->SR.TIF = STD_OFF;

        /* Calling the Interrupt Registered Callback if Valid */
        if (TIMERS_callbacks[6] != NULL) {
            TIMERS_callbacks[6](Timers_A_Interrupts_TriggerInterrupt);
        }
    }
}

void TIM1_BRK_IRQHandler(void) {

    if (TIMERS_callbacks[6] != NULL) {
        TIMERS_callbacks[6](Timers_A_Interrupts_BreakInterrupt);
    }
}

void TIM1_TRG_COM_IRQHandler(void) {

    if (TIMERS_callbacks[5] != NULL) {
        TIMERS_callbacks[5](Timers_A_Interrupts_COMInterrupt);
    }

}

void TIM1_UP_IRQHandler(void) {

    /* Clear Flag to prevent looping in interrupts */
    pTIMER1->SR.UIF = STD_OFF;

    /* Calling the Interrupt Registered Callback if Valid */
    if (TIMERS_callbacks[0] != NULL) {
        TIMERS_callbacks[0](INTERRUPTS_NO_PARAMS);
    }

}
