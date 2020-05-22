
#pragma once
#include "platform/stm32/stm32_hal.hpp"

#if defined(EEL_STM32F446XX)
#if defined(HAL_GPIO_MODULE_ENABLED)
#include "platform/stm32/gpio.hpp"
#endif
#if defined(HAL_UART_MODULE_ENABLED)
#include "platform/stm32/uart.hpp"
#endif
#endif
