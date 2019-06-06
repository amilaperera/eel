//
// Created by Amila Perera on 4/02/2019.
//
#include "sys_tick_timer.hh"

eel::util::IO_U32 eel::hal::Tick::tick_count{0};

extern "C" void SysTick_Handler(void) {
  eel::hal::Tick::increment();
}

namespace eel::hal {

void SysTickTimer::set_reload(eel::util::U32 val) {
  SysTick->LOAD = (val & 0x00FFFFFFU);
}

eel::util::U32 SysTickTimer::get_reload() {
  return SysTick->LOAD & 0x00FFFFFFU;
}

void SysTickTimer::suspend() {
  // Disable systick interrupt
  SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;
}

void SysTickTimer::resume() {
  // Enable systick interrupt
  SysTick->CTRL  |= SysTick_CTRL_TICKINT_Msk;
}

}
