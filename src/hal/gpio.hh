#pragma once
#include "platform/hal_ll.hh"

namespace eel {
namespace hal {

class Gpio {
 public:
  explicit Gpio(gpio::Pin pin);
  void ConfigureOutput(gpio::PullUpDown pud, gpio::OutputType type, gpio::OutputSpeed speed);
  void ConfigureInput(gpio::PullUpDown pud);
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
}
