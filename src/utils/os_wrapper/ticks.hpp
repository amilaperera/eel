#pragma once
#include "ots/FreeRTOS/Source/include/FreeRTOS.h"
#include "utils/os_wrapper/free_rtos_types.hpp"

namespace eel::utils::os_wrapper {

struct time_ticks {
  tick_t ticks;
};

inline constexpr time_ticks max_ticks() {
  return { portMAX_DELAY };
}

inline time_ticks tick_count() {
  return { xTaskGetTickCount() };
}

namespace literals {
  // user-defined literals that are helpful when passing ticks
  // as an argument

  // raw tick count
  constexpr time_ticks operator"" _ticks(unsigned long long ticks) {
    return { static_cast<tick_t>(ticks) };
  }

  // milliseconds -> ticks conversion
  constexpr time_ticks operator"" _ms(unsigned long long ms) {
    return { static_cast<tick_t>(ms / portTICK_PERIOD_MS)};
  }

  // seconds -> ticks conversion
  constexpr time_ticks operator"" _s(unsigned long long secs) {
    return { static_cast<tick_t>(secs * 1000 / portTICK_PERIOD_MS) };
  }
  // TOOD operator+
}
}
