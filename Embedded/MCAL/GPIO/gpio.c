


/**************	Section: Includes *********************************/
#include "gpio.h"


/**************	Section: Local Variables Declarations *************/

/**************	Section: Local Methods Prototype Declarations *****/
/**************	Section: Methods Declarations *********************/


Std_ReturnType HAL_GPIO_ConfigPins(const GPIO_PORT_ID_t port, const uint16_t pins, const GPIO_Pin_Config_t *config) {


    Std_ReturnType ret = E_OK;

    if ((uint32_t) port > PORT_ID_PORTE) {
        ret = E_NOT_OK;
    } else {

        for (uint32_t bitIndex = 0; bitIndex < 8; bitIndex++) {
            if (((pins & 0x00FF) >> bitIndex) == 0) {
                break;
            } else if (READ_BIT(pins, bitIndex) == 1) {

                FORCE_MASK(GPIO->ALL_PORTS.CRLs[port].REG, (0xF << 4 * bitIndex),
                           ((*((uint32_t *) config)) & 0xF) << (4 * bitIndex));

            }
        }


        for (uint32_t bitIndex = 8; bitIndex < 16; bitIndex++) {
            if (((pins) >> bitIndex) == 0) {
                break;
            } else if (READ_BIT(pins, bitIndex) == 1) {
                FORCE_MASK(GPIO->ALL_PORTS.CRHs[port].REG, (0xF << 4 * (bitIndex - 8)),
                           ((*((uint32_t *) config)) & 0xF) << (4 * (bitIndex - 8)));
            }
        }


    }

    return ret;
}

Std_ReturnType HAL_GPIO_ConfigPinsDirect(const GPIO_PORT_ID_t port, const uint16_t pins,
                                         const GPIO_Pin_Mode_t mode,
                                         const GPIO_Pin_Mode_Config_t config) {

    GPIO_Pin_Config_t cfg = {0};
    cfg.mode = mode;
    cfg.config = config;

    return HAL_GPIO_ConfigPins(port, pins, &cfg);
}

Std_ReturnType HAL_GPIO_SetPinsValue(const GPIO_PORT_ID_t port, const uint16_t pins, const Pin_State_t pinState) {
    Std_ReturnType ret = E_OK;
    if ((uint32_t) port > PORT_ID_PORTE) {
        ret = E_NOT_OK;
    } else {
        GPIO->ALL_PORTS.BSRRs[port].REG |= (pins << ((pinState) ? 0 : 16));
    }


    return ret;
}

Std_ReturnType HAL_GPIO_TogglePinsValue(GPIO_PORT_ID_t port, uint16_t pins) {
    Std_ReturnType ret = E_OK;

    if ((uint32_t) port > PORT_ID_PORTE) {
        ret = E_NOT_OK;
    } else {
        Pin_State_t newPinState;
        for (uint32_t bitIndex = 0; bitIndex < 16; bitIndex++) {
            if (((pins & ~0) >> bitIndex) == 0) {
                break;
            } else if ((READ_BIT(pins, bitIndex) == 1)) {
                /* Get Inverse State of the Bit */
                newPinState = (READ_BIT(~(GPIO->ALL_PORTS.ODRs[port].REG), bitIndex));
                /* Choose to Set bit or Reset it based on its new state */
//                FORCE_BIT(GPIO->ALL_PORTS.ODRs[port].REG,bitIndex,newPinState);
                GPIO->ALL_PORTS.BSRRs[port].REG |= (1 << bitIndex) << ((newPinState) ? 0 : 16);
            }

        }
    }

    return ret;
}


Std_ReturnType HAL_GPIO_ReadPinValue(const GPIO_PORT_ID_t port, const GPIO_Pin_ID_t pin, Pin_State_t *state) {
    Std_ReturnType ret = E_OK;
    if ((uint32_t) port > PORT_ID_PORTE) {
        ret = E_NOT_OK;
    } else {

        *state = (GPIO->ALL_PORTS.IDRs[port].REG & pin) ? Pin_State_ON : Pin_State_OFF;

    }


    return ret;
}


Std_ReturnType HAL_GPIO_ReadPinsValue(const GPIO_PORT_ID_t port, const uint16_t pins, uint16_t *states) {
    Std_ReturnType ret = E_OK;
    if ((uint32_t) port > PORT_ID_PORTE) {
        ret = E_NOT_OK;
    } else {

        *states = READ_MASK(GPIO->ALL_PORTS.IDRs[port].REG, pins);
    }


    return ret;
}



/**************	Section: Helper Methods Declarations  *************/


