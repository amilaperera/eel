#include "hal/sys_tick_timer.hh"
#include "hal/gpio.hh"

using eel::hal::gpio::Pin;
using eel::hal::gpio::Mode;
using eel::hal::gpio::PullUpDown;
using eel::hal::gpio::OutputType;
using eel::hal::gpio::OutputSpeed;

int main() {
  // tick per 1ms
  eel::hal::SysTickTimer::Enable<1000UL, 0xf>();

  eel::hal::gpio::Gpio pin{Pin::B7};
  pin.SetMode(Mode::Output);
  pin.ConfigureOutput(PullUpDown::None, OutputType::PushPull, OutputSpeed::High);

  for (;;) {
    pin.Write(true);
    eel::hal::Tick::Delay(2000);
    pin.Write(false);
    eel::hal::Tick::Delay(2000);
  }
}

