#pragma once
#include "platform/hal_ll.hh"

namespace eel::hal {

class Gpio {
 public:
  explicit Gpio(Pin pin);
  void ConfigureOutput(PullUpDown pud, OutputType type, OutputSpeed speed);
  void ConfigureInput(PullUpDown pud);
  bool Read() const;
  explicit operator bool() const;
  void Write(bool status);
  Gpio & operator=(bool status);
  Gpio & operator=(int status);
  void Toggle();

 private:
  ll::Gpio gpio_ll_;
};

}
