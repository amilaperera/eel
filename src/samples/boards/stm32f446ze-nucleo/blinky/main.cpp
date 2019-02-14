#include "hal/cortex/sys_tick_timer.hh"
#include "hal/cortex/lock.hh"
#include "hal/gpio.hh"

using eel::hal::gpio::Pin;
using eel::hal::gpio::Mode;
using eel::hal::gpio::PullUpDown;
using eel::hal::gpio::OutputType;
using eel::hal::gpio::OutputSpeed;

int main() {
  // tick per 1ms
  eel::hal::SysTickTimer::Enable<eel::hal::SysTickTimer::Frequency::k1kHz, 0xf>();

  // output pin
  eel::hal::gpio::Gpio pin{Pin::B7};
  pin.ConfigureOutput(PullUpDown::None, OutputType::PushPull, OutputSpeed::High);
  pin.Write(false);

  for (;;) {
    {
      eel::hal::Lock lk;
      pin.Toggle();
    }
    eel::hal::Tick::Delay(500);
  }
}

