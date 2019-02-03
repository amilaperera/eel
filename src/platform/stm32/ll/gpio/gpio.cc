//
// Created by Amila Perera on 28/01/2019.
//
#include "platform/stm32/ll/gpio/gpio.hh"
#include "platform/stm32/ll/rcc/rcc.hh"

namespace eel {
namespace hal {
namespace ll {
namespace gpio {

Gpio::Gpio(eel::hal::gpio::Pin pin) : port_{static_cast<eel::hal::gpio::Port>(static_cast<eel::util::U32>(pin) / 16)},
                                      pin_{static_cast<eel::util::U32>(pin) % 16} {
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
  temp |= (static_cast<eel::util::U8>(mode) << (pin_ * 2U));
  GpioRegisterBlock(port_base_)->MODER = temp;
}

void Gpio::ConfigureOutput(eel::hal::gpio::PullUpDown pud,
                           eel::hal::gpio::OutputType type,
                           eel::hal::gpio::OutputSpeed speed) {
  auto temp = GpioRegisterBlock(port_base_)->PUPDR;
  temp &= ~(3U << (pin_ * 2U));
  temp |= (static_cast<eel::util::U8>(pud) << (pin_ * 2U));
  GpioRegisterBlock(port_base_)->PUPDR = temp;

  temp = GpioRegisterBlock(port_base_)->OTYPER;
  temp &= ~(1U << pin_);
  temp |= (static_cast<eel::util::U8>(type) << pin_);
  GpioRegisterBlock(port_base_)->OTYPER = temp;

  temp = GpioRegisterBlock(port_base_)->OSPEEDR;
  temp &= ~(3U << (pin_ * 2U));
  temp |= (static_cast<eel::util::U8>(speed) << (pin_ * 2U));
  GpioRegisterBlock(port_base_)->OSPEEDR = temp;
}

void Gpio::Write(bool status) {
  GpioRegisterBlock(port_base_)->BSRR = status ? (1U << pin_) : (1 << (pin_ + 16U));
}

}
}
}
}
