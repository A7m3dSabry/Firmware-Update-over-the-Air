


#include "delay.h"


void delay_us (unsigned long delay){
    for (unsigned long counter = 0 ; counter < (delay / 2) ; counter ++);
}

void delay_ms(unsigned long delay){
    delay_us(delay * 1000);
}