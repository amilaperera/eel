#include "hal/hal.hpp"
#include "hal/pin_out.hpp"

// namespace alias
namespace eh = eel::hal;
// for common hal literals
using eh::literals::operator""_s;

int main() {
  eh::init();
  eh::pin_out led(eh::pin_name::B7);
  for (;;) {
    led << eh::pin_level::high;
    eh::delay(1_s);
    led << eh::pin_level::low;
    eh::delay(1_s);
  }
}

