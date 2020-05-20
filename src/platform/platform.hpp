
#pragma once
#include "platform/eel_config.hpp"
#include "platform/eel_hal_common_defs.hpp"

#if defined(EEL_STM32F446XX)
#include "ots/stm32_cube/f4/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal.h"
#include "platform/stm32/common.hpp"
#include "platform/stm32/f4/mcu_defs.hpp"
#if defined(HAL_GPIO_MODULE_ENABLED)
#include "platform/stm32/gpio.hpp"
#endif
#if defined(HAL_UART_MODULE_ENABLED)
#include "platform/stm32/uart.hpp"
#endif
#endif

