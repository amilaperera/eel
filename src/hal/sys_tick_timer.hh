#pragma once
#include "util/types.hh"
#include "stm32f446xx.h"

namespace eel {
namespace hal {

class Tick {
 public:
  static void Increment() {
    ++tick_count;
  }
  static eel::util::U32 Count() {
    return tick_count;
  }
  static void Delay(eel::util::U32 ticks) {
    auto now{Count()};
    while (Count() < (now + ticks)) { }
  }
 private:
  static eel::util::U32 tick_count;
};

class SysTickTimer {
 private:
 public:
  static void SetReloadValue(eel::util::U32 val) {
    SysTick->LOAD = (val & 0x00FFFFFFU);
  }

  static eel::util::U32 GetReloadValue() {
    return SysTick->LOAD & 0x00FFFFFFU;
  }

  static bool Enable(eel::util::U32 ticks) {
    return SysTick_Config(ticks) == 0UL;
  }
};

}
}
