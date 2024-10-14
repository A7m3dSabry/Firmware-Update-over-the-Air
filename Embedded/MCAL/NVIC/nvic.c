

/**************	Section: Includes *********************************/
#include "nvic.h"
/**************	Section: Local Variables Declarations *************/
/**************	Section: Local Methods Prototype Declarations *****/
/**************	Section: Methods Declarations *********************/

Std_ReturnType HAL_NVIC_ChangeInterruptState(const IRQn_t IRQn, const InterruptState_t state) {

    Std_ReturnType ret = E_OK;

    if ((uint32_t) IRQn > IRQn_OTG_FS) {
        ret = E_NOT_OK;
    } else {


        // TODO: Add Check for weather we are in privileged mode or not
        switch ((uint32_t) state & 0x1) {
            case InterruptState_Enable:

                SET_BIT(pNVIC->All.ISERs[IRQn / 32 ].REG, IRQn % 32);
                break;
            case InterruptState_Disable:

                SET_BIT(pNVIC->All.ICERs[IRQn / 32].REG, IRQn % 32);
                break;
        }

    }

    return ret;
}

Std_ReturnType HAL_NVIC_ReadInterruptState(const IRQn_t IRQn, InterruptState_t *state) {

    Std_ReturnType ret = E_OK;

    if (((uint32_t) IRQn > IRQn_OTG_FS) || (state == NULL)) {
        ret = E_NOT_OK;
    } else {
        // TODO: Add Check for weather we are in privileged mode or not
        *state = READ_BIT(pNVIC->All.ISERs[IRQn / 32].REG, IRQn % 32);
    }

    return ret;
}

Std_ReturnType HAL_NVIC_ChangeInterruptPendingState(const IRQn_t IRQn, const InterruptPendingState_t state) {
    Std_ReturnType ret = E_OK;
    if ((uint32_t) IRQn > IRQn_OTG_FS) {
        ret = E_NOT_OK;
    } else {


        // TODO: Add Check for weather we are in privileged mode or not
        switch ((uint32_t) state & 0x1) {
            case InterruptPendingState_Enable:

                SET_BIT(pNVIC->All.ISPRs[IRQn / 32].REG, IRQn % 32);

            case InterruptPendingState_Disable:

                SET_BIT(pNVIC->All.ICPRs[IRQn / 32].REG, IRQn % 32);
        }


    }

    return ret;
}

Std_ReturnType HAL_NVIC_ReadInterruptPendingState(const IRQn_t IRQn, InterruptPendingState_t *state) {
    Std_ReturnType ret = E_OK;

    if (((uint32_t) IRQn > IRQn_OTG_FS) || (state == NULL)) {
        ret = E_NOT_OK;
    } else {


        // TODO: Add Check for weather we are in privileged mode or not
        *state = READ_BIT(pNVIC->All.ISPRs[(uint32_t) IRQn / 32].REG, IRQn % 32);
    }

    return ret;
}

Std_ReturnType HAL_NVIC_ChangeInterruptPriority(const IRQn_t IRQn, const uint8_t priority) {
    Std_ReturnType ret = E_OK;

    if ((uint32_t) IRQn > IRQn_OTG_FS) {
        ret = E_NOT_OK;
    } else {
        pNVIC->All.IPs[(uint32_t) IRQn].IP_HIGH = (priority & 0x0F);
    }

    return ret;
}

Std_ReturnType HAL_NVIC_ReadInterruptPriority(const IRQn_t IRQn, uint8_t *priority) {
    Std_ReturnType ret = E_OK;

    if (((uint32_t) IRQn > IRQn_OTG_FS) || (priority == NULL)) {
        ret = E_NOT_OK;
    } else {
        *priority = (uint8_t) pNVIC->All.IPs[(uint32_t) IRQn].IP_HIGH;
    }


    return ret;
}

Std_ReturnType HAL_NVIC_ChangeInterruptGroupPriority(const InterruptGroupPriority_t groupPriority) {
    Std_ReturnType ret = E_OK;


    if ((uint32_t) groupPriority > InterruptPriorityGroup_Group7) {
        ret = E_NOT_OK;
    } else {
        SCB->AIRCR.PRIGROUP = (uint32_t) groupPriority;
    }

    return ret;
}

Std_ReturnType HAL_NVIC_ReadInterruptGroupPriority(InterruptGroupPriority_t *groupPriority) {
    Std_ReturnType ret = E_OK;

    if (groupPriority == NULL) {
        ret = E_NOT_OK;
    } else {
        *groupPriority = SCB->AIRCR.PRIGROUP;
    }

    return ret;
}

Std_ReturnType HAL_NVIC_IsInterruptActive(const IRQn_t IRQn, uint8_t *active) {
    Std_ReturnType ret = E_OK;

    if (((uint32_t) IRQn > IRQn_OTG_FS) || (active == NULL)) {
        ret = E_NOT_OK;
    } else {
        *active = READ_BIT(pNVIC->All.IABRs[(uint32_t) IRQn / 32].REG, (uint32_t) IRQn % 32);
    }
    return ret;
}

Std_ReturnType HAL_NVIC_GenerateSoftwareInterrupt(const IRQn_t IRQn) {
    Std_ReturnType ret = E_OK;

    if ((uint32_t) IRQn > IRQn_OTG_FS)  {
        ret = E_NOT_OK;
    } else {
        pNVIC->STIR.INTID = (uint32_t) IRQn;
    }
    return ret;
}

void HAL_NVIC_SystemReset(void) {
    SCB->AIRCR.SYSRESETREQ = STD_HIGH;
}




/**************	Section: Helper Methods Declarations  *************/
