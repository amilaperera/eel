#include "hal/hal.hpp"
#include "hal/uart.hpp"
int main() {
  eel::hal::init();
  eel::hal::uart serial(eel::hal::pin_name::D8, eel::hal::pin_name::D9, 115200);
  serial.write("\r\nWelcome !!!!!\r\n");
  for (;;) {
    char ch;
    serial.read(&ch, 1);
    serial.write(&ch, 1);
  }
}

