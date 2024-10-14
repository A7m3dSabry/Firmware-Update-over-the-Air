
#ifndef BOOTLOADER_H
#define BOOTLOADER_H

/**************	Section: Includes ***************************/
#include "std_types.h"
#include "core_functions.h"
#include "stm32f103c8t.h"
#include "flash.h"
/**************	Section: Macro Definitions Declarations *****/

#define NUMBER_OF_MEMORY_PAGES (STM32F103_FLASH_PAGES_COUNT)
#define NUMBER_OF_BOOTLOADER_PAGES  (20)
#define NUMBER_OF_APP_PAGES     (NUMBER_OF_MEMORY_PAGES - NUMBER_OF_BOOTLOADER_PAGES)

#define APP_START_PAGE (NUMBER_OF_BOOTLOADER_PAGES + 0)
#define APP_START_ADDRESS (STM32F103_FLASH_START + APP_START_PAGE * STM32F103_PAGE_SIZE)
#define APP_VERSION_LENGTH (3)
#define APP_DETAILS_ADDRESS (STM32F103_FLASH_END - sizeof(BL_AppDetails_t))

/**************	Section: Macro Functions Declarations *******/
/**************	Section: Data Types Declarations ************/

typedef struct {
	uint32_t appStartAddress;
    uint32_t appLength;
    uint8_t  checksum;
    uint8_t  version[APP_VERSION_LENGTH];
}BL_AppDetails_t;


typedef enum {
	BL_CheckSumStatus_Valid,
	BL_CheckSumStatus_NotValid,
}BL_CheckSumStatus_t;



/**************	Section: Methods Declarations  **************/
BL_AppDetails_t * BL_GetAppDetails();
uint32_t BL_GetAppLength();
uint8_t *BL_GetAppVersion();
uint8_t BL_CheckAppCheckSum();
void BL_StartApp();
uint8_t BL_CaclulateCheckSum(uint32_t startAddress , uint32_t length);
BL_CheckSumStatus_t BL_ValidateAppChecksum();

#endif //BOOTLOADER_H
