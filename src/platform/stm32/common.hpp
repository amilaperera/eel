//
// Created by amila.perera on 16/05/2020.
//

#pragma once
#include "platform/platform.hpp"

namespace eel::hal::ll {
  inline void init() {
    HAL_Init();
  }
}
