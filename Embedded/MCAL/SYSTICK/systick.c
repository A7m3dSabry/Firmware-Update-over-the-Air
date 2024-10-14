
#include "systick.h"




Std_ReturnType HAL_SYSTICK_Init(SysTick_Config_t *config){
    Std_ReturnType ret = E_OK;
    if (NULL == config){
        ret = E_NOT_OK;
    } else {
        if (0 == config->period) {
            ret = E_NOT_OK;
        } else {
            pSTK->CTRL.ENABLE = pSTK_ENABLE_OFF;
            pSTK->VAL.REG = 0;
            pSTK->LOAD.RELOAD = config->period -1;
            pSTK->CTRL.REG = CONVERT_TYPE(uint32_t,config->Options);
        }
    }
    return ret;
}


void HAL_SYSTICK_Enable(){
    pSTK->CTRL.ENABLE = STD_HIGH;
}
void HAL_SYSTICK_Disable(){
    pSTK->CTRL.ENABLE = STD_LOW;
}


void HAL_SYSTICK_InterruptEnable(){
    pSTK->CTRL.TICKINT = STD_HIGH;

}
void HAL_SYSTICK_InterruptDisable(){
    pSTK->CTRL.TICKINT = STD_LOW;
}

void HAL_SYSTICK_PreloadSet(uint32_t preload){
    pSTK->LOAD.RELOAD = preload;
}
uint32_t HAL_SYSTICK_ValueGet(){
    return pSTK->VAL.REG;
}

uint32_t HAL_SYSTICK_OverFlowed(){
    return pSTK->CTRL.COUNTFLAG;
}

static InterruptCallback_t systick_callback = NULL;

/**
 *
 * @param callback
 * @return
 */
Std_ReturnType HAL_SYSTICK_RegisterInterruptCallback(InterruptCallback_t callback){
    Std_ReturnType ret = E_OK;
    if (NULL == callback){
        ret= E_NOT_OK;
    }
    systick_callback = callback;
    return ret;
}

void HAL_SYSTICK_DeRegisterInterruptCallback(){
    systick_callback = NULL;
}


void HAL_SYSTICK_Delay(const uint32_t delay,const SYSTICK_Delay_t delay_type){

    if ((delay_type != SYSTICK_Delay_Seconds) && (delay_type != SYSTICK_Delay_MilliSeconds) && (delay_type != SYSTICK_Delay_MicroSeconds)) {
        return;
    } else {


        /* Calculate Required Wait Ticks */
        uint64_t wait = delay * System_PeripheralsClock.AHB/ delay_type;

        /* Return if The Required Wait Ticks Not Achievable Because Clock is Lower */
        if (0 != wait){
            /* Initialize Config Sturct */
            SysTick_Config_t config = {0};
            /* Config Timer to in Init Function Start Immediately */
            config.Options.startImmediately = STD_HIGH;
            config.Options.clkSource = SYSTICK_ClockSource_AHB;
            /* Extend Timer Capability to Support uint64 values */
            /* Even in The Max Frequency (72,000,000 HZ) it will support about 8124 Years as MAX */
            uint32_t counter = wait / SYSTICK_MAX;
            uint32_t remain = wait % SYSTICK_MAX;
            /* Start Delaying */
            if (0 != counter ){
                config.period = SYSTICK_MAX;
                HAL_SYSTICK_Init(&config);
                for (uint32_t i = 0 ; i < counter ; i++){

                    while (pSTK->CTRL.COUNTFLAG == STD_LOW){ /* DO NOTHING */};
                }
            }
            /* Delay The Remaining Part (which is lower than the max of the timer) */
            if (0 != remain){
                config.period = remain;
                HAL_SYSTICK_Init(&config);
                while (pSTK->CTRL.COUNTFLAG == STD_LOW){ /* DO NOTHING */};
            }
        }
        /* Disable Timer */
        pSTK->CTRL.ENABLE = pSTK_ENABLE_OFF;


    }
}

//void SysTick_Handler(void){
//    if (NULL != systick_callback){
//        systick_callback(0);
//    }
//}

