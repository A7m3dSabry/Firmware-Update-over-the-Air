

#ifndef SYSTICK_H
#define SYSTICK_H


/**************	Section: Includes ***************************/
#include "std_types.h"
#include "stm32f103c8t.h"
#include "interrupts.h"
#include "rcc.h"

/**************	Section: Macro Definitions Declarations *****/
/* SysTick is a 24 bit Timer, so it has max of (2^25 -1) but i used 2^25 only since the init function will subtract 1 */
#define SYSTICK_MAX  (1<<25)


/**************	Section: Macro Functions Declarations *******/
/**************	Section: Data Types Declarations ************/

typedef enum {

    SYSTICK_ClockSource_AHB = (pSTK_CLKSOURCE_AHB),
    SYSTICK_ClockSource_AHB_DIV_BY_8 = (pSTK_CLKSOURCE_AHB_DIV_BY_8)

}SYSTICK_ClockSource_t;

typedef enum {
    SYSTICK_Delay_Seconds = (1),
    SYSTICK_Delay_MilliSeconds = (1000),
    SYSTICK_Delay_MicroSeconds = (1000*1000)

} SYSTICK_Delay_t;
typedef struct {

    volatile struct {
        uint32_t startImmediately :1;
        uint32_t enableInterrupt :1;
        SYSTICK_ClockSource_t clkSource :1;
    }Options;
    uint32_t period;

} SysTick_Config_t;



/**************	Section: Methods Declarations  **************/

Std_ReturnType HAL_SYSTICK_Init(SysTick_Config_t *config);

void HAL_SYSTICK_Enable();
void HAL_SYSTICK_Disable();
void HAL_SYSTICK_InterruptEnable();
void HAL_SYSTICK_InterruptDisable();

void HAL_SYSTICK_PreloadSet(uint32_t preload);
uint32_t HAL_SYSTICK_ValueGet();
uint32_t HAL_SYSTICK_OverFlowed();


void HAL_SYSTICK_Delay(const uint32_t delay,const SYSTICK_Delay_t delay_type);

void HAL_SYSTICK_DeRegisterInterruptCallback();
Std_ReturnType HAL_SYSTICK_RegisterInterruptCallback(InterruptCallback_t callback);

#endif //SYSTICK_H
