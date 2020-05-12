#pragma once
#include "ots/FreeRTOS/Source/include/FreeRTOS.h"
#include "utils/os_wrapper/free_rtos_types.hh"

namespace eel::utils::os_wrapper {

constexpr tick_t max_ticks() {
  return portMAX_DELAY;
}

inline tick_t tick_count() {
  return xTaskGetTickCount();
}

namespace literals {
  // user-defined literals that are helpful when passing ticks
  // as an argument

  // raw tick count
  constexpr tick_t operator"" _ticks(unsigned long long ticks) {
    return static_cast<tick_t>(ticks);
  }

  // milliseconds -> ticks conversion
  constexpr tick_t operator"" _ms(unsigned long long ticks) {
    return static_cast<tick_t>(ticks)/portTICK_PERIOD_MS;
  }

  // seconds -> ticks conversion
  constexpr tick_t operator"" _s(unsigned long long ticks) {
    return static_cast<tick_t>(ticks)/portTICK_PERIOD_MS * 1000;
  }
  // TOOD operator+
}
}
