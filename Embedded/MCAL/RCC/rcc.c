

/**************	Section: Includes *********************************/
#include "rcc.h"
#include "rcc_cfg.h"

/**************	Section: Global Variables Declarations *************/
RCC_PeripheralClock_t System_PeripheralsClock = {0};
/**************	Section: Local Variables Declarations *************/


typedef enum {
    Wait_Flag_HSI,
    Wait_Flag_HSE,
    Wait_Flag_PLL
} Wait_Flag_t;

/**************	Section: Local Methods Prototype Declarations *****/
Std_ReturnType RCC_WaitForReadyFlag(Wait_Flag_t flag);

/**************	Section: Methods Declarations *********************/



Std_ReturnType HAL_RCC_Init_DefaultConfigured(void) {
    Std_ReturnType ret = E_NOT_OK;
    RCC_Config_t config;

    config.sys_clk_src = RCC_CFG_SYSCLK_SRC;

    config.PLL.src = RCC_CFG_PLL_SRC;
    config.PLL.mul_factor = RCC_CFG_PLL_MUL_FACTOR;

    config.AHB.prescaller = RCC_CFG_AHB_PRESCALLER;

    config.APB1.prescaller = RCC_CFG_APB1_PRESCALLER;
    config.APB2.prescaller = RCC_CFG_APB2_PRESCALLER;


    ret = HAL_RCC_Init(&config);
    return ret;
}

Std_ReturnType HAL_RCC_Init(const RCC_Config_t *config) {
    Std_ReturnType ret = E_OK;

    if (config == NULL) {
        ret = E_NOT_OK;
    } else {
        if ((uint32_t) config->sys_clk_src > SYS_CLK_SRC_PLL) {
            ret = E_NOT_OK;
        } else {

            RCC->CFGR.SW = config->sys_clk_src;

            /* Check Selected Clock Source */
            if (config->sys_clk_src == SYS_CLK_SRC_HSI) {
                /* Internal High Speed Source Selected */

                /* Configuring TRIM Value With Default One */
                RCC->CR.HSITRIM = RCC_HSITRIM_DEFAULT;

                /* Enable Internal Oscillator */
                RCC->CR.HSION = RCC_HSION_ENABLE;

                ret = RCC_WaitForReadyFlag(Wait_Flag_HSI);

            } else if (config->sys_clk_src == SYS_CLK_SRC_HSE_Crystal) {
                /* External Crystal Source Selected */

                RCC->CR.HSEBYP = RCC_HSEBYP_DONT_BYPASS;
                RCC->CR.HSEON = RCC_HSEON_ENABLE;
                ret = RCC_WaitForReadyFlag(Wait_Flag_HSE);

//            } else if (config->sys_clk_src == SYS_CLK_SRC_HSE_Clock) {
//              // TODO: RCC add modification for HSE clock bypass
//                /* External Clock Source Selected */
//                RCC->CR.HSEBYP = RCC_HSEBYP_BYPASS;
//                RCC->CR.HSEON = RCC_HSEON_ENABLE;
//                ret = RCC_WaitForReadyFlag(Wait_Flag_HSE);

            } else if ((config->sys_clk_src == SYS_CLK_SRC_PLL) && (config->PLL.src <= 2)) {
                /* Phase Locked Loop Source Selected */


                if (config->PLL.src == PLL_SRC_HSI_DIV_BY_2) {

                    RCC->CR.HSITRIM = RCC_HSITRIM_DEFAULT;
                    RCC->CR.HSION = RCC_HSION_ENABLE;
                    ret = RCC_WaitForReadyFlag(Wait_Flag_HSI);

                } else if (config->PLL.src == PLL_SRC_HSE_Crystal) {
                    RCC->CR.HSEBYP = RCC_HSEBYP_DONT_BYPASS;
                    RCC->CR.HSEON = RCC_HSEON_ENABLE;
                    ret = RCC_WaitForReadyFlag(Wait_Flag_HSE);
                } else if (config->PLL.src == PLL_SRC_HSE_Clock) {
                    RCC->CR.HSEBYP = RCC_HSEBYP_BYPASS;
                    RCC->CR.HSEON = RCC_HSEON_ENABLE;
                    ret = RCC_WaitForReadyFlag(Wait_Flag_HSE);
                }

                if (ret == E_OK) {

                    RCC->CFGR.PLLSRC = config->PLL.src;
                    RCC->CFGR.PLLMUL = config->PLL.mul_factor;
                    RCC->CR.PLLON = RCC_PLLON_ENABLE;
                    ret = RCC_WaitForReadyFlag(Wait_Flag_PLL);
                }

            } else {
                ret = E_NOT_OK;
            }
            HAL_RCC_UpdateSystemClockValues();
        }
    }
    return ret;
}

Std_ReturnType HAL_RCC_ChangePeripheralCLKState(const PeripheralID_t id, const Peripheral_State_t state) {

    Std_ReturnType ret = E_OK;
    if ((uint32_t) id > PeripheralID_DAC) {
        ret = E_NOT_OK;
    } else {
        FORCE_BIT(RCC->ClockEnableRegisters[((uint32_t) id) / 32].REG, ((uint32_t) id) % 32, (uint32_t) state);
    }
    return ret;
}


Std_ReturnType HAL_RCC_ResetAllAPBPeripherals(){


	/* Reset all peripherals on APB1 */
	RCC->APB1RSTR.REG = 0xFFFFFFFF; // Reset all APB1 peripherals

	/* Reset all peripherals on APB2 */
	RCC->APB2RSTR.REG = 0xFFFFFFFF; // Reset all APB2 peripherals



	return E_OK;


}
Std_ReturnType HAL_RCC_ReadPeripheralCLKState(const PeripheralID_t id, Peripheral_State_t *state) {

    Std_ReturnType ret = E_OK;
    if ((uint32_t) id > PeripheralID_DAC) {
        ret = E_NOT_OK;
    } else {
        *state = READ_BIT(RCC->ClockEnableRegisters[((uint32_t) id) / 32].REG, ((uint32_t) id) % 32);
    }
    return ret;
}




RCC_PeripheralClock_t HAL_RCC_UpdateSystemClockValues(void) {

    RCC_PeripheralClock_t ret = {0};
    uint32_t systemFrequency = 0;
    uint8_t temp = 0;
    uint8_t pllMull = 0;
    switch (RCC->CFGR.SWS) {

        case SYS_CLK_SRC_HSI:
            systemFrequency = CPU_FREQ;
            break;
        case SYS_CLK_SRC_HSE_Crystal:
            systemFrequency = RCC_CFG_CLK_SRC_ExternalHighSpeed_FREQ;
            break;
        case SYS_CLK_SRC_PLL:


            pllMull = RCC->CFGR.PLLMUL + 2;
            if (pllMull > 16) {
                pllMull = 16;
            }


            if (RCC->CFGR.PLLSRC == RCC_PLLSRC_HSI_DIV_BY_2) {
                systemFrequency = CPU_FREQ / 2;
            } else {
                systemFrequency = RCC_CFG_CLK_SRC_ExternalHighSpeed_FREQ;
            }
            systemFrequency *= pllMull;
            break;
        default:
            ret.CPU = 0;
    }

    if ((RCC->CFGR.HPRE <= RCC_HPRE_DIV_BY_1)) {
        temp = 0;
    } else if (RCC->CFGR.HPRE <= RCC_HPRE_DIV_BY_16) {
        temp = RCC->CFGR.HPRE - 7;
    } else {
        temp = RCC->CFGR.HPRE - 6;
    }


    ret.CPU = systemFrequency / (1<<temp);

    if (RCC->CFGR.PPRE1 <= 3 ){
    	temp = 0;
    } else{
    	temp = RCC->CFGR.PPRE1 - 3;
    }
    ret.APB1 = ret.CPU / (1<<temp);   // RCC_PPRE1_DIV_BY_1 = 3

    if (RCC->CFGR.PPRE2 <= 3 ){
       	temp = 0;
       } else{
       	temp = RCC->CFGR.PPRE2 - 3;
       }


    ret.APB2 = ret.CPU / (1<<temp);   // RCC_PPRE2_DIV_BY_1 = 3
    ret.ADC = ret.APB2 / (2 * (RCC->CFGR.ADCPRE + 1));

    System_PeripheralsClock = ret;

    return ret;
}

/**************	Section: Helper Methods Declarations  *************/



Std_ReturnType RCC_WaitForReadyFlag(Wait_Flag_t flag) {

    Std_ReturnType ret = E_NOT_OK;
    uint8_t POS = 0;
    if (flag == Wait_Flag_HSE) {
        POS = 17;
    } else if (flag == Wait_Flag_HSI) {
        POS = 1;
    } else if (flag == Wait_Flag_PLL) {
        POS = 25;
    }

    uint32_t TimeOutCounter = 0;
    while ((TimeOutCounter++ < RCC_CFG_RDY_WAIT_TIME) && ~((RCC->CR.REG) & (1 << POS))) {
        TimeOutCounter = TimeOutCounter;
        /* Do Nothing */ }

    if (RCC->CR.HSIRDY == RCC_HSIRDY_NOT_READY) {
        ret = E_NOT_OK;
    } else {
        ret = E_OK;
    }
    return ret;
}
