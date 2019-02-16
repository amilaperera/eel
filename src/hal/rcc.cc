//
// Created by Amila Perera on 3/02/2019.
//

#include "hal/rcc.hh"

namespace eel {
namespace hal {
namespace rcc {
void Rcc::EnableGpioPort(eel::hal::gpio::Port port, bool status) {
  eel::hal::ll::rcc::Rcc::EnableGpioPort(port, status);
}
}
}
}
