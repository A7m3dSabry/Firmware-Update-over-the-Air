
#ifndef RCC_RCC_CFG_H_
#define RCC_RCC_CFG_H_


/**************	Section: Includes **********************************/
#include "rcc.h"
#include "std_math.h"


/**************	Section: Macro configurations Declarations ********/

#define RCC_CFG_RDY_WAIT_TIME       (10000)
#define RCC_CFG_SYSCLK_SRC          (SYS_CLK_SRC_InternalHighSpeed)

#define RCC_CFG_PLL_SRC             (PLL_SRC_HSI_DIV_BY_2)
#define RCC_CFG_PLL_MUL_FACTOR      (PLL_MUL_FACTOR_2)

#define RCC_CFG_AHB_PRESCALLER      (AHB_PRESCALLER_1)
#define RCC_CFG_APB1_PRESCALLER     (APB1_PRESCALLER_1)
#define RCC_CFG_APB2_PRESCALLER     (APB2_PRESCALLER_1)

#define RCC_CFG_CLK_SRC_InternalHighSpeed_FREQ       (8000000UL)
#define RCC_CFG_CLK_SRC_ExternalHighSpeed_FREQ       (0UL)
#define RCC_CFG_CLK_SRC_ExternalLowSpeed_FREQ        (0UL)

#ifndef CPU_FREQ
    #if    (RCC_CFG_SYSCLK_SRC == SYS_CLK_SRC_InternalHighSpeed)
        #define CPU_FREQ    (RCC_CFG_CLK_SRC_InternalHighSpeed_FREQ)

    #elif  ((RCC_CFG_SYSCLK_SRC == SYS_CLK_SRC_ExternalHighSpeed_Crystal) || (RCC_CFG_SYSCLK_SRC == SYS_CLK_SRC_ExternalHighSpeed_Clock))
        #define CPU_FREQ        (RCC_CFG_CLK_SRC_ExternalHighSpeed_FREQ)

    #elif  (RCC_CFG_SYSCLK_SRC == SYS_CLK_SRC_PhaseLockedLoop)

        #if (RCC_CFG_PLL_SRC == PLL_SRC_HSI_DIV_BY_2 )
            #define CPU_FREQ        (RCC_CFG_CLK_SRC_InternalHighSpeed_FREQ/2 * RCC_CFG_PLL_MUL_FACTOR )
        #elif  (( RCC_CFG_PLL_SRC == PLL_SRC_HSE_Crystal) || (RCC_CFG_PLL_SRC == PLL_SRC_HSE_Clock ))
            #define CPU_FREQ        (RCC_CFG_CLK_SRC_ExternalHighSpeed_FREQ * RCC_CFG_PLL_MUL_FACTOR )
        #endif
    #else

        #error "Unknown Clock Soruce"

    #endif

#endif
/**************	Section: Variable configurations Declarations *****/


#endif /* RCC_RCC_CFG_H_ */
