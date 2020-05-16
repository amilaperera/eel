//
// Created by amila.perera on 16/05/2020.
//

#pragma once
#include "platform/eel_config.hpp"

namespace eel::ll {
  inline void init() {
    HAL_Init();
  }
}
