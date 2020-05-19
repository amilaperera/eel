//
// Created by amila.perera on 16/05/2020.
//

#pragma once
#include <cstdint>
#include "platform/platform.hpp"

namespace eel::hal::ll {
  inline void init() {
    HAL_Init();
  }

  inline void delay(std::uint32_t ticks) {
    HAL_Delay(ticks);
  }
}
