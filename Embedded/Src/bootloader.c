
#include "bootloader.h"




BL_AppDetails_t * BL_GetAppDetails(){
    return (BL_AppDetails_t *)APP_DETAILS_ADDRESS;
}

uint32_t BL_GetAppLength(){
    BL_AppDetails_t *details = (BL_AppDetails_t *)APP_DETAILS_ADDRESS;
    return details->appLength;
}
uint8_t *BL_GetAppVersion(){
    BL_AppDetails_t *details = (BL_AppDetails_t *)APP_DETAILS_ADDRESS;
    return details->version;
}


uint8_t BL_CaclulateCheckSum(uint32_t startAddress , uint32_t length){
	uint8_t crc = 0;
	uint8_t *mem = (uint8_t *)startAddress;
	for (uint32_t i = 0 ; i < length ; i++){
		crc += mem[i];
	}
	return (0xFF - crc);
}



BL_CheckSumStatus_t BL_ValidateAppChecksum(){

	BL_AppDetails_t *const appDetails = BL_GetAppDetails();
	uint8_t crc = BL_CaclulateCheckSum(appDetails->appStartAddress, appDetails->appLength);

	if (appDetails->checksum != crc){
		return BL_CheckSumStatus_NotValid;
	}

	return BL_CheckSumStatus_Valid;
}

void BL_StartApp(){

	BL_AppDetails_t *const appDetails = BL_GetAppDetails();

//	__set_MSP(*(uint32_t *)appDetails->appStartAddress);

	SCB->VTOR.REG = appDetails->appStartAddress & SCB_VTOR_MASK;
	void (*reset_handler)(void)  = (void (*)(void))(*(uint32_t*)(appDetails->appStartAddress + 4));

	reset_handler();

}
