#pragma once
#include "util/types.hh"
#include "stm32f446xx.h"

namespace eel {
namespace hal {

class SysTickTimer {
 private:
  static constexpr eel::util::U32 kBaseAddr{0xE000E010U};

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
