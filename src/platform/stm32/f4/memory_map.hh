#pragma once

/*
 * pages 56,57 of stm32f446ze reference manual
 */
#define EEL_PERIPHERAL_BASE   (0x40000000U)
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

