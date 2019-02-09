#pragma once
#include "util/types.hh"
#include "stm32f446xx.h"

extern "C" void SysTick_Handler(void);

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
  static eel::util::IO_U32 tick_count;
};

class SysTickTimer {
 private:
 public:
  static void SetReloadValue(eel::util::U32 val);
  static eel::util::U32 GetReloadValue();
  static void Suspend();
  static void Resume();
  static bool Enable(eel::util::U32 ticks);
};

}
}
