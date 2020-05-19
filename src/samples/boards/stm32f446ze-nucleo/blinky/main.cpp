#include "hal/hal.hpp"
#include "hal/pin_out.hpp"

namespace eh = eel::hal;
int main() {
  eh::init();
  eh::pin_out led(eh::pin_name::B7);
  for (;;) {
    led << eh::pin_level::high;
    HAL_Delay(1000);
    led << eh::pin_level::low;
    HAL_Delay(1000);
  }
}

