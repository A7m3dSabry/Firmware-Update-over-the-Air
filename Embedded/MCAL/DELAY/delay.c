
#include "delay.h"


//  __attribute__((optimize("O0")))


void  HAL_Delay_us(uint32_t delay){
// Maximum is 500 us

    uint64_t counter =( (System_PeripheralsClock.AHB * delay) / (11*1000000) );
    while ((counter--) != 0){
        /* Do Nothing */
    }

}
void   HAL_Delay_ms(uint32_t delay){
	delay *=2;
	while (delay--)
		HAL_Delay_us(500);
}
