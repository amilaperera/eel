#pragma once
#include "platform/hal_ll.hh"

namespace eel::hal {

class Gpio {
 public:
  explicit Gpio(Pin pin);
  void configure_output(PullUpDown pud, OutputType type, OutputSpeed speed);
  void configure_input(PullUpDown pud);
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
