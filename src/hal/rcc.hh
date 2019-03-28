#pragma once

#include "platform/hal_ll.hh"

namespace eel {
namespace hal {
struct Rcc {
  static void enable_port(gpio::Port port, bool status = true);
};
}
}
