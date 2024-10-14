

#ifndef RCC_RCC_H_
#define RCC_RCC_H_

/**************	Section: Includes ***************************/

//#include <math.h>

#include "std_types.h"
#include "stm32f103c8t.h"
#include "std_math.h"
/**************	Section: Macro Definitions Declarations *****/

/**************	Section: Macro Functions Declarations *******/

/**************	Section: Data Types Declarations ************/




typedef enum {
    SYS_CLK_SRC_HSI = (RCC_SW_HSI),
    SYS_CLK_SRC_HSE_Crystal = (RCC_SW_HSE),
    SYS_CLK_SRC_PLL = (RCC_SW_PLL),
    // SYS_CLK_SRC_HSE_Clock = (4) ,

    SYS_CLK_SRC_InternalHighSpeed = (SYS_CLK_SRC_HSI),
    SYS_CLK_SRC_ExternalHighSpeed_Crystal = (SYS_CLK_SRC_HSE_Crystal),
    //SYS_CLK_SRC_ExternalHighSpeed_Clock = (SYS_CLK_SRC_HSE_Clock),
    SYS_CLK_SRC_PhaseLockedLoop = (SYS_CLK_SRC_PLL)

} SYSCLK_Src_t;


typedef enum {
    PLL_SRC_HSI_DIV_BY_2 = 0,
    PLL_SRC_HSE_Crystal = 1,
    PLL_SRC_HSE_Clock = 2,
} PLL_Src_t;


typedef enum {
    PLL_MUL_FACTOR_2 = (RCC_PLLMUL_MUL_BY_2),
    PLL_MUL_FACTOR_3 = (RCC_PLLMUL_MUL_BY_3),
    PLL_MUL_FACTOR_4 = (RCC_PLLMUL_MUL_BY_4),
    PLL_MUL_FACTOR_5 = (RCC_PLLMUL_MUL_BY_5),
    PLL_MUL_FACTOR_6 = (RCC_PLLMUL_MUL_BY_6),
    PLL_MUL_FACTOR_7 = (RCC_PLLMUL_MUL_BY_7),
    PLL_MUL_FACTOR_8 = (RCC_PLLMUL_MUL_BY_8),
    PLL_MUL_FACTOR_9 = (RCC_PLLMUL_MUL_BY_9),
    PLL_MUL_FACTOR_10 = (RCC_PLLMUL_MUL_BY_10),
    PLL_MUL_FACTOR_11 = (RCC_PLLMUL_MUL_BY_11),
    PLL_MUL_FACTOR_12 = (RCC_PLLMUL_MUL_BY_12),
    PLL_MUL_FACTOR_13 = (RCC_PLLMUL_MUL_BY_13),
    PLL_MUL_FACTOR_14 = (RCC_PLLMUL_MUL_BY_14),
    PLL_MUL_FACTOR_15 = (RCC_PLLMUL_MUL_BY_15),
    PLL_MUL_FACTOR_16 = (RCC_PLLMUL_MUL_BY_16)
} PLL_Mul_Factor_t;


typedef enum {

    AHB_PRESCALLER_1 = (RCC_HPRE_DIV_BY_1),
    AHB_PRESCALLER_2 = (RCC_HPRE_DIV_BY_2),
    AHB_PRESCALLER_4 = (RCC_HPRE_DIV_BY_4),
    AHB_PRESCALLER_8 = (RCC_HPRE_DIV_BY_8),
    AHB_PRESCALLER_16 = (RCC_HPRE_DIV_BY_16),
    AHB_PRESCALLER_64 = (RCC_HPRE_DIV_BY_64),
    AHB_PRESCALLER_128 = (RCC_HPRE_DIV_BY_128),
    AHB_PRESCALLER_256 = (RCC_HPRE_DIV_BY_256),
    AHB_PRESCALLER_512 = (RCC_HPRE_DIV_BY_512),

} AHB_Prescaller_t;

typedef enum {
    APB1_PRESCALLER_1 = (RCC_PPRE1_DIV_BY_1),
    APB1_PRESCALLER_2 = (RCC_PPRE1_DIV_BY_2),
    APB1_PRESCALLER_4 = (RCC_PPRE1_DIV_BY_4),
    APB1_PRESCALLER_8 = (RCC_PPRE1_DIV_BY_8),
    APB1_PRESCALLER_16 = (RCC_PPRE1_DIV_BY_16),

} APB1_Prescaller_t;

typedef enum {
    APB2_PRESCALLER_1 = (RCC_PPRE2_DIV_BY_1),
    APB2_PRESCALLER_2 = (RCC_PPRE2_DIV_BY_2),
    APB2_PRESCALLER_4 = (RCC_PPRE2_DIV_BY_4),
    APB2_PRESCALLER_8 = (RCC_PPRE2_DIV_BY_8),
    APB2_PRESCALLER_16 = (RCC_PPRE2_DIV_BY_16),
} APB2_Prescaller_t;

typedef enum {
    ADC2_PRESCALLER_2 = (RCC_ADCPRE_DIV_BY_2),
    ADC2_PRESCALLER_4 = (RCC_ADCPRE_DIV_BY_4),
    ADC2_PRESCALLER_6 = (RCC_ADCPRE_DIV_BY_6),
    ADC2_PRESCALLER_8 = (RCC_ADCPRE_DIV_BY_8),

} ADC_Prescaller_t;


typedef enum {
    PeripheralID_DMA1 = 0,
    PeripheralID_DMA2 = 1,
    PeripheralID_SRAM = 2,
    PeripheralID_FLITF = 3,
    PeripheralID_CRC = 6,
    PeripheralID_USB = 12,
    PeripheralID_ETH_MAC = 14,
    PeripheralID_ETH_MAC_TX = 15,
    PeripheralID_ETH_MAC_RX = 16,

    PeripheralID_AFIO = (32 + 0),
    PeripheralID_PORTA = (32 + 2),
    PeripheralID_PORTB = (32 + 3),
    PeripheralID_PORTC = (32 + 4),
    PeripheralID_PORTD = (32 + 5),
    PeripheralID_PORTE = (32 + 6),
    PeripheralID_ADC1 = (32 + 9),
    PeripheralID_ADC2 = (32 + 10),
    PeripheralID_TIMER1 = (32 + 11),
    PeripheralID_SPI1 = (32 + 12),
    PeripheralID_USART1 = (32 + 14),

    PeripheralID_TIMER2 = (64 + 0),
    PeripheralID_TIMER3 = (64 + 1),
    PeripheralID_TIMER4 = (64 + 2),
    PeripheralID_TIMER5 = (64 + 3),
    PeripheralID_TIMER6 = (64 + 4),
    PeripheralID_TIMER7 = (64 + 5),
    PeripheralID_WWDG = (64 + 11),
    PeripheralID_SPI2 = (64 + 14),
    PeripheralID_SPI3 = (64 + 15),
    PeripheralID_USART2 = (64 + 17),
    PeripheralID_USART3 = (64 + 18),
    PeripheralID_UART4 = (64 + 19),
    PeripheralID_UART5 = (64 + 20),
    PeripheralID_I2C1 = (64 + 21),
    PeripheralID_I2C2 = (64 + 22),
    PeripheralID_CAN1 = (64 + 25),
    PeripheralID_CAN2 = (64 + 26),
    PeripheralID_BKP_DOMAIN = (64 + 27),
    PeripheralID_PWR_INTERFACE = (64 + 28),
    PeripheralID_DAC = (64 + 29),


} PeripheralID_t;


typedef enum {
    Peripheral_State_OFF = 0,
    Peripheral_State_ON = 1,

} Peripheral_State_t;


typedef struct {
    union {
        uint32_t CPU;
        uint32_t AHB;
        uint32_t DMA1;
        uint32_t DMA2;
        uint32_t SRAM;
        uint32_t FLITF;
        uint32_t CRC;
        uint32_t USB;
        uint32_t ETH_MAC;
        uint32_t ETH_MAC_TX;
        uint32_t ETH_MAC_RX;
    };


    union {

        uint32_t APB1;

        uint32_t TIMER2;
        uint32_t TIMER3;
        uint32_t TIMER4;
        uint32_t TIMER5;
        uint32_t TIMER6;
        uint32_t TIMER7;
        uint32_t WWDG;
        uint32_t SPI2;
        uint32_t SPI3;
        uint32_t USART2;
        uint32_t USART3;
        uint32_t UART4;
        uint32_t UART5;
        uint32_t I2C;
        uint32_t I2C1;
        uint32_t I2C2;
        uint32_t CAN1;
        uint32_t CAN2;
        uint32_t BKP_DOMAIN;
        uint32_t PWR_INTERFACE;
        uint32_t DAC;
    };

    union {
        uint32_t APB2;
        uint32_t AFIO;
        uint32_t PORTA;
        uint32_t PORTB;
        uint32_t PORTC;
        uint32_t PORTD;
        uint32_t TIMER1;
        uint32_t SPI1;
        uint32_t USART1;
    };
    uint32_t ADC;

} RCC_PeripheralClock_t;


typedef union {


    SYSCLK_Src_t sys_clk_src: 2;
    struct {
        uint32_t                         : 2;
        PLL_Src_t src: 2;
        PLL_Mul_Factor_t mul_factor: 4;
    } PLL;

    struct {
        uint32_t                          : 8;
        AHB_Prescaller_t prescaller: 4;
    } AHB;

    struct {
        uint32_t                        : 12;
        APB1_Prescaller_t prescaller: 3;
    } APB1;
    struct {
        uint32_t                        : 15;
        APB2_Prescaller_t prescaller: 3;
        ADC_Prescaller_t ADC_prescaller: 2;
    } APB2;


} RCC_Config_t;

extern RCC_PeripheralClock_t System_PeripheralsClock;

/**************	Section: Methods Declarations  **************/

Std_ReturnType HAL_RCC_Init_DefaultConfigured(void);

Std_ReturnType HAL_RCC_Init(const RCC_Config_t *config);

Std_ReturnType HAL_RCC_ChangePeripheralCLKState(const PeripheralID_t id, const Peripheral_State_t state);

Std_ReturnType HAL_RCC_ReadPeripheralCLKState(const PeripheralID_t id, Peripheral_State_t *state);
//Std_ReturnType HAL_RCC_ChangePrescallersConfigurations(void);

RCC_PeripheralClock_t HAL_RCC_UpdateSystemClockValues(void);


Std_ReturnType HAL_RCC_ResetAllAPBPeripherals(void);

#endif /* RCC_RCC_H_ */
