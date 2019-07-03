//
// Created by Amila Perera on 3/07/2019.
//

#include "util/ports/pc/console_device.hh"
#include <iostream>

namespace eel::util {
void ConsoleDevice::Write(const eel::util::U8 *buffer, eel::util::U32 size) {
  std::cout.write(reinterpret_cast<const char *>(buffer), static_cast<std::streamsize>(size));
}

void ConsoleDevice::Read(eel::util::U8 *buffer, eel::util::U32 size) {
  std::cin.read(reinterpret_cast<char *>(buffer), static_cast<std::streamsize>(size));
}
}

