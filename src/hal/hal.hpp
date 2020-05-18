//
// Created by amila.perera on 16/05/2020.
//

#pragma once
#include "platform/platform.hpp"
namespace eel::hal {
  inline void init() {
    return eel::hal::ll::init();
  }
};
