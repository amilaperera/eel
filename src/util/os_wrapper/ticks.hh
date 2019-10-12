#pragma once
#include "ots/FreeRTOS/Source/include/FreeRTOS.h"

namespace eel::util::os_wrapper {
struct Ticks{
  TickType_t ticks_;
};

namespace literals {
  constexpr Ticks operator"" _ms(unsigned long long ticks) {
    return {static_cast<TickType_t>(ticks)/portTICK_PERIOD_MS};
  }
  constexpr Ticks operator"" _s(unsigned long long ticks) {
    return {static_cast<TickType_t>(ticks)/portTICK_PERIOD_MS * 1000};
  }
  constexpr Ticks operator"" _ticks(unsigned long long ticks) {
    return {static_cast<TickType_t>(ticks)};
  }
  // TOOD operator+
}
}
