

#ifndef FLASH_H
#define FLASH_H

#include "std_types.h"
#include "stm32f103c8t.h"

void HAL_FLASH_WriteHalfWord(uint32_t Address, uint16_t Data);
uint32_t HAL_FLASH_isLocked(void);
uint32_t HAL_FLASH_Unlock(void);
Std_ReturnType HAL_FLASH_Lock(void);
Std_ReturnType HAL_FLASH_ErasePageNumber(uint32_t PageNumber, uint32_t numberOfPages);
Std_ReturnType HAL_FLASH_ErasePage(uint32_t PageAddress,uint32_t numberOfPages);
Std_ReturnType HAL_FLASH_EraseAll(uint8_t confirm);
Std_ReturnType HAL_FLASH_WriteProgram(uint32_t startAddress,uint8_t *program,uint32_t size);
Std_ReturnType HAL_FLASH_OptionByte_Lock(void);
uint16_t HAL_FLASH_ReadAddress(uint32_t address);


#endif //FLASH_H
