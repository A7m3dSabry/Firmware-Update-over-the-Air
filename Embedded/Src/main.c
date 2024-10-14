#include "main.h"



uint8_t RX_BUFFER[RX_BUFFER_SIZE];


/* WiFi Module Config */
ESP8266_Config_t espConfig = {0};

UpdateResult_t searchForNewUpdate(uint8_t * const currentVersion, uint8_t *availableVersion){
    /* Send Get Version Packet */
	send(PACKET_HEADER_GET_VERSION, NULL, 0);
    /* Wait for Receiving */
	receive(availableVersion);
    /* Validate if Current Version is different than the available one */
    if (!validate(currentVersion,availableVersion,0,APP_VERSION_LENGTH)){
        return UpdateResult_UPDATE_FOUND;
    }
    return UpdateResult_UPDATE_NOT_FOUND;
}

uint32_t getUpdateSize(){

    uint32_t updateSize = 0;
	/* Send Get File Size Packet */
    send(PACKET_HEADER_GET_FILE_SIZE,NULL,0);
    /* Reciving Packet */
	receive(&updateSize);
    return updateSize;
}


uint32_t downloadImage(uint32_t offset){
    uint8_t data[6] = {0};
    *(uint16_t*)data = 1+2+4+MAX_DOWNLOAD_PER_PACKET+1;
    *(uint32_t*)(data+2 )= offset;

    reverse(data,0,2);
    reverse(data,2,4);
    send(PACKET_HEADER_DOWNLOAD_IMAGE_PART,data,6);
    uint32_t downloadedSize =0;
    receive(&downloadedSize);
    return downloadedSize;
}

int main() {


    Std_ReturnType ret = E_OK;

    /* Initialize RCC */
    HAL_RCC_Init_DefaultConfigured();


    Bootloader_CheckUpdate();
    if (BL_CheckSumStatus_Valid == BL_ValidateAppChecksum()){
        disablePeripherals();
    	BL_StartApp();
    }
    HAL_NVIC_SystemReset();

    /* Should Not Be Reached */

    while(1){ /* Do Nothing */ }

}



void enablePeripherals() {
    /* Enable Peripherals */
    HAL_RCC_ChangePeripheralCLKState(PeripheralID_USART2, Peripheral_State_ON);
    HAL_RCC_ChangePeripheralCLKState(PeripheralID_PORTA, Peripheral_State_ON);
}




void disablePeripherals() {
    /* Disable Peripherals */
    HAL_RCC_ChangePeripheralCLKState(PeripheralID_USART2, Peripheral_State_OFF);
    HAL_RCC_ChangePeripheralCLKState(PeripheralID_PORTA, Peripheral_State_OFF);
}


void forceConnectToServerIP(ESP8266_ResponseType_t *res) {
    /* Loop Until Connection Started */
    do {

        (*res) = HAL_ESP8266_startUART_WIFI_PassThroughConnection(&espConfig, ESP8266_ProtocolType_TCP, RHOST,
                                                                  RPORT,
                                                                  NULL);
        if ((*res) == ESP8266_Return_ERROR) {
            HAL_Delay_ms(100);
        }
    } while ((*res) == ESP8266_Return_ERROR);
}

void forceConnectToNetwork(ESP8266_ResponseType_t *res) {

    /* Loop Until Join The Network */
    do {
        (*res) = HAL_ESP8266_joinAccessPoint(&espConfig, SSID_NAME, SSID_PASS);
        if ((*res) == ESP8266_Return_ERROR) {
            HAL_Delay_ms(100);
        }
    } while ((*res) == ESP8266_Return_ERROR || (*res) == ESP8266_Return_FAIL);
}

void initWiFiModule() {
    /* Configuring ESP8266 Module */
    espConfig.usartNumber = USART_Number_2;

    espConfig.selectedConfigs = ESP8266_SelectedConfigs_BasicConfigs | ESP8266_SelectedConfigs_WifiConfigs;

    espConfig.basicConfig.echoMode = ESP8266_EchoMode_Disable;
    espConfig.basicConfig.sleepMode = ESP8266_SleepMode_Disable;
    espConfig.uartConfig.flowControl = ESP8266_UART_flowControl_Disable;
    espConfig.uartConfig.parityBits = ESP8266_UART_parityBits_None;
    espConfig.uartConfig.stopBits = ESP8266_UART_stopBits_1;
    espConfig.uartConfig.dataBits = ESP8266_UART_dataBits_8;
    espConfig.wifiConfig.workingMode = ESP8266_Wifi_WorkingMode_StationMode;

    HAL_ESP8266_Init(&espConfig);
}

void initUSART() {
    /* Configuring USART Peripheral */
    USART_Config_t usartConfig = {0};
    usartConfig.mode = USART_Mode_Async;
    usartConfig.BaudRate = 115200;
    usartConfig.BasicConfig.stopBits = USART_StopBits_1Bit;
    usartConfig.BasicConfig.dataDirectionMode = USART_Mode_TransmitterAndReceiver;
    usartConfig.BasicConfig.wordLength = USART_FullPacket_8Bits;

    HAL_USART_Init(USART_Number_2, &usartConfig);
    HAL_USART_GPIOInit(USART_Number_2, &usartConfig);
}


void initializeMCUClock() {
    /* Configuring MCU Clock */
    /* CPU_Frequency = 56 MHZ */
    RCC_Config_t rccConfig = {0};
    rccConfig.sys_clk_src = SYS_CLK_SRC_PhaseLockedLoop;
    rccConfig.PLL.src = PLL_SRC_HSI_DIV_BY_2;
    rccConfig.PLL.mul_factor = PLL_MUL_FACTOR_13;
    rccConfig.APB1.prescaller = APB1_PRESCALLER_2;

    /* Init RCC */
    HAL_RCC_Init(&rccConfig);
}


void Bootloader_CheckUpdate(){

	 Std_ReturnType ret = E_OK;
     ESP8266_ResponseType_t res = ESP8266_Return_OK;

    /* Enable RCC Peripherals */
    enablePeripherals();

    /* Config USART to Communicate with WiFi Module */
    initUSART();

    /* Config WiFi Module */
    initWiFiModule();

    /* Loop Until Join The Network */
    forceConnectToNetwork(&res);

    /* Loop Until Connection Started */
    forceConnectToServerIP(&res);

    uint8_t newUpdateVersion[APP_VERSION_LENGTH] = {0};

    BL_AppDetails_t appDetails = *BL_GetAppDetails();

    /* Check if the latest available version isn't equal the current stored one */
   if (UpdateResult_UPDATE_FOUND == searchForNewUpdate(appDetails.version,newUpdateVersion)){
       /* Get Update File Size */
        uint32_t updateSize = getUpdateSize();
        /* Get Number of Pages Required to be erased */
        uint32_t pagesRequired = updateSize / STM32F103_PAGE_SIZE;
        /* Add 1 page if the update size isn't dividable by PageSize */
        pagesRequired += (0 != (updateSize % STM32F103_PAGE_SIZE))? 1 : 0;
        /* downloaded size and works as offset */
        uint32_t downloaded = 0;
        /* unlocking the flash */
        HAL_FLASH_Unlock();
        /* Try to Erase Required Pages if success then processed */
        if (E_OK == HAL_FLASH_ErasePageNumber(APP_START_PAGE,pagesRequired)){

            uint32_t offset = 0 ;
            while ((updateSize-downloaded) != 0){
                offset = downloadImage(downloaded);
                HAL_FLASH_WriteProgram(APP_START_ADDRESS + downloaded,RX_BUFFER+4,offset);
                downloaded += offset;
            }

            HAL_FLASH_ErasePage((uint32_t)BL_GetAppDetails(), 1);
            /* Update Version */
            appDetails.appStartAddress = APP_START_ADDRESS;
            appDetails.appLength = downloaded;
            appDetails.checksum = BL_CaclulateCheckSum(appDetails.appStartAddress,appDetails.appLength);
            for(uint32_t i = 0 ; i < APP_VERSION_LENGTH ; i ++){
                appDetails.version[i] = newUpdateVersion[i];
            }
            HAL_FLASH_WriteProgram((uint32_t) BL_GetAppDetails(), (uint8_t *)&appDetails, sizeof(appDetails));
        }
       HAL_FLASH_Lock();
   }

}

void send(uint8_t header, uint8_t *data, uint16_t data_length){
    uint8_t crc = 0;

    data_length +=1;
    uint8_t length[2] = {(data_length>>8) & 0xFF,data_length & 0xFF};

    /* Calculate CheckSum */
    crc+= header;
    crc+= data_length & 0xFF;
    crc+= (data_length >> 8) & 0xFF;
    data_length-=1;

	if ( NULL != data){
		for (uint32_t i = 0 ; i < data_length; i++){
				crc+= data[i];
			}

	}
    /* Summation of the packet should always be 0xFF */
    crc = 0xFF - crc;

    HAL_ESP8266_connSendBytes(&espConfig,ESP8266_LinkNumber_0,&header,1,ESP8266_UART_WiFi_PassThroughMode_On);
    HAL_ESP8266_connSendBytes(&espConfig,ESP8266_LinkNumber_0,length,2,ESP8266_UART_WiFi_PassThroughMode_On);

    if (NULL != data){
    	HAL_ESP8266_connSendBytes(&espConfig,ESP8266_LinkNumber_0 , data , data_length,ESP8266_UART_WiFi_PassThroughMode_On);
    }

    HAL_ESP8266_connSendBytes(&espConfig,ESP8266_LinkNumber_0 , &crc , 1,ESP8266_UART_WiFi_PassThroughMode_On);

}


BL_ReceiveStatus_t processPacket(uint8_t header){

    BL_ReceiveStatus_t ret = BL_ReceiveStatus_CheckSum_OK;
    ESP8266_ResponseType_t espRet = ESP8266_Return_OK;

    uint16_t length = {0};

    /* Get Length of the packet */
    espRet = HAL_ESP8266_ReceiveBytes(&espConfig,(uint8_t *)&length,2,1000);
    length = (length & 0xFF)<<8 | ((length>>8) & 0xFF);
    /* Receive Packet */
    HAL_ESP8266_ReceiveBytes(&espConfig,RX_BUFFER,(uint32_t)length,1000);

    /* Calculate CheckSum */
    uint8_t crc =0;
    crc+=header;
    crc += (length & 0xFF) + ((length >> 8) & 0xFF);
    for (uint32_t i = 0 ; i < length ; i++){
        crc+=RX_BUFFER[i];
    }
    if (0xFF != crc){
        ret = BL_ReceiveStatus_CheckSum_NOT_OK;
    }

    return ret;

}

uint32_t validate(uint8_t *a, uint8_t *b, uint32_t start,uint32_t length){

    for (uint32_t i = start ; i < (start + length); i++){
        if (a[i] != b[i]){
            return 0;
        }
    }
    return 1;
}


void reverse(uint8_t *data, uint32_t start, uint32_t len){
    uint8_t tmp;
    for (int i = 0 ; i < len/2 ;i++){
        tmp = data[start+i];
        data[start+i] = data[start+len-i-1] ;
        data[start+len-i-1] = tmp;
    }
}


void handle_version(uint8_t *version){
    for (uint32_t i = 0 ; i < APP_VERSION_LENGTH ; i++){
    	version[i] = RX_BUFFER[i];
    }
}


uint32_t handle_images_size(){
    reverse(RX_BUFFER,0,4);
    return *(uint32_t *)RX_BUFFER;
}

uint32_t handle_image_rx(){
    reverse(RX_BUFFER,0,4);
    return *(uint32_t*)RX_BUFFER;

}

void receive(void *result){
    uint8_t header = 0;
    BL_ReceiveStatus_t ret = BL_ReceiveStatus_CheckSum_OK;

    HAL_ESP8266_ReceiveByte(&espConfig,&header,1000);


    switch (header){
        case PACKET_HEADER_GET_VERSION_RESPONSE:
            processPacket(header);
            handle_version(result);
            break;
        case PACKET_HEADER_GET_FILE_SIZE:
            processPacket(header);
            *(uint32_t *) result = handle_images_size();
            break;
        case 0x83:
            processPacket(header);
            *(uint32_t *) result = handle_image_rx();
            break;

        case 0xFF:
            /* ERROR */
            break;
        default:
            /* This is Error so neglect it */
            /* FUTURE: You can send Error Msg to the Server and it resend last packet */
    }

}




