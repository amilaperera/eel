#pragma once
#include "util/types.hh"

namespace eel::hal {
enum class Port : eel::util::U8 {
  A = 0,
  B,
  C,
  D,
  E,
  F,
  G,
  H
};

enum class Pin : eel::util::U32 {
  A0 = 0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15,
  B0, B1, B2, B3, B4, B5, B6, B7, B8, B9, B10, B11, B12, B13, B14, B15,
  C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14, C15,
  D0, D1, D2, D3, D4, D5, D6, D7, D8, D9, D10, D11, D12, D13, D14, D15,
  E0, E1, E2, E3, E4, E5, E6, E7, E8, E9, E10, E11, E12, E13, E14, E15,
  F0, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13, F14, F15,
  G0, G1, G2, G3, G4, G5, G6, G7, G8, G9, G10, G11, G12, G13, G14, G15,
};

enum class PinMode : eel::util::U8 { Input = 0x00, Output, Alternate, Analog };
enum class PullUpDown : eel::util::U8 { None = 0x00, Up, Down };
enum class OutputSpeed : eel::util::U8 { Low = 0x00, Medium, Fast, High };
enum class OutputType : eel::util::U8 { PushPull = 0x00, OpenDrain };
enum class AfMode : eel::util::U8 {k0 = 0x00, k1, k2, k3, k4, k5, k6, k7, k8, k9, k10, k11, k12, k13, k14, k15};
enum class PinInterrupt : eel::util::U8 { kRising, kFalling, kRisingFalling };

enum class UsartPeripheral {
 kUsart1,
 kUsart2,
 kUsart3,
 kUart4,
 kUart5,
 kUsart6
};

enum class OverSampling : eel::util::U8 {
  k16 = 0,
  k8
};

enum class WordLength : eel::util::U8 {
  k8DataBits = 0,
  k9DataBits
};

enum class Parity : eel::util::U8 {
  kNone = 0,
  kEven,
  kOdd
};

enum class UsartMode : eel::util::U8 {
  kNone = 0,
  kRxOnly,
  kTxOnly,
  kTxRx,
};

}

