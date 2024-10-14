


#include "patterns.h"

Std_ReturnType Pattern_Init(Pattern_t *restrict patStruct, char *pattern, uint32_t patternSize) {
    Std_ReturnType ret = E_OK;

    // Init if wasn't
    if (patStruct == NULL) {
        patStruct = (Pattern_t *) malloc(sizeof(Pattern_t));
    }

    // Get Pattern sequence length
    uint32_t size = patternSize;
    if (patternSize == 0) {
        size = strlen(pattern);
    }
    // Assign Struct childes
    patStruct->pattern = (char *) malloc(size * sizeof(char));
    patStruct->size = size;

    // if malloc failed
    if (patStruct->pattern == NULL) {
        patStruct->size = 0;
        ret = E_NOT_OK;
    } else {
        strncpy(patStruct->pattern, pattern, size);
    }
    return ret;
}

Std_ReturnType Pattern_Add(PatternManager_t *manager, char *pattern, uint32_t patternSize, uint8_t newReserve) {
    Std_ReturnType ret = E_OK;

    if (newReserve) {
        // COPY and SO ON

        Pattern_t *newPatterns = (Pattern_t *) malloc(sizeof(Pattern_t) * (manager->count + 1));
        Pattern_t *oldPatterns = manager->patterns;

        if (newPatterns == NULL) {
            // fail to allocate memory
            return E_NOT_OK;
        }
        memcpy(newPatterns, oldPatterns, sizeof(Pattern_t) * (manager->count));
        manager->count++;
        manager->patterns = newPatterns;
        free(oldPatterns);
    }



    Pattern_Init(&manager->patterns[manager->count], pattern, patternSize);


    return ret;
}

Std_ReturnType PatternManager_Init(PatternManager_t *restrict manager, uint32_t patternsCount) {
    Std_ReturnType ret = E_OK;

    // Init if wasn't
    if (manager == NULL) {
        manager = (PatternManager_t *) malloc(sizeof(PatternManager_t));
    }

    // Reserve Required Patterns
    manager->patterns = (Pattern_t *) malloc(patternsCount * sizeof(Pattern_t));
    manager->count = patternsCount;

    if (manager->patterns == NULL) {
        manager->count = 0;
        ret = E_NOT_OK;
    }

    return ret;
}
