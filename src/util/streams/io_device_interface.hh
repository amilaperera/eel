#pragma once
#include "util/types.hh"

namespace eel::util {

class IODeviceInterface {
 public:
  virtual void Write(const U8 *buffer, U32 size) = 0;
  virtual void Read(U8 *buffer, U32 size) = 0;
};

}
