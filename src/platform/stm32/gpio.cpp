#include "platform/stm32/gpio.hpp"

namespace eel::hal::ll {
gpio::gpio(eel::hal::pin_name pin) : handle_(), gpiox_(nullptr), name_(pin) {
  // pin
  handle_.Pin = (static_cast<std::uint16_t>(1) << static_cast<std::uint16_t>(eel::utils::to_integral(pin) % 16));
  // port
  auto port_value = eel::utils::to_integral(pin) / 16;
  enable_clock(port_value);
  gpiox_ = get_gpiox(port_value);
}

void gpio::init(eel::hal::pin_mode m, eel::hal::pin_speed s, eel::hal::pin_pud p) {
  set_mode(m);
  set_speed(s);
  set_pull_up_down(p);
  HAL_GPIO_Init(gpiox_, &handle_);
}

void gpio::set_af(eel::hal::af a) {
#if defined(STM32F446XX)
  handle_.Alternate = eel::utils::to_integral(a);
#endif
}

eel::hal::pin_name gpio::name() const {
  return name_;
}

void gpio::set_mode(eel::hal::pin_mode m) {
  handle_.Mode = eel::utils::to_integral(m);
}

void gpio::set_speed(eel::hal::pin_speed s) {
  handle_.Speed = eel::utils::to_integral(s);
}

void gpio::set_pull_up_down(eel::hal::pin_pud p) {
  handle_.Pull = eel::utils::to_integral(p);
}

void gpio::write(eel::hal::pin_level lvl) {
  HAL_GPIO_WritePin(gpiox_, handle_.Pin, lvl == eel::hal::pin_level::low ? GPIO_PIN_RESET : GPIO_PIN_SET);
}

eel::hal::pin_level gpio::read() {
  return HAL_GPIO_ReadPin(gpiox_, handle_.Pin) == GPIO_PIN_RESET ? eel::hal::pin_level::low : eel::hal::pin_level::high;
}

void gpio::toggle() {
  HAL_GPIO_TogglePin(gpiox_, handle_.Pin);
}

}