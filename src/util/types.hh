#pragma once
#include <cstdint>
#include <type_traits>

namespace eel::util {
using U32 = std::uint32_t;
using IO_U32 = volatile U32;

using U16 = std::uint16_t;
using IO_U16 = volatile U16;

using U8 = std::uint8_t;
using IO_U8 = volatile U8;

template <typename E>
constexpr auto ToInt(E e) {
  return static_cast<typename std::underlying_type<E>::type>(e);
}

}
