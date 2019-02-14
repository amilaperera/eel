//
// Created by Amila Perera on 28/01/2019.
//

#include "hal/gpio.hh"

namespace eel {
namespace hal {
namespace gpio {

/**
 * @class Gpio
 * @example
 *
 * @param pin
 */
Gpio::Gpio(Pin pin) : gpio_ll_{pin} {
}

void Gpio::SetMode(Mode mode) {
  gpio_ll_.SetMode(mode);
}

void Gpio::ConfigureOutput(PullUpDown pud, OutputType type, OutputSpeed speed) {
  gpio_ll_.SetMode(Mode::Output);
  gpio_ll_.ConfigureOutput(pud, type, speed);
}

void Gpio::ConfigureInput(PullUpDown pud) {
  gpio_ll_.SetMode(Mode::Input);
  gpio_ll_.ConfigureInput(pud);
}

void Gpio::Write(bool status) {
  gpio_ll_.Write(status);
}

bool Gpio::Read() {
  return gpio_ll_.Read();
}

}
}
}
