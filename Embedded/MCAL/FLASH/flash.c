
#include "flash.h"






uint32_t HAL_FLASH_isLocked(void){
    /* Return Lock State */
    return READ_BIT(pFLASH->CR.REG , FLASH_LOCK_POS);
}

uint32_t HAL_FLASH_Unlock(void){

    /* Check if FLASH is Already UnLocked */
    if (STD_HIGH == HAL_FLASH_isLocked()){
        /* Write Unlock Sequence: Key1 then Key2 */
        pFLASH->KEYR.REG = FLASH_KEY1;
        pFLASH->KEYR.REG = FLASH_KEY2;
    }
    /* Return Current Flash Lock State as a result */
    return !HAL_FLASH_isLocked();
}

Std_ReturnType HAL_FLASH_Lock(void){
    /* Locking the FLASH */
    SET_BIT(pFLASH->CR.REG,FLASH_LOCK_POS);
    return E_OK;
}

Std_ReturnType HAL_FLASH_WaitLastOperation(){
    /* TODO:Make Time Out using SYSTick */

    WAIT_CONDITION_OR_TIMEOUT(READ_BIT(pFLASH->SR.REG, FLASH_BSY_POS) ,1000);
    return E_OK;
}



uint16_t HAL_FLASH_ReadAddress(uint32_t address){
	return *(volatile uint16_t*) address;
}

Std_ReturnType HAL_FLASH_ErasePageNumber(uint32_t PageNumber, uint32_t numberOfPages){
    return HAL_FLASH_ErasePage(STM32F103_FLASH_START + PageNumber * STM32F103_PAGE_SIZE,numberOfPages);
}
Std_ReturnType HAL_FLASH_ErasePage(uint32_t PageAddress,uint32_t numberOfPages){

    Std_ReturnType  ret = E_OK;

    if ((PageAddress >STM32F103_FLASH_END) || (PageAddress <  STM32F103_FLASH_START)){
        ret = E_NOT_OK;
    }
    else {
        /* Enable Page Erase Option */
        SET_BIT(pFLASH->CR.REG,FLASH_PER_POS);

        /* Get Start of The Current Page */
        PageAddress -= PageAddress % STM32F103_PAGE_SIZE;
        for (uint32_t i = 0; i < numberOfPages ; i++){

            /* Set Page Address */
            pFLASH->AR.REG = PageAddress + i * STM32F103_PAGE_SIZE;
            /* Start Erasing */
            FLASH_CR |= FLASH_CR_STRT_START_ENABLED;

            /* Wait For Erasing To Complete */
            HAL_FLASH_WaitLastOperation();
        }
        /* Disable Page Erase Option */
        CLEAR_BIT(pFLASH->CR.REG,FLASH_PER_POS);

    }

    return ret;

}
Std_ReturnType HAL_FLASH_EraseAll(uint8_t confirm){

    if (!confirm) return E_NOT_OK;

    /* Set Mass Erase to Enabled */
    SET_BIT(pFLASH->CR.REG,FLASH_MER_POS);

    /* Start Erasing */
    SET_BIT(pFLASH->CR.REG,FLASH_STRT_POS);

    /* Wait Till Operation Finish */
    HAL_FLASH_WaitLastOperation();

    /* Set Mass Erase to Disabled */
    CLEAR_BIT(pFLASH->CR.REG,FLASH_MER_POS);


    return E_OK;


}


Std_ReturnType HAL_FLASH_WriteProgram(uint32_t startAddress,uint8_t *program,uint32_t size){
    Std_ReturnType ret = E_OK;
    if (NULL == program){
        ret = E_NOT_OK;
    } else {

        /* Clean the error context */
        SET_BIT(pFLASH->SR.REG,FLASH_PGERR_POS);

        /* Proceed to program the new data */
        SET_BIT(pFLASH->CR.REG,FLASH_PG_POS);

        /* Get Remaining Data Size (due to writing in 16 bits) */
        uint8_t remaining = size % 2;


        for (int i = 0 ; i < size ; i+=2){
			/* Write data in the address */
			*(volatile uint16_t*)(startAddress + i) = *(uint16_t*)(program+i);
        }

        if (1==remaining){
            *(uint16_t *)(startAddress+size-1) = program[size-1] << 8 | 0xFF;
        }

        /* Disable Programming to Prevent Unwanted Actions */
        CLEAR_BIT(pFLASH->CR.REG,FLASH_PG_POS);
    }

    return ret;
}


Std_ReturnType HAL_FLASH_OptionByte_Lock(void){
    /* Clear the OPTWRE Bit to lock the FLASH Option Byte Registers access */
//    pFLASH->CR = STD_LOW;

    return E_OK;
}




void HAL_FLASH_WriteHalfWord(uint32_t Address, uint16_t Data)
{
    /* Clean the error context */
    SET_BIT(pFLASH->SR.REG,FLASH_PGERR_POS);

    /* Proceed to program the new data */
    SET_BIT(pFLASH->CR.REG,FLASH_PG_POS);

    /* Write data in the address */
    *(volatile uint16_t*)Address = Data;

    /* Disable Programming to Prevent Unwanted Actions */
    CLEAR_BIT(pFLASH->CR.REG,FLASH_PG_POS);
}
