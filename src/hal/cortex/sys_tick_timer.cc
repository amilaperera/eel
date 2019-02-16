//
// Created by Amila Perera on 4/02/2019.
//
#include "sys_tick_timer.hh"

eel::util::IO_U32 eel::hal::Tick::tick_count{0};

extern "C" void SysTick_Handler(void) {
  eel::hal::Tick::Increment();
}

namespace eel {
namespace hal {

void SysTickTimer::SetReloadValue(eel::util::U32 val) {
  SysTick->LOAD = (val & 0x00FFFFFFU);
}

eel::util::U32 SysTickTimer::GetReloadValue() {
  return SysTick->LOAD & 0x00FFFFFFU;
}

void SysTickTimer::Suspend() {
  // Disable systick interrupt
  SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;
}

void SysTickTimer::Resume() {
  // Enable systick interrupt
  SysTick->CTRL  |= SysTick_CTRL_TICKINT_Msk;
}

}
}