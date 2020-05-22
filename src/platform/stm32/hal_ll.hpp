#pragma once
#include <cstdint>
#include "platform/stm32/stm32_hal.hpp"

namespace eel::hal::ll {
  inline void init() {
    HAL_Init();
  }

  inline void delay(std::uint32_t ticks) {
    HAL_Delay(ticks);
  }
}
