#pragma once

#include "platform/hal_ll.hh"

namespace eel::hal {
struct Rcc {
  static void enable_port(Port port, bool status = true);
};
}
