//
// Created by Amila Perera on 3/07/2019.
//

#pragma once
#include "utils/types.hh"

namespace eel::util {
struct ConsoleDevice {
  void Write(const eel::util::U8 *buffer, eel::util::U32 size);
  void Read(eel::util::U8 *buffer, eel::util::U32 size);
};
}


