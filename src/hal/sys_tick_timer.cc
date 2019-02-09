//
// Created by Amila Perera on 4/02/2019.
//
#include "hal/sys_tick_timer.hh"

eel::util::IO_U32 eel::hal::Tick::tick_count{0};

extern "C" void SysTick_Handler(void) {
  eel::hal::Tick::Increment();
}

namespace eel {
namespace hal {

bool SysTickTimer::Enable(eel::util::U32 ticks) {
  NVIC_SetPriorityGrouping(0x00000003U);
  NVIC_SetPriority(SysTick_IRQn, 0xf);
  return SysTick_Config(ticks) == 0UL;
}

void SysTickTimer::SetReloadValue(eel::util::U32 val) {
  SysTick->LOAD = (val & 0x00FFFFFFU);
}

eel::util::U32 SysTickTimer::GetReloadValue() {
  return SysTick->LOAD & 0x00FFFFFFU;
}

}
}
