#pragma once
#include "platform/hal_ll.hh"

namespace eel {
namespace hal {
namespace gpio {

class Gpio {
 public:
  explicit Gpio(Pin pin);
  void ConfigureOutput(PullUpDown pud, OutputType type, OutputSpeed speed);
  void ConfigureInput(PullUpDown pud);
  void ConfigureAf(PullUpDown pud, OutputType type, OutputSpeed speed);
  bool Read() const;
  explicit operator bool() const;
  void Write(bool status);
  Gpio & operator=(bool status);
  Gpio & operator=(int status);
  void Toggle();

 private:
  eel::hal::ll::gpio::Gpio gpio_ll_;
};

}
}
}
