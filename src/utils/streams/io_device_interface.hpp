#pragma once
#include "utils/types.hpp"

namespace eel::utils {

class io_device_interface {
 public:
  virtual void write(const char *buffer, std::size_t sz) = 0;
  virtual void read(char* buffer, std::size_t sz) = 0;
};

}
