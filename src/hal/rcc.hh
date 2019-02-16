#pragma once

#include "platform/hal_ll.hh"

namespace eel {
namespace hal {
namespace rcc {
struct Rcc {
  static void EnableGpioPort(eel::hal::gpio::Port port, bool status = true);
};
}
}
}
