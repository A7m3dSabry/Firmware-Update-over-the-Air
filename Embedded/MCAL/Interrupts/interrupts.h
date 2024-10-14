
#ifndef STM32_DRIVERS_INTERRUPTS_H
#define STM32_DRIVERS_INTERRUPTS_H

/**************	Section: Includes ***************************/
#include "std_types.h"

/**************	Section: Macro Definitions Declarations *****/
#define INTERRUPTS_NO_PARAMS        (0xFFFFFFFFUL)
/**************	Section: Macro Functions Declarations *******/
/**************	Section: Data Types Declarations ************/
typedef void (*InterruptCallback_t)(uint32_t param);
/**************	Section: Methods Declarations  **************/


#endif //STM32_DRIVERS_INTERRUPTS_H
