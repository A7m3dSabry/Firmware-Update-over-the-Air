


#ifndef STM32_DRIVERS_NVIC_H
#define STM32_DRIVERS_NVIC_H


/**************	Section: Includes ***************************/

#include "std_types.h"
#include "stm32f103c8t.h"
#include "nvic_cfg.h"

/**************	Section: Macro Definitions Declarations *****/
/**************	Section: Macro Functions Declarations *******/
/**************	Section: Data Types Declarations ************/

typedef enum {
    IRQn_WWDG = (pNVIC_IRQn_WWDG),
    IRQn_PVD = (pNVIC_IRQn_PVD),
    IRQn_TAMPER = (pNVIC_IRQn_TAMPER),
    IRQn_RTC = (pNVIC_IRQn_RTC),
    IRQn_FLASH = (pNVIC_IRQn_FLASH),
    IRQn_RCC = (pNVIC_IRQn_RCC),
    IRQn_EXTI0 = (pNVIC_IRQn_EXTI0),
    IRQn_EXTI1 = (pNVIC_IRQn_EXTI1),
    IRQn_EXTI2 = (pNVIC_IRQn_EXTI2),
    IRQn_EXTI3 = (pNVIC_IRQn_EXTI3),
    IRQn_EXTI4 = (pNVIC_IRQn_EXTI4),
    IRQn_DMA1_Channel1 = (pNVIC_IRQn_DMA1_Channel1),
    IRQn_DMA1_Channel2 = (pNVIC_IRQn_DMA1_Channel2),
    IRQn_DMA1_Channel3 = (pNVIC_IRQn_DMA1_Channel3),
    IRQn_DMA1_Channel4 = (pNVIC_IRQn_DMA1_Channel4),
    IRQn_DMA1_Channel5 = (pNVIC_IRQn_DMA1_Channel5),
    IRQn_DMA1_Channel6 = (pNVIC_IRQn_DMA1_Channel6),
    IRQn_DMA1_Channel7 = (pNVIC_IRQn_DMA1_Channel7),
    IRQn_ADC1_2 = (pNVIC_IRQn_ADC1_2),
    IRQn_CAN1_TX = (pNVIC_IRQn_CAN1_TX),
    IRQn_CAN1_RX0 = (pNVIC_IRQn_CAN1_RX0),
    IRQn_CAN1_RX1 = (pNVIC_IRQn_CAN1_RX1),
    IRQn_CAN1_SCE = (pNVIC_IRQn_CAN1_SCE),
    IRQn_EXTI9_5 = (pNVIC_IRQn_EXTI9_5),
    IRQn_TIM1_BRK = (pNVIC_IRQn_TIM1_BRK),
    IRQn_TIM1_UP = (pNVIC_IRQn_TIM1_UP),
    IRQn_TIM1_TRG_COM = (pNVIC_IRQn_TIM1_TRG_COM),
    IRQn_TIM1_CC = (pNVIC_IRQn_TIM1_CC),
    IRQn_TIM2 = (pNVIC_IRQn_TIM2),
    IRQn_TIM3 = (pNVIC_IRQn_TIM3),
    IRQn_TIM4 = (pNVIC_IRQn_TIM4),
    IRQn_I2C1_EV = (pNVIC_IRQn_I2C1_EV),
    IRQn_I2C1_ER = (pNVIC_IRQn_I2C1_ER),
    IRQn_I2C2_EV = (pNVIC_IRQn_I2C2_EV),
    IRQn_I2C2_ER = (pNVIC_IRQn_I2C2_ER),
    IRQn_SPI1 = (pNVIC_IRQn_SPI1),
    IRQn_SPI2 = (pNVIC_IRQn_SPI2),
    IRQn_USART1 = (pNVIC_IRQn_USART1),
    IRQn_USART2 = (pNVIC_IRQn_USART2),
    IRQn_USART3 = (pNVIC_IRQn_USART3),
    IRQn_EXTI15_10 = (pNVIC_IRQn_EXTI15_10),
    IRQn_RTCAlarm = (pNVIC_IRQn_RTCAlarm),
    IRQn_OTG_FS_WKUP = (pNVIC_IRQn_OTG_FS_WKUP),
    IRQn_TIM5 = (pNVIC_IRQn_TIM5),
    IRQn_SPI3 = (pNVIC_IRQn_SPI3),
    IRQn_UART4 = (pNVIC_IRQn_UART4),
    IRQn_UART5 = (pNVIC_IRQn_UART5),
    IRQn_TIM6 = (pNVIC_IRQn_TIM6),
    IRQn_TIM7 = (pNVIC_IRQn_TIM7),
    IRQn_DMA2_Channel1 = (pNVIC_IRQn_DMA2_Channel1),
    IRQn_DMA2_Channel2 = (pNVIC_IRQn_DMA2_Channel2),
    IRQn_DMA2_Channel3 = (pNVIC_IRQn_DMA2_Channel3),
    IRQn_DMA2_Channel4 = (pNVIC_IRQn_DMA2_Channel4),
    IRQn_DMA2_Channel5 = (pNVIC_IRQn_DMA2_Channel5),
    IRQn_ETH = (pNVIC_IRQn_ETH),
    IRQn_ETH_WKUP = (pNVIC_IRQn_ETH_WKUP),
    IRQn_CAN2_TX = (pNVIC_IRQn_CAN2_TX),
    IRQn_CAN2_RX0 = (pNVIC_IRQn_CAN2_RX0),
    IRQn_CAN2_RX1 = (pNVIC_IRQn_CAN2_RX1),
    IRQn_CAN2_SCE = (pNVIC_IRQn_CAN2_SCE),
    IRQn_OTG_FS = (pNVIC_IRQn_OTG_FS)
} IRQn_t;

typedef enum {
    InterruptState_Disable = (STD_OFF),
    InterruptState_Enable = (STD_ON),
} InterruptState_t;
typedef enum {
    InterruptPendingState_Disable = (STD_OFF),
    InterruptPendingState_Enable = (STD_ON),
} InterruptPendingState_t;

typedef enum {
    InterruptPriorityGroup_Group0 = (SCB_PRIORITY_GROUP0),
    InterruptPriorityGroup_Group1 = (SCB_PRIORITY_GROUP1),
    InterruptPriorityGroup_Group2 = (SCB_PRIORITY_GROUP2),
    InterruptPriorityGroup_Group3 = (SCB_PRIORITY_GROUP3),
    InterruptPriorityGroup_Group4 = (SCB_PRIORITY_GROUP4),
    InterruptPriorityGroup_Group5 = (SCB_PRIORITY_GROUP5),
    InterruptPriorityGroup_Group6 = (SCB_PRIORITY_GROUP6),
    InterruptPriorityGroup_Group7 = (SCB_PRIORITY_GROUP7)
}InterruptGroupPriority_t;


/**************	Section: Methods Declarations  **************/

Std_ReturnType HAL_NVIC_ChangeInterruptState(const IRQn_t IRQn, const InterruptState_t state);
Std_ReturnType HAL_NVIC_ReadInterruptState(const IRQn_t IRQn, InterruptState_t *state);
Std_ReturnType HAL_NVIC_ChangeInterruptPendingState(const IRQn_t IRQn, const InterruptPendingState_t state);
Std_ReturnType HAL_NVIC_ReadInterruptPendingState(const IRQn_t IRQn, InterruptPendingState_t *state);

Std_ReturnType HAL_NVIC_ChangeInterruptPriority(const IRQn_t IRQn, const uint8_t priority);
Std_ReturnType HAL_NVIC_ReadInterruptPriority(const IRQn_t IRQn, uint8_t *priority);

Std_ReturnType HAL_NVIC_ChangeInterruptGroupPriority(const InterruptGroupPriority_t groupPriority);
Std_ReturnType HAL_NVIC_ReadInterruptGroupPriority(InterruptGroupPriority_t *groupPriority);

Std_ReturnType HAL_NVIC_IsInterruptActive(const IRQn_t IRQn, uint8_t *active);

Std_ReturnType HAL_NVIC_GenerateSoftwareInterrupt(const IRQn_t IRQn);
void HAL_NVIC_SystemReset(void);
#endif //STM32_DRIVERS_NVIC_H
