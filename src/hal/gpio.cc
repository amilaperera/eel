//
// Created by Amila Perera on 28/01/2019.
//

#include "hal/gpio.hh"

namespace eel::hal {
/**
 * @class Gpio
 * @example
 *
 * @param pin
 */
Gpio::Gpio(gpio::Pin pin) : gpio_ll_{pin} {
}

void Gpio::configure_output(gpio::PullUpDown pud, gpio::OutputType type, gpio::OutputSpeed speed) {
  gpio_ll_.configure_output(pud, type, speed);
}

void Gpio::configure_input(gpio::PullUpDown pud) {
  gpio_ll_.configure_input(pud);
}

bool Gpio::read() const {
  return gpio_ll_.read();
}

Gpio::operator bool() const {
  return gpio_ll_.read();
}


void Gpio::write(bool status) {
  gpio_ll_.write(status);
}

Gpio & Gpio::operator=(bool status) {
  gpio_ll_.write(status);
  return *this;
}

Gpio & Gpio::operator=(int status) {
  *this = (status != 0);
  return *this;
}

void Gpio::toggle() {
  gpio_ll_.toggle();
}

}
