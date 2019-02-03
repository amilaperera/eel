#pragma once

#include "platform/hal_ll.hh"

namespace eel {
namespace hal {
namespace rcc {
void EnableGpioPort(eel::hal::gpio::Port port, bool status = true);
}
}
}
