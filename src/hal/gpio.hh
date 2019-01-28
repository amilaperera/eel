#pragma once
#include "platform/hal_ll.hh"

namespace eel {
namespace hal {
namespace gpio {

class Gpio {
 public:
  explicit Gpio(Pin pin);
  void SetDirection(Direction dir);
 private:
  eel::hal::ll::gpio::Gpio gpio_ll_;
};

}
}
}
