#pragma once
#include "utils/types.hpp"

namespace eel::utils {

class io_device_interface {
 public:
  virtual void Write(const U8 *buffer, U32 size) = 0;
  virtual void Read(U8 *buffer, U32 size) = 0;
};

}
