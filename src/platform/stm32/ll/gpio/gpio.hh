#pragma once

#include "platform/stm32/stm32_registry.hh"

namespace eel {
namespace hal {
namespace ll {
namespace gpio {

struct Gpio {
  explicit Gpio(eel::hal::gpio::Pin pin);
  void SetDirection(eel::hal::gpio::Direction dir);
};

}
}
}
}

