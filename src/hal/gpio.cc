//
// Created by Amila Perera on 28/01/2019.
//

#include "hal/gpio.hh"

namespace eel {
namespace hal {
namespace gpio {

Gpio::Gpio(Pin pin) : gpio_ll_{pin} {
}

void Gpio::SetMode(Mode mode) {
  gpio_ll_.SetMode(mode);
}

void Gpio::ConfigureOutput(PullUpDown pud, OutputType type, OutputSpeed speed) {
  gpio_ll_.ConfigureOutput(pud, type, speed);
}

void Gpio::Write(bool status) {
  gpio_ll_.Write(status);
}

}
}
}
