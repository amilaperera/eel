//
// Created by Amila Perera on 28/01/2019.
//
#include "platform/stm32/ll/gpio/gpio.hh"
#include "platform/stm32/ll/rcc/rcc.hh"
#include "util/types.hh"

namespace eel {
namespace hal {
namespace ll {

Gpio::Gpio(eel::hal::gpio::Pin pin) : port_{static_cast<eel::hal::gpio::Port>(util::ToInt(pin) / 16)},
                                      pin_{util::ToInt(pin) % 16U} {
  switch (port_) {
    case gpio::Port::A:
      port_base_ = EEL_GPIOA_BASE;
      break;
    case gpio::Port::B:
      port_base_ = EEL_GPIOB_BASE;
      break;
    case gpio::Port::C:
      port_base_ = EEL_GPIOC_BASE;
      break;
    case gpio::Port::D:
      port_base_ = EEL_GPIOD_BASE;
      break;
    case gpio::Port::E:
      port_base_ = EEL_GPIOE_BASE;
      break;
    case gpio::Port::F:
      port_base_ = EEL_GPIOF_BASE;
      break;
    case gpio::Port::G:
      port_base_ = EEL_GPIOG_BASE;
      break;
    case gpio::Port::H:
      port_base_ = EEL_GPIOH_BASE;
      break;
  }

  ll::Rcc::enable_port(port_, true);
}

void Gpio::configure_output(gpio::PullUpDown pud,
                            gpio::OutputType type,
                            gpio::OutputSpeed speed) {
  ll::set_mode(port_base_, pin_, eel::hal::gpio::Mode::Output);
  configure(pud, type, speed);
}

void Gpio::configure_input(gpio::PullUpDown pud) {
  ll::set_mode(port_base_, pin_, gpio::Mode::Input);
  set_pud(port_base_, pin_, pud);
}

void Gpio::configure_af(gpio::Af af,
                        gpio::PullUpDown pud,
                        gpio::OutputType type,
                        gpio::OutputSpeed speed) {
  ll::set_mode(port_base_, pin_, eel::hal::gpio::Mode::Alternate);
  set_af(port_base_, pin_, af);
  configure(pud, type, speed);
}

void Gpio::write(bool status) {
  GpioRegisterBlock(port_base_)->BSRR = status ? (1U << pin_) : (1 << (pin_ + 16U));
}

bool Gpio::read() const {
  return (GpioRegisterBlock(port_base_)->IDR & (1U << pin_)) != 0;
}

void Gpio::toggle() {
  bool status = (GpioRegisterBlock(port_base_)->ODR & (1U << pin_)) != 0;
  write(!status);
}

// private implementation
void Gpio::configure(gpio::PullUpDown pud,
                     gpio::OutputType type,
                     gpio::OutputSpeed speed) {
  set_pud(port_base_, pin_, pud);
  set_otype(port_base_, pin_, type);
  set_ospeed(port_base_, pin_, speed);
}

}
}
}
