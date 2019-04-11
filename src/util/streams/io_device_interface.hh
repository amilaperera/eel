#pragma once
#include "util/types.hh"

namespace eel::util {

class IODeviceInterface {
 public:
  virtual void write(const U8 *buffer, U32 size) = 0;
  virtual void read(U8 *buffer, U32 size) = 0;
};

}
