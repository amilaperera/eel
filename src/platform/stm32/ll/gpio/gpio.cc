//
// Created by Amila Perera on 28/01/2019.
//
#include "platform/stm32/ll/gpio/gpio.hh"
#include "platform/stm32/ll/rcc/rcc.hh"
#include "util/types.hh"

namespace eel {
namespace hal {
namespace ll {
namespace gpio {

Gpio::Gpio(eel::hal::gpio::Pin pin) : port_{static_cast<eel::hal::gpio::Port>(util::ToInt(pin) / 16)},
                                      pin_{util::ToInt(pin) % 16U} {
  switch (port_) {
    case eel::hal::gpio::Port::A:
      port_base_ = EEL_GPIOA_BASE;
      break;
    case eel::hal::gpio::Port::B:
      port_base_ = EEL_GPIOB_BASE;
      break;
    case eel::hal::gpio::Port::C:
      port_base_ = EEL_GPIOC_BASE;
      break;
    case eel::hal::gpio::Port::D:
      port_base_ = EEL_GPIOD_BASE;
      break;
    case eel::hal::gpio::Port::E:
      port_base_ = EEL_GPIOE_BASE;
      break;
    case eel::hal::gpio::Port::F:
      port_base_ = EEL_GPIOF_BASE;
      break;
    case eel::hal::gpio::Port::G:
      port_base_ = EEL_GPIOG_BASE;
      break;
    case eel::hal::gpio::Port::H:
      port_base_ = EEL_GPIOH_BASE;
      break;
  }

  eel::hal::ll::rcc::EnableGpioPort(port_, true);
}

void Gpio::SetMode(eel::hal::gpio::Mode mode) {
  eel::util::IO_U32 temp = GpioRegisterBlock(port_base_)->MODER;
  temp &= ~(3U << (pin_ * 2U));
  temp |= (util::ToInt(mode) << (pin_ * 2U));
  GpioRegisterBlock(port_base_)->MODER = temp;
}

void Gpio::ConfigureOutput(eel::hal::gpio::PullUpDown pud,
                           eel::hal::gpio::OutputType type,
                           eel::hal::gpio::OutputSpeed speed) {
  SetPud(port_base_, pin_, pud);
  SetOType(port_base_, pin_, type);
  SetOSpeed(port_base_, pin_, speed);
}

void Gpio::ConfigureInput(eel::hal::gpio::PullUpDown pud) {
  SetPud(port_base_, pin_, pud);
}

void Gpio::Write(bool status) {
  GpioRegisterBlock(port_base_)->BSRR = status ? (1U << pin_) : (1 << (pin_ + 16U));
}

bool Gpio::Read() {
  return (GpioRegisterBlock(port_base_)->IDR & (1U << pin_)) != 0;
}

}
}
}
}
