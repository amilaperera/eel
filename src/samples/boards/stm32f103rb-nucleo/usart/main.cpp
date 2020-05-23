#include "hal/hal.hpp"
#include "hal/uart.hpp"
#include "system_clock_config.hpp"

int main() {
  eel::hal::init();
  SystemClock_Config(); // TODO(Amila)

  eel::hal::uart serial(eel::hal::pin_name::A2, eel::hal::pin_name::A3, 115200);
  serial.write("\r\nWelcome !!!!!\r\n");
  for (;;) {
    char ch;
    serial.read(&ch, 1);
    serial.write(&ch, 1);
  }
}

