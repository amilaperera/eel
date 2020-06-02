#pragma once

#include "ots/FreeRTOS/Source/include/FreeRTOS.h"
#include <type_traits>

namespace eel::utils::os_wrapper {
using base_t = UBaseType_t;
using tick_t = TickType_t;

struct priority {
  using type = UBaseType_t;
  constexpr explicit priority(type p) : p_(p) {}
  [[nodiscard]] constexpr type value() const {return p_;}
 private:
  type p_;
};

struct stack_size {
  using type = StackType_t;
  constexpr explicit stack_size(type s) : sz_(s) {}
  [[nodiscard]] constexpr type value() const {return sz_;}
 private:
  type sz_;
};

namespace literals {
constexpr inline auto operator"" _ws(unsigned long long sz) {
  return stack_size(static_cast<stack_size::type>(sz));
}

constexpr inline auto operator"" _bs(unsigned long long sz) {
  return stack_size(static_cast<stack_size::type>(sz)/sizeof(stack_size::type));
}
}
}
