#pragma once
#include "ots/FreeRTOS/Source/include/FreeRTOS.h"

namespace eel::utils::os_wrapper {

constexpr TickType_t max_ticks() {
  return portMAX_DELAY;
}

inline TickType_t tick_count() {
  return xTaskGetTickCount();
}

namespace literals {
  // user-defined literals that are helpful when passing ticks
  // as an argument

  // raw tick count
  constexpr TickType_t operator"" _ticks(unsigned long long ticks) {
    return static_cast<TickType_t>(ticks);
  }

  // milliseconds -> ticks conversion
  constexpr TickType_t operator"" _ms(unsigned long long ticks) {
    return static_cast<TickType_t>(ticks)/portTICK_PERIOD_MS;
  }

  // seconds -> ticks conversion
  constexpr TickType_t operator"" _s(unsigned long long ticks) {
    return static_cast<TickType_t>(ticks)/portTICK_PERIOD_MS * 1000;
  }
  // TOOD operator+
}
}
