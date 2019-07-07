#include "hal/cortex/sys_tick_timer.hh"
#include "hal/cortex/lock.hh"
#include "hal/gpio.hh"

using eel::hal::Pin;
using eel::hal::PinMode;
using eel::hal::PullUpDown;
using eel::hal::OutputType;
using eel::hal::OutputSpeed;
using eel::hal::PinInterrupt;

bool is_pressed_or_released{false};

extern "C" void EXTI15_10_IRQHandler() {
  is_pressed_or_released = true;
}

int main() {
  // tick per 1ms
  eel::hal::SysTickTimer::enable<eel::hal::SysTickTimer::Frequency::k1kHz, 0xf>();

  // output pin
  eel::hal::Gpio led{Pin::B7};
  led.ConfigureOutput(PullUpDown::None, OutputType::PushPull, OutputSpeed::High);
  led.Write(false);

  // input pin
  eel::hal::Gpio button{Pin::C13};
  button.ConfigureInput(PullUpDown::None);
  button.ConfigureInterrupt(PinInterrupt::kFalling);
  button.EnableInterrupt(3);

  for (;;) {
    if (is_pressed_or_released) {
      led.Toggle();
    }
  }
}


