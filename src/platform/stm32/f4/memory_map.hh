#pragma once

/*
 * pages 56,57 of stm32f446ze reference manual
 */
#define EEL_PERIPHERAL_BASE   (0x40000000U)
#define EEL_APB1_BASE         (EEL_PERIPHERAL_BASE)
#define EEL_APB2_BASE         (EEL_PERIPHERAL_BASE + 0x10000)
#define EEL_AHB1_BASE         (EEL_PERIPHERAL_BASE + 0x20000)
// GPIO A-H
#define EEL_GPIOA_BASE        (EEL_AHB1_BASE + 0x0000)
#define EEL_GPIOB_BASE        (EEL_AHB1_BASE + 0x0400)
#define EEL_GPIOC_BASE        (EEL_AHB1_BASE + 0x0800)
#define EEL_GPIOD_BASE        (EEL_AHB1_BASE + 0x0C00)
#define EEL_GPIOE_BASE        (EEL_AHB1_BASE + 0x1000)
#define EEL_GPIOF_BASE        (EEL_AHB1_BASE + 0x1400)
#define EEL_GPIOG_BASE        (EEL_AHB1_BASE + 0x1800)
#define EEL_GPIOH_BASE        (EEL_AHB1_BASE + 0x1C00)
// CRC
#define EEL_CRC_BASE          (EEL_AHB1_BASE + 0x3000)
// RCC
#define EEL_RCC_BASE          (EEL_AHB1_BASE + 0x3800)
// USART
#define EEL_USART1_BASE       (EEL_APB2_BASE + 0x1000)
#define EEL_USART2_BASE       (EEL_APB1_BASE + 0x4400)
#define EEL_USART3_BASE       (EEL_APB1_BASE + 0x4800)
#define EEL_UART4_BASE        (EEL_APB1_BASE + 0x4C00)
#define EEL_UART5_BASE        (EEL_APB1_BASE + 0x5000)
#define EEL_USART6_BASE       (EEL_APB2_BASE + 0x1400)
// EXTI
#define EEL_EXTI_BASE         (EEL_APB2_BASE + 0x3C00)
// SYSCFG
#define EEL_SYSCFG_BASE       (EEL_APB2_BASE + 0x3800)

