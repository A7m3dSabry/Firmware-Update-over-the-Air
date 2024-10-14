//
// Created by J on 1/15/2024.
//

#ifndef STM32_DRIVERS_USART_CFG_H
#define STM32_DRIVERS_USART_CFG_H

#include "usart.h"
#include "rcc.h"
#include "rcc_cfg.h"

#define USART_CFG_MAX_TIMEOUT        (1000)
#define USART_CFG_INF_TIMEOUT        (TIMEOUT_INF)

#define USART_CFG_BAUDRATE(baud)    (CPU_FREQ/(8.0*(baud)))

#endif //STM32_DRIVERS_USART_CFG_H
