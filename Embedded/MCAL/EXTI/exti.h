
#ifndef STM32_DRIVERS_EXTI_H
#define STM32_DRIVERS_EXTI_H

/**************	Section: Includes ***************************/
#include "std_types.h"
#include "stm32f103c8t.h"
#include "interrupts.h"

/**************	Section: Macro Definitions Declarations *****/
/**************	Section: Macro Functions Declarations *******/
/**************	Section: Data Types Declarations ************/

typedef enum {
    EXTILine_0 = (0),
    EXTILine_1 = (1),
    EXTILine_2 = (2),
    EXTILine_3 = (3),
    EXTILine_4 = (4),
    EXTILine_5 = (5),
    EXTILine_6 = (6),
    EXTILine_7 = (7),
    EXTILine_8 = (8),
    EXTILine_9 = (9),
    EXTILine_10 = (10),
    EXTILine_11 = (11),
    EXTILine_12 = (12),
    EXTILine_13 = (13),
    EXTILine_14 = (14),
    EXTILine_15 = (15),
    EXTILine_16 = (16),
    EXTILine_17 = (17),
    EXTILine_18 = (18),
    EXTILine_19 = (19),

    EXTILine_PX0 = (EXTILine_0),
    EXTILine_PX1 = (EXTILine_1),
    EXTILine_PX2 = (EXTILine_2),
    EXTILine_PX3 = (EXTILine_3),
    EXTILine_PX4 = (EXTILine_4),
    EXTILine_PX5 = (EXTILine_5),
    EXTILine_PX6 = (EXTILine_6),
    EXTILine_PX7 = (EXTILine_7),
    EXTILine_PX8 = (EXTILine_8),
    EXTILine_PX9 = (EXTILine_9),
    EXTILine_PX10 = (EXTILine_10),
    EXTILine_PX11 = (EXTILine_11),
    EXTILine_PX12 = (EXTILine_12),
    EXTILine_PX13 = (EXTILine_13),
    EXTILine_PX14 = (EXTILine_14),
    EXTILine_PX15 = (EXTILine_15),
    EXTILine_PVD = (EXTILine_16),
    EXTILine_RTC_AlarmEvent = (EXTILine_17),
    EXTILine_USB_WakeUpEvent = (EXTILine_18),
    EXTILine_ETH_WakeUpEvent = (EXTILine_19),





}EXTILine_t;



typedef enum {
    EXTILineType_None = (0),
    EXTILineType_Event = (1),
    EXTILineType_Interrupt = (2),
    EXTILineType_InterruptAndEvent = (3)
}EXTILineType_t;

typedef enum{
    EXTIEdgeType_NoEdgeDetection = (0),
    EXTIEdgeType_Rising = (1),
    EXTIEdgeType_Falling = (2),
    EXTIEdgeType_RisingAndFalling = (3),
}EXTIEdgeType_t;


typedef enum {
    EXTILinePendingState_NOT_Pending = (0),
    EXTILinePendingState_Pending = (1),

}EXTILinePendingState_t;


typedef enum {
    EXTI_0 = (0),
    EXTI_1 = (1),
    EXTI_2 = (2),
    EXTI_3 = (3),
    EXTI_4 = (4),
    EXTI_9_5 = (5),
    EXTI_15_10 = (6)
}EXTIInterruptLines_t;
/**************	Section: Methods Declarations  **************/

Std_ReturnType HAL_EXTI_ChangeLineState(const EXTILine_t line,const EXTILineType_t type);
Std_ReturnType HAL_EXTI_ChangeLineEdgeDetection(const EXTILine_t line, const EXTIEdgeType_t edgeType);


//Std_ReturnType HAL_EXTI_TriggerSoftwareInterruptEvent(const EXTILine_t line);

Std_ReturnType HAL_EXTI_ReadLinePendingState(const EXTILine_t line, EXTILinePendingState_t *state);
Std_ReturnType HAL_EXTI_ChangeLinePendingState(const EXTILine_t line, const EXTILinePendingState_t state);



Std_ReturnType HAL_EXTI_RegisterInterruptCallback(const EXTIInterruptLines_t line, InterruptCallback_t handler);


#endif //STM32_DRIVERS_EXTI_H
