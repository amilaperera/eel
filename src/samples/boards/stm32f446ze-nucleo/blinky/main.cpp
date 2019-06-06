#include "hal/cortex/sys_tick_timer.hh"
#include "hal/cortex/lock.hh"
#include "hal/gpio.hh"

using eel::hal::Pin;
using eel::hal::PinMode;
using eel::hal::PullUpDown;
using eel::hal::OutputType;
using eel::hal::OutputSpeed;

int main() {
  // tick per 1ms
  eel::hal::SysTickTimer::enable<eel::hal::SysTickTimer::Frequency::k1kHz, 0xf>();

  // output pin
  eel::hal::Gpio pin{Pin::B7};
  pin.configure_output(PullUpDown::None, OutputType::PushPull, OutputSpeed::High);
  pin.write(false);

  for (;;) {
    {
      eel::hal::Lock lk;
      pin.toggle();
    }
    eel::hal::Tick::delay(500);
  }
}

