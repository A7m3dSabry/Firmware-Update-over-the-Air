
#ifndef STM32_DRIVERS_PATTERNS_H
#define STM32_DRIVERS_PATTERNS_H


#include "std_types.h"
//#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>


//typedef char* charPattern_t;

typedef struct {
    uint32_t size;
    char *pattern;
} Pattern_t;

typedef struct {
    uint32_t count;
    Pattern_t *patterns;
} PatternManager_t;


Std_ReturnType Pattern_Init(Pattern_t *restrict patStruct, char *pattern, uint32_t patternSize);

Std_ReturnType PatternManager_Init(PatternManager_t *restrict manager, uint32_t patternsCount);

Std_ReturnType Pattern_Add(PatternManager_t *manager, char *pattern, uint32_t patternSize, uint8_t newReserve);

#endif //STM32_DRIVERS_PATTERNS_H
