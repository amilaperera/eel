#pragma once
#include <cstring>
#include "utils/preprocessor.hpp"
#include "platform/platform.hpp"
#include "platform/driver_dispatcher.hpp"

namespace eel::hal {
class uart {
 private:
  eel::hal::ll::uart uart_;
 public:
  uart(eel::hal::pin_name tx, eel::hal::pin_name rx, int baudrate) : uart_(tx, rx) {
    uart_.init(baudrate);
  }
  DELETE_COPY_CTOR(uart);
  DELETE_COPY_ASSIGNMENT(uart);

  void write(const char* s, int size) {
    uart_.write(s, static_cast<std::uint16_t>(size));
  }
  void write(const char* s) {
    uart_.write(s, static_cast<std::uint16_t>(std::strlen(s)));
  }
  void read(char* s, int size) {
    uart_.read(s, static_cast<std::uint16_t>(size));
  }
};
}

