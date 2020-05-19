#include "platform/stm32/gpio.hpp"

namespace eel::hal::ll {
gpio::gpio(eel::hal::pin_name pin) : gpio_init_(), gpiox_(nullptr) {
  // pin
  gpio_init_.Pin = (static_cast<std::uint16_t>(1) << static_cast<std::uint16_t>(eel::utils::to_integral(pin) % 16));
  // port
  auto port_value = eel::utils::to_integral(pin) / 16;
  switch (port_value) {
    case 0:
      gpiox_ = GPIOA;
      __GPIOA_CLK_ENABLE();
      break;
    case 1:
      gpiox_ = GPIOB;
      __GPIOB_CLK_ENABLE();
      break;
    case 2:
      gpiox_ = GPIOC;
      __GPIOC_CLK_ENABLE();
      break;
    case 3:
      gpiox_ = GPIOD;
      __GPIOD_CLK_ENABLE();
      break;
    case 4:
      gpiox_ = GPIOE;
      __GPIOE_CLK_ENABLE();
      break;
    case 5:
      gpiox_ = GPIOF;
      __GPIOF_CLK_ENABLE();
      break;
    case 6:
      gpiox_ = GPIOG;
      __GPIOG_CLK_ENABLE();
      break;
    default:
      // TODO
      break;
  }
}

void gpio::initialize(eel::hal::pin_mode m, eel::hal::pin_speed s, eel::hal::pull_up_down p) {
  set_mode(m);
  set_speed(s);
  set_pull_up_down(p);
  HAL_GPIO_Init(gpiox_, &gpio_init_);
}

void gpio::set_mode(eel::hal::pin_mode m) {
  gpio_init_.Mode = eel::utils::to_integral(m);
}

void gpio::set_speed(eel::hal::pin_speed s) {
  gpio_init_.Speed = eel::utils::to_integral(s);
}

void gpio::set_pull_up_down(eel::hal::pull_up_down p) {
  gpio_init_.Pull = eel::utils::to_integral(p);
}

void gpio::write(eel::hal::pin_level lvl) {
  HAL_GPIO_WritePin(gpiox_, gpio_init_.Pin, lvl == eel::hal::pin_level::low ? GPIO_PIN_RESET : GPIO_PIN_SET);
}

eel::hal::pin_level gpio::read() {
  return HAL_GPIO_ReadPin(gpiox_, gpio_init_.Pin) == GPIO_PIN_RESET ? eel::hal::pin_level::low : eel::hal::pin_level::high;
}

}