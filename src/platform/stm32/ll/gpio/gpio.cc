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
  auto temp = PortRCB(port_)->MODER;
  temp |= (static_cast<eel::util::U32>(mode) << (pin_ * 2U));
  PortRCB(port_)->MODER = temp;
}

}
}
}
}
