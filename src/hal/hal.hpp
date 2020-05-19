
#pragma once
#include <cstdint>
#include "platform/platform.hpp"
namespace eel::hal {
namespace literals{
std::uint32_t operator"" _ticks(unsigned long long t) {
  return static_cast<std::uint32_t>(t);
}
std::uint32_t operator"" _ms(unsigned long long t) {
  return static_cast<std::uint32_t>(t);
}
std::uint32_t operator"" _s(unsigned long long t) {
  return static_cast<std::uint32_t>(t*1000);
}
}
inline void init() {
  return eel::hal::ll::init();
}
inline void delay(std::uint32_t ticks) {
  eel::hal::ll::delay(ticks);
}
};
