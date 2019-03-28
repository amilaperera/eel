#pragma once
#include "platform/hal_ll.hh"

namespace eel {
namespace hal {

class Gpio {
 public:
  explicit Gpio(gpio::Pin pin);
  void configure_output(gpio::PullUpDown pud, gpio::OutputType type, gpio::OutputSpeed speed);
  void configure_input(gpio::PullUpDown pud);
  bool read() const;
  explicit operator bool() const;
  void write(bool status);
  Gpio & operator=(bool status);
  Gpio & operator=(int status);
  void toggle();

 private:
  ll::Gpio gpio_ll_;
};

}
}
