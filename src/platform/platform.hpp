
#pragma once
#include "platform/eel_config.hpp"

#include "platform/stm32/stm32_hal.hpp"
#include "platform/stm32/hal_ll.hpp"
#if defined(EEL_STM32F446XX)
#include "platform/stm32/f4/mcu_defs.hpp"
#elif defined(EEL_STM32F103XX)
#include "platform/stm32/f1/mcu_defs.hpp"
#endif

