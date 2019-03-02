#pragma once

#include "platform/hal_ll.hh"

namespace eel {
namespace hal {
struct Rcc {
  static void EnableGpioPort(gpio::Port port, bool status = true);
};
}
}
