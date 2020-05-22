//
// Created by Amila Perera on 3/07/2019.
//

#pragma once
#include "utils/types.hpp"

namespace eel::utils {
struct console_device {
  void Write(const eel::utils::U8 *buffer, eel::utils::U32 size);
  void Read(eel::utils::U8 *buffer, eel::utils::U32 size);
};
}

