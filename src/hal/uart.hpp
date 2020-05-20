#pragma once
#include "platform/platform.hpp"
#include "utils/preprocessor.hh"
namespace eel::hal {
class uart {
 private:
  eel::hal::ll::uart uart_;
 public:
  uart(eel::hal::pin_name tx, eel::hal::pin_name rx) : uart_(tx, rx) {}
};
}

