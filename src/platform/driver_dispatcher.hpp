
#pragma once
#include "platform/stm32/stm32_hal.hpp"

#if defined(HAL_GPIO_MODULE_ENABLED)
#include "platform/stm32/gpio.hpp"
#include "platform/stm32/gpio_interrupt.hpp"
#endif
#if defined(HAL_UART_MODULE_ENABLED)
#include "platform/stm32/uart.hpp"
#endif
