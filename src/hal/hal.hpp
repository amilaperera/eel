
#pragma once
#include "platform/platform.hpp"
#include <cstdint>
namespace eel::hal {
struct time_ticks {
  std::uint32_t tick_count;
};
namespace literals{
inline eel::hal::time_ticks operator"" _ticks(unsigned long long t) {
  return {static_cast<std::uint32_t>(t)};
}
inline eel::hal::time_ticks operator"" _ms(unsigned long long t) {
  return {static_cast<std::uint32_t>(t)};
}
inline eel::hal::time_ticks operator"" _s(unsigned long long t) {
  return {static_cast<std::uint32_t>(t*1000)};
}
}
inline void init() {
  return eel::hal::ll::init();
}
inline void delay(eel::hal::time_ticks ticks) {
  eel::hal::ll::delay(ticks.tick_count);
}
}
