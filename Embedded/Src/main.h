
#ifndef MAIN_H_
#define MAIN_H_

/**************	Section: Includes ***************************/
#include "stm32f103c8t.h"
#include "mcal_layer.h"
#include "std_types.h"
#include "delay.h"
#include "esp8266.h"
#include "bootloader.h"
/**************	Section: Macro Definitions Declarations *****/




#define SSID_NAME "WIFI_NAME"
#define SSID_PASS "WIFI_PASSWORD"
#define RHOST "HOST_IP"
#define RPORT (8000)

#define RX_BUFFER_SIZE      (7000)

#define MAX_DOWNLOAD_PER_PACKET (6000)

#define PACKET_HEADER_GET_VERSION          (0x01)
#define PACKET_HEADER_GET_FILE_SIZE        (0x02)
#define PACKET_HEADER_DOWNLOAD_IMAGE_PART  (0x03)

#define PACKET_HEADER_GET_VERSION_RESPONSE          (0x81)
#define PACKET_HEADER_GET_FILE_SIZE_RESPONSE        (0x82)
#define PACKET_HEADER_DOWNLOAD_IMAGE_PART_RESPONSE  (0x83)

/**************	Section: Macro Functions Declarations *******/
/**************	Section: Data Types Declarations ************/

/**
 * @brief Update Status Enum
 */
typedef enum {
    UpdateResult_UPDATE_NOT_FOUND,
    UpdateResult_UPDATE_FOUND
}UpdateResult_t;

/**
 * @brief Bootloader Receiving Status
 */
typedef enum {
    BL_ReceiveStatus_CheckSum_OK,
    BL_ReceiveStatus_CheckSum_NOT_OK,
    BL_ReceiveStatus_TimeOut,
} BL_ReceiveStatus_t;

/**************	Section: Methods Declarations  **************/



/**
 * @brief Prototype of Void Handles Initializing MCU Clock (RCC)
 */
void initializeMCUClock(void);


/**
 * @brief Prototype of Void Handles Configuring USART Communication Peripheral
 */
void initUSART();

/**
 * @brief Prototype of Void Handles Configuring WiFi Module
 */
void initWiFiModule();

/**
 * @brief Prototype of Void Handles Looping Until Connection to Network Happen
 * @param res response of the function
 */
void forceConnectToNetwork(ESP8266_ResponseType_t *res);

/**
 * @brief Prototype of Void Handles Looping Until Connection to Server IP Happen
 * @param res response of the function
 */
void forceConnectToServerIP(ESP8266_ResponseType_t *res);


/**
 * @brief Prototype of Void Handles Enabling Peripherals Clock
 */
void enablePeripherals();


/**
 * @brief Prototype of Void Handles Disabling Peripherals Clock
 */
void disablePeripherals();

/**
 * @brief function manages packet formation and sending the packet
 * @param header: header of the packet
 * @param data:   data to be sent and can be null
 * @param data_length data length, can be 0
 */
void send(uint8_t header, uint8_t *data, uint16_t data_length);
/**
 * @brief function to await the response and process it when it received
 */
void receive(void *);

/**
 * @brief function reverse an array.
 * @param data  data pointer of the array
 * @param start start index
 * @param len   length to be reversed
 */
void reverse(uint8_t *data, uint32_t start, uint32_t len);
/**
 * @brief a comparing function compare the two arrays have same values or not, which also validates equality
 * @param a first array
 * @param b second array
 * @param start  start index
 * @param length length to be compared
 * @return
 */
uint32_t validate(uint8_t *a, uint8_t *b, uint32_t start,uint32_t length);

/**
 * @brief function to check for update and perform update if needed
 */
void  Bootloader_CheckUpdate(void);



#endif /* MAIN_H_ */




