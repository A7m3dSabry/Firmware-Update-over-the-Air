

/**************	Section: Includes *********************************/
#include "dma.h"
/**************	Section: Local Variables Declarations *************/
/**************	Section: Local Methods Prototype Declarations *****/
/**************	Section: Methods Declarations *********************/

Std_ReturnType HAL_DMA_Init(const DMA_ChannelNumber_t channelNumber, const DMA_ChannelConfig_t *config) {
    Std_ReturnType ret = E_OK;
    if ((config == NULL) || (channelNumber > DMA_Channel_7)) {
        ret = E_NOT_OK;
    } else {


        pDMA->All.Channels[channelNumber].channel.CCR.BITS.EN = STD_OFF;
        WAIT_CONDITION_OR_TIMEOUT(pDMA->All.Channels[channelNumber].channel.CCR.BITS.EN == STD_OFF, TIMEOUT_INF);

        pDMA->IFCR.REG = ~(0UL);
        pDMA->All.Channels[channelNumber].channel.CMAR.REG = config->memoryAddress;
        pDMA->All.Channels[channelNumber].channel.CPAR.REG = config->peripheralAddress;
        pDMA->All.Channels[channelNumber].channel.CNDTR.REG = config->operationsCount;
        pDMA->All.Channels[channelNumber].channel.CCR.REG = CONVERT_TYPE(uint32_t, config->ChannelConfigurations);


    }
    return ret;
}



Std_ReturnType  HAL_DMA_InitPeripheral(DMA_PeripheralRequest_t peripheralRequest, const DMA_ChannelConfig_t *config ){

    return HAL_DMA_Init((uint32_t)peripheralRequest,config);
}
Std_ReturnType HAL_DMA_StartTransfer(const DMA_ChannelNumber_t channelNumber) {
    Std_ReturnType ret = E_OK;

    if ((uint32_t) channelNumber > DMA_Channel_7) {
        ret = E_NOT_OK;
    } else {

        pDMA->All.Channels[channelNumber].channel.CCR.REG |= STD_ON;
    }

    return ret;
}

Std_ReturnType HAL_DMA_StartTransferCount(const DMA_ChannelNumber_t channelNumber, const uint16_t NumberOfTransfers) {
    Std_ReturnType ret = E_OK;

    if ((uint32_t) channelNumber > DMA_Channel_7) {
        ret = E_NOT_OK;
    } else {

        pDMA->All.Channels[channelNumber].channel.CNDTR.REG = NumberOfTransfers;
        pDMA->All.Channels[channelNumber].channel.CCR.REG |= STD_ON;
    }

    return ret;
}

Std_ReturnType
HAL_DMA_StartBlockingTransfer(const DMA_ChannelNumber_t channelNumber, const uint16_t NumberOfTransfers,
                              uint32_t maxTime) {

    Std_ReturnType ret = E_OK;


    ret = HAL_DMA_StartTransferCount(channelNumber, NumberOfTransfers);

    if (ret == E_OK) {
        while ((READ_BIT(pDMA->ISR.REG, channelNumber * 4 + 1) == 0)
               && (maxTime-- > 0)) {/* Do Nothing */}
        // TODO: Return Error Type on The transfer didn't end before the blocking time end
    }

    return ret;
}

static InterruptCallback_t interruptsCallbacks[7] = {0};

Std_ReturnType
HAL_DMA_RegisterInterruptCallback(const DMA_PeripheralRequest_t channel, const InterruptCallback_t callback) {

    Std_ReturnType ret = E_OK;
    if ((uint32_t) channel > DMA_Channel_7) {
        ret = E_NOT_OK;
    } else {
        interruptsCallbacks[channel] = callback;
    }

    return ret;
}

/**************	Section: Helper Methods Declarations  *************/
void DMA1_Channel1_IRQHandler(void) {
    pDMA->IFCR.CTCIF1 = STD_HIGH;
    if (interruptsCallbacks[0] != NULL) {
        interruptsCallbacks[0](DMA_Channel_1);
    }
}

void DMA1_Channel2_IRQHandler(void) {
    pDMA->IFCR.CTCIF2 = STD_HIGH;
    if (interruptsCallbacks[1] != NULL) {
        interruptsCallbacks[1](DMA_Channel_2);
    }
}

void DMA1_Channel3_IRQHandler(void) {
    pDMA->IFCR.CTCIF3 = STD_HIGH;
    if (interruptsCallbacks[2] != NULL) {
        interruptsCallbacks[2](DMA_Channel_3);
    }
}

void DMA1_Channel4_IRQHandler(void) {
	pDMA->IFCR.CTCIF4 = STD_HIGH;
    if (interruptsCallbacks[3] != NULL) {
        interruptsCallbacks[3](DMA_Channel_4);
    }
}

void DMA1_Channel5_IRQHandler(void) {
    pDMA->IFCR.CTCIF5 = STD_HIGH;
    if (interruptsCallbacks[4] != NULL) {
        interruptsCallbacks[4](DMA_Channel_5);
    }
}

void DMA1_Channel6_IRQHandler(void) {
    pDMA->IFCR.CTCIF6 = STD_HIGH;
    if (interruptsCallbacks[5] != NULL) {
        interruptsCallbacks[5](DMA_Channel_6);
    }
}

void DMA1_Channel7_IRQHandler(void) {
    pDMA->IFCR.CTCIF7 = STD_HIGH;
    if (interruptsCallbacks[6] != NULL) {
        interruptsCallbacks[6](DMA_Channel_7);
    }
}



