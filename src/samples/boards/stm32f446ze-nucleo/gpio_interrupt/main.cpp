#include "hal/hal.hpp"
#include "hal/pin_out.hpp"
#include "hal/pin_in.hpp"
#include <memory>

bool keep_on{false};
eel::hal::pin_in* button_ptr{nullptr};

GPIO_IRQ_BEGIN(eel::hal::pin_name::C13)
   keep_on = (button_ptr->read() == eel::hal::pin_level::high);
GPIO_IRQ_END

int main() {
  eel::hal::init();
  eel::hal::pin_out led(eel::hal::pin_name::B7);
  eel::hal::pin_in button(eel::hal::pin_name::C13, eel::hal::interrupt_mode::both);
  button_ptr = &button;

  for (;;) {
    led << (keep_on ? eel::hal::pin_level::high : eel::hal::pin_level::low);
  }
}

