#include "hal/hal.hpp"
#include "hal/pin_out.hpp"
#include "hal/pin_in.hpp"
#include "system_clock_config.hpp"

bool keep_on{false};
eel::hal::pin_in* button_ptr{nullptr};

GPIO_IRQ_BEGIN(eel::hal::pin_name::C13)
    // PC13 is ON by default
    keep_on = (button_ptr->read() == eel::hal::pin_level::low);
GPIO_IRQ_END

int main() {
  eel::hal::init();
  SystemClock_Config(); // TODO(Amila)

  eel::hal::pin_out led(eel::hal::pin_name::A5);
  eel::hal::pin_in button(eel::hal::pin_name::C13, eel::hal::interrupt_mode::both);
  button_ptr = &button;

  for (;;) {
    led << (keep_on ? eel::hal::pin_level::high : eel::hal::pin_level::low);
  }
}
