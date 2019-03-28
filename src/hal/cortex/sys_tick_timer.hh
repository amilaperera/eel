#pragma once

#include "util/types.hh"
#include "platform/mcu.hh"

//extern "C" void SysTick_Handler(void);

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
    auto start_tick_count{Count()};

    while (Count() - start_tick_count < ticks) { }
  }
 public:
  static eel::util::IO_U32 tick_count;
};

struct SysTickTimer {
  enum class Frequency : eel::util::U32 {
    k1kHz = 1000,
    k10kHz = 10000,
  };
  static void SetReloadValue(eel::util::U32 val);
  static eel::util::U32 GetReloadValue();
  static void Suspend();
  static void Resume();

  template <SysTickTimer::Frequency Frequency, eel::util::U8 Priority>
  static bool Enable() {
    static_assert(Priority <= 0xf, "Priority should be less than 16");
    NVIC_SetPriorityGrouping(0x00000003U);
    NVIC_SetPriority(SysTick_IRQn, Priority);
    // Systick_Config configures systick to run @ processor clock NOT @ AHB/8
    // TODO: The following assumes frequency to be a multiple of SystemCoreClock.
    eel::util::U32 ticks = SystemCoreClock/util::ToInt(Frequency);
    return SysTick_Config(ticks) == 0UL;
  }
};

}
}
