//
// Created by Amila Perera on 3/02/2019.
//

#include "hal/rcc.hh"

namespace eel {
namespace hal {
void Rcc::enable_port(gpio::Port port, bool status) {
  ll::Rcc::enable_port(port, status);
}
}
}
