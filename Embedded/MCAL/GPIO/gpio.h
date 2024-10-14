

#ifndef GPIO_GPIO_H_
#define GPIO_GPIO_H_


/**************	Section: Includes ***************************/

#include "std_types.h"
#include "stm32f103c8t.h"

/**************	Section: Macro Definitions Declarations *****/
/**************	Section: Macro Functions Declarations *******/
/**************	Section: Data Types Declarations ************/

typedef enum {
    PORT_ID_PORTA = 0,
    PORT_ID_PORTB,
    PORT_ID_PORTC,
    PORT_ID_PORTD,
    PORT_ID_PORTE
} GPIO_PORT_ID_t;

typedef enum {
    GPIO_PIN_ID_0 = PIN_0,
    GPIO_PIN_ID_1 = PIN_1,
    GPIO_PIN_ID_2 = PIN_2,
    GPIO_PIN_ID_3 = PIN_3,
    GPIO_PIN_ID_4 = PIN_4,
    GPIO_PIN_ID_5 = PIN_5,
    GPIO_PIN_ID_6 = PIN_6,
    GPIO_PIN_ID_7 = PIN_7,
    GPIO_PIN_ID_8 = PIN_8,
    GPIO_PIN_ID_9 = PIN_9,
    GPIO_PIN_ID_10 = PIN_10,
    GPIO_PIN_ID_11 = PIN_11,
    GPIO_PIN_ID_12 = PIN_12,
    GPIO_PIN_ID_13 = PIN_13,
    GPIO_PIN_ID_14 = PIN_14,
    GPIO_PIN_ID_15 = PIN_15,
    GPIO_PIN_ID_16 = PIN_16,

} GPIO_Pin_ID_t;

typedef enum {
    Pin_Mode_Input        = (GPIO_MODE_INPUT),
    Pin_Mode_Output_10MHZ = (GPIO_MODE_OUTPUT_10MHZ),
    Pin_Mode_Output_2MHZ  = (GPIO_MODE_OUTPUT_2MHZ),
    Pin_Mode_Output_50MHZ = (GPIO_MODE_OUTPUT_50MHZ),
} GPIO_Pin_Mode_t;

typedef enum {

    Pin_Mode_Config_INPUT_FLOATING      = (GPIO_CNF_INPUT_FLOATING),
    Pin_Mode_Config_INPUT_PULL_UP_DOWN  = (GPIO_CNF_INPUT_PULL_UP_DOWN),
    Pin_Mode_Config_INPUT_ANALOG        = (GPIO_CNF_INPUT_ANALOG),

    Pin_Mode_Config_Output_PUSH_PULL_GENERAL_PURPOSE     = (GPIO_CNF_OUTPUT_PUSH_PULL_GENERAL_PURPOSE),
    Pin_Mode_Config_Output_PUSH_PULL_ALTERNATE_FUNCTION         = (GPIO_CNF_OUTPUT_PUSH_PULL_ALTERNATE_FUNCTION),
    Pin_Mode_Config_Output_OPEN_DRAIN_GENERAL_PURPOSE           = (GPIO_CNF_OUTPUT_OPEN_DRAIN_GENERAL_PURPOSE),
    Pin_Mode_Config_Output_OPEN_DRAIN_ALTERNATE_FUNCTION        =(GPIO_CNF_OUTPUT_OPEN_DRAIN_ALTERNATE_FUNCTION)

}GPIO_Pin_Mode_Config_t ;

typedef struct {

        GPIO_Pin_Mode_t mode              :2;
        GPIO_Pin_Mode_Config_t config     :2;

}GPIO_Pin_Config_t;


typedef enum {
    Pin_ON = (STD_ON),
    Pin_OFF = (STD_OFF),

    Pin_High = (STD_HIGH),
    Pin_Low = (STD_LOW),

} Pin_State_Configurations_t;

//typedef struct {
//    uint8_t state           :1;
//} Pin_State_t;

typedef enum {
    Pin_State_ON = (STD_ON),
    Pin_State_OFF = (STD_OFF)
}Pin_State_t;
/**************	Section: Methods Declarations  **************/

Std_ReturnType HAL_GPIO_ConfigPins(const GPIO_PORT_ID_t port, const uint16_t pins, const GPIO_Pin_Config_t *config);
Std_ReturnType HAL_GPIO_ConfigPinsDirect(const GPIO_PORT_ID_t port, const uint16_t pins,
                                         const GPIO_Pin_Mode_t mode,
                                         const GPIO_Pin_Mode_Config_t config);
Std_ReturnType HAL_GPIO_SetPinsValue(const GPIO_PORT_ID_t port, const uint16_t pins, const Pin_State_t pinState);
Std_ReturnType HAL_GPIO_TogglePinsValue(GPIO_PORT_ID_t port, uint16_t pins);
Std_ReturnType HAL_GPIO_ReadPinValue(const GPIO_PORT_ID_t port, const GPIO_Pin_ID_t pin, Pin_State_t *state);
Std_ReturnType HAL_GPIO_ReadPinsValue(const GPIO_PORT_ID_t port, const uint16_t pins, uint16_t *states);
#endif /* GPIO_GPIO_H_ */
