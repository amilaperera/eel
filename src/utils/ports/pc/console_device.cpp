//
// Created by Amila Perera on 3/07/2019.
//

#include "utils/ports/pc/console_device.hpp"
#include <iostream>

namespace eel::utils {
void console_device::write(const char *buffer, std::size_t size) {
  std::cout.write(buffer, static_cast<std::streamsize>(size));
}

void console_device::read(char *buffer, std::size_t size) {
  std::cin.read(buffer, static_cast<std::streamsize>(size));
}
}

