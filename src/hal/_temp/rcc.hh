#pragma once

#include "platform/hal_ll.hh"

namespace eel::hal {
struct Rcc {
  static void EnablePort(Port port, bool status = true);
};
}
