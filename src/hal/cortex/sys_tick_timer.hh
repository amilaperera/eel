#pragma once

#include "util/types.hh"
#include "platform/mcu.hh"

//extern "C" void SysTick_Handler(void);

namespace eel::hal {

class Tick {
 public:
   static void increment() {
    ++tick_count;
  }
  static eel::util::U32 count() {
    return tick_count;
  }
  static void delay(eel::util::U32 ticks) {
    auto start_tick_count{count()};

    while (count() - start_tick_count < ticks) { }
  }
 public:
  static eel::util::IO_U32 tick_count;
};

struct SysTickTimer {
  enum class Frequency : eel::util::U32 {
    k1kHz = 1000,
    k10kHz = 10000,
  };
  static void set_reload(eel::util::U32 val);
  static eel::util::U32 get_reload();
  static void suspend();
  static void resume();

  template <SysTickTimer::Frequency Frequency, eel::util::U8 Priority>
  static bool enable() {
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
