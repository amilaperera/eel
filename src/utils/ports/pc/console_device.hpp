//
// Created by Amila Perera on 3/07/2019.
//

#pragma once
#include "utils/types.hpp"

namespace eel::utils {
struct console_device {
  void write(const char *buffer, std::size_t size);
  void read(char *buffer, std::size_t size);
};
}


