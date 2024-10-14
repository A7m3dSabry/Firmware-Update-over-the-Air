
#ifndef STM32_DRIVERS_DELAY_H
#define STM32_DRIVERS_DELAY_H

#include "std_types.h"
#include "stm32f103c8t.h"
#include "rcc.h"

void HAL_Delay_us(uint32_t delay);
void HAL_Delay_ms(uint32_t delay);
#endif //STM32_DRIVERS_DELAY_H
