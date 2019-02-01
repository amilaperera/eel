#pragma once
#include "platform/hal_ll.hh"

namespace eel {
namespace hal {
namespace gpio {

class Gpio {
 public:
  explicit Gpio(Pin pin);
  void SetMode(Mode mode);
  void ConfigureOutput(PullUpDown pud, OutputType type, OutputSpeed speed);
  void Write(bool status);
 private:
  eel::hal::ll::gpio::Gpio gpio_ll_;
};

}
}
}
