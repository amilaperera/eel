#include "hal/hal.hpp"
#include "hal/pin_out.hpp"

// namespace alias
namespace eh = eel::hal;
// for common hal literals
using eh::literals::operator""_s;

int main() {
  eh::init();
  eh::pin_out led(eh::pin_name::B7, eh::pin_level::high);
  for (;;) {
    led.toggle();
    eh::delay(1_s);
  }
}

