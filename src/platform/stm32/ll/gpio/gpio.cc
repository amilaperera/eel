//
// Created by Amila Perera on 28/01/2019.
//
#include "platform/stm32/ll/gpio/gpio.hh"

namespace eel {
namespace hal {
namespace ll {
namespace gpio {

Gpio::Gpio(eel::hal::gpio::Pin pin) : port_{EEL_GPIOA_BASE + (static_cast<eel::util::U32>(pin) / 16) * 0x0400},
                                      pin_{static_cast<eel::util::U32>(pin) % 16} {
}

void Gpio::SetMode(eel::hal::gpio::Mode mode) {
  eel::util::IO_U32 temp = PortRCB(port_)->MODER;
  temp &= ~(3U << (pin_ * 2U));
  temp |= (static_cast<eel::util::U8>(mode) << (pin_ * 2U));
  PortRCB(port_)->MODER = temp;
}

void Gpio::ConfigureOutput(eel::hal::gpio::PullUpDown pud,
                           eel::hal::gpio::OutputType type,
                           eel::hal::gpio::OutputSpeed speed) {
  auto temp = PortRCB(port_)->PUPDR;
  temp &= ~(3U << (pin_ * 2U));
  temp |= (static_cast<eel::util::U8>(pud) << (pin_ * 2U));
  PortRCB(port_)->PUPDR = temp;

  temp = PortRCB(port_)->OTYPER;
  temp &= ~(1U << pin_);
  temp |= (static_cast<eel::util::U8>(type) << pin_);
  PortRCB(port_)->OTYPER = temp;

  temp = PortRCB(port_)->OSPEEDR;
  temp &= ~(3U << (pin_ * 2U));
  temp |= (static_cast<eel::util::U8>(speed) << (pin_ * 2U));
  PortRCB(port_)->OSPEEDR = temp;
}

void Gpio::Write(bool status) {
  PortRCB(port_)->BSRR = status ? (1U << pin_) : (1 << (pin_ + 16U));
}

}
}
}
}
