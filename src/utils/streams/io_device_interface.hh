#pragma once
#include "utils/types.hh"

namespace eel::utils {

class IODeviceInterface {
 public:
  virtual void Write(const U8 *buffer, U32 size) = 0;
  virtual void Read(U8 *buffer, U32 size) = 0;
};

}
