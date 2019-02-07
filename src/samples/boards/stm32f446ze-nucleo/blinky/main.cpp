#include "stm32f446xx.h"
#include "hal/gpio.hh"

using eel::hal::gpio::Pin;
using eel::hal::gpio::Mode;
using eel::hal::gpio::PullUpDown;
using eel::hal::gpio::OutputType;
using eel::hal::gpio::OutputSpeed;

int main() {
  SysTick_Config();

  eel::hal::gpio::Gpio pin{Pin::B7};
  pin.SetMode(Mode::Output);
  pin.ConfigureOutput(PullUpDown::None, OutputType::PushPull, OutputSpeed::High);

  for (;;) {
    pin.Write(true);
    HAL_Delay(500);
    pin.Write(false);
    HAL_Delay(500);
  }
}

