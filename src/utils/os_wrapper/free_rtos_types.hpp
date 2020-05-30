#pragma once

#include "ots/FreeRTOS/Source/include/FreeRTOS.h"

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

struct word_size {
  using type = unsigned short;
  constexpr explicit word_size(type s) : sz_(s) {}
  [[nodiscard]] constexpr type value() const {return sz_;}
 private:
  type sz_;
};

struct byte_size {
  using type = UBaseType_t;
  constexpr explicit byte_size(type s) : sz_(s) {}
  [[nodiscard]] constexpr type value() const {return sz_/sizeof(StackType_t);}
 private:
  type sz_;
};

template <typename T>
struct stack_size {
  constexpr explicit stack_size(T s) : sz_(s) {}
  [[nodiscard]] constexpr typename T::type value() const {return sz_.value();}
 private:
  T sz_;
};

template <typename T>
constexpr inline stack_size<T> make_stack_size(T sz) {
  return stack_size<T>(sz);
}
namespace literals {
constexpr inline auto operator"" _ws(unsigned long long sz) {
  return make_stack_size(word_size(sz));
}

constexpr inline auto operator"" _bs(unsigned long long sz) {
  return make_stack_size(byte_size(sz));
}
}
static constexpr stack_size min_stack_size{make_stack_size(word_size(configMINIMAL_STACK_SIZE))};
}
