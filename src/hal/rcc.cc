//
// Created by Amila Perera on 3/02/2019.
//

#include "hal/rcc.hh"

namespace eel::hal {
void Rcc::EnablePort(Port port, bool status) {
  ll::Rcc::EnablePort(port, status);
}
}
