

/**************	Section{} Includes *********************************/
#include "exti.h"
/**************	Section{} Local Variables Declarations *************/
/**************	Section{} Local Methods Prototype Declarations *****/
/**************	Section{} Methods Declarations *********************/

Std_ReturnType HAL_EXTI_ChangeLineState(const EXTILine_t line, const EXTILineType_t type) {
    Std_ReturnType ret = E_OK;

    if (((uint32_t) line > EXTILine_19)
        || ((uint32_t) type > EXTILineType_InterruptAndEvent)) {

        ret = E_NOT_OK;
    } else {


        FORCE_BIT(EXTI->EMR.REG, (uint32_t) line, READ_BIT((uint32_t) type, BIT_0));
        FORCE_BIT(EXTI->IMR.REG, (uint32_t) line, READ_BIT((uint32_t) type, BIT_1));


    }


    return ret;
}

Std_ReturnType
HAL_EXTI_ChangeLineEdgeDetection(const EXTILine_t line, const EXTIEdgeType_t edgeType) {

    Std_ReturnType ret = E_OK;

    if (((uint32_t) line > EXTILine_19)
        || ((uint32_t) edgeType > EXTIEdgeType_RisingAndFalling)) {
        ret = E_NOT_OK;
    } else {

        FORCE_BIT(EXTI->RTSR.REG, (uint32_t) line, READ_BIT((uint32_t) edgeType, BIT_0));
        FORCE_BIT(EXTI->FTSR.REG, (uint32_t) line, READ_BIT((uint32_t) edgeType, BIT_1));

    }


    return ret;

}


Std_ReturnType HAL_EXTI_ReadLinePendingState(const EXTILine_t line, EXTILinePendingState_t *state) {
    Std_ReturnType ret = E_OK;

    if (((uint32_t) line > EXTILine_19) || (state == NULL)) {
        ret = E_NOT_OK;
    } else {

        *state = READ_BIT(EXTI->PR.REG, (uint32_t) line);

    }


    return ret;
}

Std_ReturnType HAL_EXTI_ChangeLinePendingState(const EXTILine_t line, const EXTILinePendingState_t state) {

    Std_ReturnType ret = E_OK;

    if (((uint32_t) line > EXTILine_19) || ((uint32_t) state > 1)) {
        ret = E_NOT_OK;
    } else {

        if ((uint32_t) state & 0x1) {
            // Trigger The Line
            SET_BIT(EXTI->SWIER.REG, (uint32_t) line);
        } else {
            // Clear Pending state
            SET_BIT(EXTI->PR.REG, (uint32_t) line);
        }
    }


    return ret;
}


static InterruptCallback_t interruptsCallbacks[7] = {0};
Std_ReturnType HAL_EXTI_RegisterInterruptCallback(const EXTIInterruptLines_t line, InterruptCallback_t handler) {
    Std_ReturnType ret = E_OK;

    if (((uint32_t) line > EXTI_15_10) || (handler == NULL)) {
        ret = E_NOT_OK;
    } else {
        interruptsCallbacks[line] = handler;
    }
    return ret;
}

/**************	Section{} Helper Methods Declarations  *************/

void EXTI0_IRQHandler(void){
    SET_BIT(EXTI->PR.REG,BIT_0);
    if (interruptsCallbacks[0] != NULL){
        interruptsCallbacks[0](INTERRUPTS_NO_PARAMS);
    }
}

void EXTI1_IRQHandler(void){
    SET_BIT(EXTI->PR.REG,BIT_1);
    if (interruptsCallbacks[1] != NULL){
        interruptsCallbacks[1](INTERRUPTS_NO_PARAMS);
    }
}

void EXTI2_IRQHandler(void){
    SET_BIT(EXTI->PR.REG,BIT_2);
    if (interruptsCallbacks[2] != NULL){
        interruptsCallbacks[2](INTERRUPTS_NO_PARAMS);
    }
}
void EXTI3_IRQHandler(void){
    SET_BIT(EXTI->PR.REG,BIT_3);
    if (interruptsCallbacks[3] != NULL){
        interruptsCallbacks[3](INTERRUPTS_NO_PARAMS);
    }
}
void EXTI4_IRQHandler(void){
    SET_BIT(EXTI->PR.REG,BIT_4);
    if (interruptsCallbacks[4] != NULL){
        interruptsCallbacks[4](INTERRUPTS_NO_PARAMS);
    }
}

void EXTI9_5_IRQHandler(void){
    for (uint8_t i=5; i <= 9 ; i++){
        if ((READ_BIT(EXTI->PR.REG,i)) && (READ_BIT(EXTI->IMR.REG,i))){
            SET_BIT(EXTI->PR.REG,i);
            if (interruptsCallbacks[5] != NULL){
                interruptsCallbacks[5]((uint32_t) i);
            }
            break;
        }
    }
}


void EXTI15_10_IRQHandler(void){
    for (uint8_t i=10; i <= 15 ; i++){
        if ((READ_BIT(EXTI->PR.REG,i)) && (READ_BIT(EXTI->IMR.REG,i))){
            SET_BIT(EXTI->PR.REG,i);
            if (interruptsCallbacks[6] != NULL){
                interruptsCallbacks[6]((uint32_t) i);
            }
            break;
        }
    }
}
