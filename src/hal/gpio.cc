//
// Created by Amila Perera on 28/01/2019.
//

#include "hal/gpio.hh"

namespace eel {
namespace hal {
namespace gpio {

Gpio::Gpio(Pin pin) : gpio_ll_{pin} {
}

void Gpio::SetDirection(Direction dir) {
}

}
}
}
