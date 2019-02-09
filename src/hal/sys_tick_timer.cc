//
// Created by Amila Perera on 4/02/2019.
//
#include "hal/sys_tick_timer.hh"

namespace eel {
namespace hal {

eel::util::U32 Tick::tick_count{0};

extern "C" void SysTick_Handler(void) {
  Tick::Increment();
}

}
}
