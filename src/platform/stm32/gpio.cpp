//
// Created by amila.perera on 17/05/2020.
//

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
    case 1:
      gpiox_ = GPIOB;
          __GPIOB_CLK_ENABLE();
    case 2:
      gpiox_ = GPIOC;
          __GPIOC_CLK_ENABLE();
    default:
      // TODO
      break;
  }
}
//
void gpio::set_direction() {}
// mode + otype
void gpio::set_mode() {}
}
