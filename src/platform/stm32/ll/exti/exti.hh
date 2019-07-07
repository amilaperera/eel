#pragma once

#include <util/types.hh>
#include <util/preprocessor.hh>
#include <platform/common_defs.hh>
#include "platform/stm32/f4/memory_map.hh"

namespace eel::hal::ll {
enum class ExtiLine : eel::util::U32 {
  kLine0,
  kLine1,
  kLine2,
  kLine3,
  kLine4,
  kLine5,
  kLine6,
  kLine7,
  kLine8,
  kLine9,
  kLine10,
  kLine11,
  kLine12,
  kLine13,
  kLine14,
  kLine15,
  kLine16,
  kLine17,
  kLine18,
  kLine19,
  kLine20,
  kLine21,
  kLine22,
};

struct ExtiRCB {
  eel::util::IO_U32 IMR;
  eel::util::IO_U32 EMR;
  eel::util::IO_U32 RTSR;
  eel::util::IO_U32 FTSR;
  eel::util::IO_U32 SWIER;
  eel::util::IO_U32 PR;
};

EEL_ALWAYS_INLINE auto ExtiReg() {
  return reinterpret_cast<ExtiRCB*>(EEL_EXTI_BASE);
}

struct Exti {
  static void SetTrigger(ExtiLine line, eel::hal::PinInterrupt trigger);
  static void Enable(ExtiLine line);
  static void Disable(ExtiLine line);
  static bool IsPending(ExtiLine line);
  static void ClearPending(ExtiLine line);
};
}
