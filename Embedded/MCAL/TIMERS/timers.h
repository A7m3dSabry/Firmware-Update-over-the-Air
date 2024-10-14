
#ifndef STM32_DRIVERS_TIMERS_H
#define STM32_DRIVERS_TIMERS_H

/**************	Section: Includes ***************************/
#include "std_types.h"
//#include "timers_basic.h"
//#include "timers_generalpuprpose.h"
//#include "timers_advanced.h"

/**************	Section: Macro Definitions Declarations *****/
/**************	Section: Macro Functions Declarations *******/
/**************	Section: Data Types Declarations ************/

typedef enum {
    TIMERS_RunningState_ON = (TIMERS_BASIC_CEN_ENABLE),
    TIMERS_RunningState_OFF = (TIMERS_BASIC_CEN_DISABLE),
} Timers_RunningState_t;

/**************	Section: Methods Declarations  **************/


#endif //STM32_DRIVERS_TIMERS_H
