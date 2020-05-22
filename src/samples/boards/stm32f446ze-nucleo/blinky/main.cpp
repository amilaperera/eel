#include "hal/hal.hpp"
#include "hal/pin_out.hpp"

// namespace alias
namespace eh = eel::hal;
// for common hal literals
using namespace eh::literals;

int main() {
  eh::init();
  eh::pin_out led(eh::pin_name::B7, eh::pin_level::low);
  for (;;) {
    for (int i = 0; i < 10; ++i) {
      led.toggle();
      eh::delay(100_ms);
    }
    eh::delay(9_s);
  }
}

