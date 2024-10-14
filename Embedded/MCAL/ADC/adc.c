


/**************	Section: Includes *********************************/
#include "adc.h"

/**************	Section: Local Variables Declarations *************/
/**************	Section: Local Methods Prototype Declarations *****/
/**************	Section: Methods Declarations *********************/



Std_ReturnType HAL_ADC_Init(const ADC_Number_t adcNumber, const ADC_Config_t *config) {
    Std_ReturnType ret = E_OK;

    if (((uint32_t) adcNumber > ADC_Number_2) || (config == NULL)) {
        ret = E_NOT_OK;
    } else {
        pADC->ADCs[adcNumber].ADC.CR1.REG = CONVERT_TYPE_INDX(uint32_t, *config, 0);
        pADC->ADCs[adcNumber].ADC.CR2.REG = CONVERT_TYPE_INDX(uint32_t, *config, 1);

        pADC->ADCs[adcNumber].ADC.SQR1.L = config->RegularChannelsOptions.conversionLength;
        pADC->ADCs[adcNumber].ADC.JSQR.JL = config->InjectedChannelsOptions.conversionLength;

        pADC->ADCs[adcNumber].ADC.HTR.HT = config->WatchDogOptions.highLevelThreshold;
        pADC->ADCs[adcNumber].ADC.LTR.LT = config->WatchDogOptions.lowLevelThreshold;

        pADC->ADCs[adcNumber].ADC.CR2.ADON = pADC_ADON_ENABLE;
    }
    return ret;
}

Std_ReturnType HAL_ADC_DeInit(const ADC_Number_t adcNumber) {
    Std_ReturnType ret = E_OK;

    if ((uint32_t) adcNumber > ADC_Number_2) {
        ret = E_NOT_OK;
    } else {
        pADC->ADCs[adcNumber].ADC.CR2.ADON = pADC_ADON_DISABLE;
    }
    return ret;
}

Std_ReturnType HAL_ADC_TriggerRegularConv(const ADC_Number_t adcNumber) {
    Std_ReturnType ret = E_OK;

    if ((uint32_t) adcNumber > ADC_Number_2) {
        ret = E_NOT_OK;
    } else {
        pADC->ADCs[adcNumber].ADC.CR2.EXTTRIG = pADC_EXTTRIG_REG_CONV_ON_EXT_EVENT_ENABLE;
        pADC->ADCs[adcNumber].ADC.CR2.SWSTART = pADC_SWSTART_START_CONV_ON_REG_CHANNELS;
    }
    return ret;
}


Std_ReturnType
HAL_ADC_TriggerRegularConvChannel(const ADC_Number_t adcNumber, const ADC_ChannelType_Number_t channelNumber,
                                  const ADC_RegularChannelSampleTime_t sampleTime) {
    Std_ReturnType ret = E_OK;

    if ((uint32_t) adcNumber > ADC_Number_2) {
        ret = E_NOT_OK;
    } else {

        ADC_Channel_Config_t config = {0};
        config.RegularChannel.SampleTime = sampleTime;
        config.RegularChannel.SequenceNumber = 0;
        HAL_ADC_Channel_Init(adcNumber, channelNumber, config);

        if (pADC->ADCs[adcNumber].ADC.CR2.EXTTRIG != pADC_EXTTRIG_REG_CONV_ON_EXT_EVENT_ENABLE) {
            pADC->ADCs[adcNumber].ADC.CR2.EXTTRIG = pADC_EXTTRIG_REG_CONV_ON_EXT_EVENT_ENABLE;
        }

        pADC->ADCs[adcNumber].ADC.CR2.SWSTART = pADC_SWSTART_START_CONV_ON_REG_CHANNELS;
    }
    return ret;
}


Std_ReturnType HAL_ADC_TriggerInjectedConversion(const ADC_Number_t adcNumber) {
    Std_ReturnType ret = E_OK;

    if ((uint32_t) adcNumber > ADC_Number_2) {
        ret = E_NOT_OK;
    } else {
        if (pADC->ADCs[adcNumber].ADC.CR2.EXTTRIG != pADC_EXTTRIG_REG_CONV_ON_EXT_EVENT_ENABLE) {
            pADC->ADCs[adcNumber].ADC.CR2.EXTTRIG = pADC_EXTTRIG_REG_CONV_ON_EXT_EVENT_ENABLE;
        }
        pADC->ADCs[adcNumber].ADC.CR2.JSWSTART = pADC_JSWSTART_START_CONV_ON_INJ_CHANNELS;
    }
    return ret;
}

Std_ReturnType
HAL_ADC_Channel_Init(const ADC_Number_t adcNumber, ADC_ChannelType_Number_t channelNumber,
                     const ADC_Channel_Config_t config) {

    Std_ReturnType ret = E_OK;

    if (((uint32_t) adcNumber > ADC_Number_2) || ((uint32_t) channelNumber > ADC_Channel_Injected_Number_4)) {
        ret = E_NOT_OK;
    } else {

        if (channelNumber <= ADC_Channel_Regular_Number_17) {
            /* Regular channel configuration */

            /* Sample Time */
            /*
             *  Maximum Channels count in Sample Registers is 9 channels
             *  Every Sample Time Consists of 3 bits
             *  The config Designed to make the sample time in first 3 bits
             *
             */
            FORCE_MASK_OFFSET(pADC->ADCs[adcNumber].SMPRs[1 - channelNumber / (9 + 1)].REG,
                              0b111,
                              config.RegularChannel.SampleTime,
                              (channelNumber % (9 + 1)) * 3);
            /* Sequence */
            /*
             *  Maximum Channels count in Sequence Registers is 6 channels
             *  Every Sample Time Consists of 5 bits
             *  The config Designed to make the sample time in first 3 bits
             *
             *  Note: The Shifting of the Config is to Remove the first 3 bits which is Equivalent to the sample time
             */
            FORCE_MASK_OFFSET(pADC->ADCs[adcNumber].SQR[2 - config.RegularChannel.SequenceNumber / (6 + 1)].REG,
                              0b11111,
                              channelNumber,
                              (config.RegularChannel.SequenceNumber % (6 + 1)) * 5);
        } else {
            /* Important Note: This Value depends on The L in the JSQR
             *  As in reference the ADC converts */
            /* The First Channel ADC_Channel_Injected_Number_1 has value of 18, so it must be converted to 0 */
            channelNumber -= 18;

            if (pADC->ADCs[adcNumber].ADC.JSQR.JL < channelNumber) {
                ret = E_NOT_OK;
            } else {

                /* Sequence */
                /*
                 *  Maximum Channels count in Sequence Registers is 6 channels
                 *  Every Sample Time Consists of 5 bits
                 *  The config Designed to make the sample time in first 3 bits
                 *
                 *  Note: The Shifting of the Config is to Remove the first 3 bits which is Equivalent to the sample time
                 */
                FORCE_MASK_OFFSET(pADC->ADCs[adcNumber].ADC.JSQR.REG,
                                  0b11111,
                                  channelNumber,
                                  (config.InjectedChannel.SequenceNumber + 3 - pADC->ADCs[adcNumber].ADC.JSQR.JL) * 5);

                pADC->ADCs[adcNumber].JOFR[channelNumber].JOFFSET = config.InjectedChannel.negativeOffset;
            }
        }
    }
    return ret;
}

Std_ReturnType
HAL_ADC_ReadChannel(const ADC_Number_t adcNumber, ADC_ChannelReadType_t channelNumber, uint16_t *value) {
    Std_ReturnType ret = E_OK;

    if (((uint32_t) adcNumber > ADC_Number_2) || ((uint32_t) channelNumber > ADC_ChannelReadType_Injected_4) ||
        (value == NULL)) {
        ret = E_NOT_OK;
    } else {
        if (channelNumber == ADC_ChannelReadType_Regular) {
            // Read Regular Channel

            WAIT_CONDITION_OR_TIMEOUT(pADC->ADCs[adcNumber].ADC.SR.EOC == STD_ON, 1000);
            switch (adcNumber) {
                case ADC_Number_1:
                    *value = pADC->ADC1.DR.DATA;
                    break;
                case ADC_Number_2:
                    *value = pADC->ADC1.DR.ADC2DATA;
                    break;
            }


        } else {
            if (pADC->ADCs[adcNumber].ADC.JSQR.JL < channelNumber) {
                ret = E_NOT_OK;
            } else {
                WAIT_CONDITION_OR_TIMEOUT(pADC->ADCs[adcNumber].ADC.SR.JEOC == STD_ON, 1000);
                *value = pADC->ADCs[adcNumber].JDR[((3 - pADC->ADCs[adcNumber].ADC.JSQR.JL) +
                                                    (channelNumber - 1))].JDATA;
            }
        }
    }
    return ret;
}

Std_ReturnType
HAL_ADC_ReadChannelFloat(const ADC_Number_t adcNumber, ADC_ChannelReadType_t channelNumber, float *value) {
    Std_ReturnType ret = E_OK;
    uint16_t _adc_temp_value = 0;
    ret = HAL_ADC_ReadChannel(adcNumber, channelNumber, &_adc_temp_value);
    if (ret == E_OK) {
//    	sint32_t timeout = 10;
//        WAIT_CONDITION_OR_TIMEOUT_M(pADC->ADCs[adcNumber].ADC.SR.EOC == pADC_EOC_CONV_COMP, timeout)
//    	if (timeout <= 0){
//    		*value = 5;
//    	} else {
//
//    	}
        *value = 3.287f * _adc_temp_value / (0xFFE);

        pADC->ADCs[adcNumber].ADC.SR.STRT = STD_OFF;
    }
    return ret;
}


Std_ReturnType HAL_ADC_ChannelGPIOInit(const ADC_Number_t adcNumber, ADC_Channel_Number channelNumber) {
    Std_ReturnType ret = E_OK;

    if (((uint32_t) adcNumber > ADC_Number_2) || ((uint32_t) channelNumber > ADC_Channel_Number_9)) {
        ret = E_NOT_OK;
    } else {

        if (channelNumber <= ADC_Channel_Number_7) {
            HAL_GPIO_ConfigPinsDirect(PORT_ID_PORTA, 1 << channelNumber, Pin_Mode_Input, Pin_Mode_Config_INPUT_ANALOG);
        } else {
            HAL_GPIO_ConfigPinsDirect(PORT_ID_PORTB, 1 << (channelNumber - ADC_Channel_Number_8),
                                      Pin_Mode_Input, Pin_Mode_Config_INPUT_ANALOG);
        }
    }
    return ret;
}


InterruptCallback_t ADC_interruptCallbacks[] = {0, 0};

Std_ReturnType HAL_ADC_RegisterInterruptCallback(const ADC_Number_t adcNumber, const InterruptCallback_t callback) {
    Std_ReturnType ret = E_OK;

    if ((uint32_t) adcNumber > ADC_Number_2) {
        ret = E_NOT_OK;
    } else {
        ADC_interruptCallbacks[adcNumber] = callback;
    }
    return ret;
}


/**************	Section: Helper Methods Declarations  *************/


void ADC1_2_IRQHandler(void) {

    if ((ADC_interruptCallbacks[0] != NULL) && ((pADC->ADC1.SR.REG & 0b111) > 0)) {
        if (pADC->ADC1.SR.EOC == STD_HIGH) {

//            pADC->ADC1.SR.EOC = STD_LOW;
            ADC_interruptCallbacks[0](ADC_Interrupts_EndOfConversion);

        } else if (pADC->ADC1.SR.JEOC == STD_HIGH) {

//            pADC->ADC1.SR.JEOC = STD_LOW;
            ADC_interruptCallbacks[0](ADC_Interrupts_EndOfConversion_Injected);

        } else if (pADC->ADC1.SR.AWD == STD_HIGH) {

//            pADC->ADC1.SR.AWD = STD_LOW;
            ADC_interruptCallbacks[0](ADC_Interrupts_AnalogWatchDog);
        }

    }


    if ((ADC_interruptCallbacks[1] != NULL) && ((pADC->ADC2.SR.REG & 0b111) > 0)) {
        if (pADC->ADC2.SR.EOC == STD_HIGH) {

//            pADC->ADC2.SR.EOC = STD_LOW;
            ADC_interruptCallbacks[1](ADC_Interrupts_EndOfConversion);

        } else if (pADC->ADC2.SR.JEOC == STD_HIGH) {

//            pADC->ADC2.SR.JEOC = STD_LOW;
            ADC_interruptCallbacks[1](ADC_Interrupts_EndOfConversion_Injected);

        } else if (pADC->ADC2.SR.AWD == STD_HIGH) {

//            pADC->ADC2.SR.AWD = STD_LOW;
            ADC_interruptCallbacks[1](ADC_Interrupts_AnalogWatchDog);
        }

    }
}
