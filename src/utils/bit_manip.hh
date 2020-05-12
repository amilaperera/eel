#pragma once

#include "utils/types.hh"

namespace eel::utils {
constexpr U8 kBit0 = (1UL << 0);
constexpr U8 kBit1 = (1UL << 1);
constexpr U8 kBit2 = (1UL << 2);
constexpr U8 kBit3 = (1UL << 3);
constexpr U8 kBit4 = (1UL << 4);
constexpr U8 kBit5 = (1UL << 5);
constexpr U8 kBit6 = (1UL << 6);
constexpr U8 kBit7 = (1UL << 7);
constexpr U16 kBit8 = (1UL << 8);
constexpr U16 kBit9 = (1UL << 9);
constexpr U16 kBit10 = (1UL << 10);
constexpr U16 kBit11 = (1UL << 11);
constexpr U16 kBit12 = (1UL << 12);
constexpr U16 kBit13 = (1UL << 13);
constexpr U16 kBit14 = (1UL << 14);
constexpr U16 kBit15 = (1UL << 15);
constexpr U32 kBit16 = (1UL << 16);
constexpr U32 kBit17 = (1UL << 17);
constexpr U32 kBit18 = (1UL << 18);
constexpr U32 kBit19 = (1UL << 19);
constexpr U32 kBit20 = (1UL << 20);
constexpr U32 kBit21 = (1UL << 21);
constexpr U32 kBit22 = (1UL << 22);
constexpr U32 kBit23 = (1UL << 23);
constexpr U32 kBit24 = (1UL << 24);
constexpr U32 kBit25 = (1UL << 25);
constexpr U32 kBit26 = (1UL << 26);
constexpr U32 kBit27 = (1UL << 27);
constexpr U32 kBit28 = (1UL << 28);
constexpr U32 kBit29 = (1UL << 29);
constexpr U32 kBit30 = (1UL << 30);
constexpr U32 kBit31 = (1UL << 31);

template <typename T>
constexpr auto SetBit(T val, eel::utils::U32 n) {
  return val | (1UL << n);
}

template <typename T>
constexpr auto ClearBit(T val, eel::utils::U32 n) {
  return val & ~(1UL << n);
}

template <typename T>
constexpr auto SetOrClearBit(bool status, T val, eel::utils::U32 n) {
  return status ? (val | (1UL << n)) : (val & ~(1UL << n));
}

template <typename T>
constexpr bool IsSet(T val, eel::utils::U32 n) {
  return (val & (1UL << n)) != 0;
}

template <typename T>
constexpr bool IsClear(T val, eel::utils::U32 n) {
  return (val & (1UL << n)) == 0;
}
}
