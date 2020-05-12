//
// Created by Amila Perera on 3/07/2019.
//

#include "utils/ports/pc/console_device.hh"
#include <iostream>

namespace eel::utils {
void ConsoleDevice::Write(const eel::utils::U8 *buffer, eel::utils::U32 size) {
  std::cout.write(reinterpret_cast<const char *>(buffer), static_cast<std::streamsize>(size));
}

void ConsoleDevice::Read(eel::utils::U8 *buffer, eel::utils::U32 size) {
  std::cin.read(reinterpret_cast<char *>(buffer), static_cast<std::streamsize>(size));
}
}

