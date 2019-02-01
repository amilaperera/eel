#include "hal/critical_section.hh"
#include "hal/gpio.hh"

int main() {
  HAL_Init();

  __GPIOB_CLK_ENABLE();

  eel::hal::ll::gpio::Gpio pin{eel::hal::gpio::Pin::B7};
  pin.SetMode(eel::hal::gpio::Mode::Output);
  pin.ConfigureOutput(eel::hal::gpio::PullUpDown::None, eel::hal::gpio::OutputType::PushPull, eel::hal::gpio::OutputSpeed::High);

  for (;;) {
    pin.Write(true);
    HAL_Delay(500);
    pin.Write(false);
    HAL_Delay(500);
  }
}

