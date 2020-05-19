
#pragma once
#include "platform/platform.hpp"
#include "utils/preprocessor.hh"
namespace eel::hal {
struct pin_out {
 private:
  eel::hal::ll::gpio gpio_;
 public:
  explicit pin_out(eel::hal::pin_name p) : gpio_(p) {
    gpio_.initialize(eel::hal::pin_mode::output_pp, eel::hal::pin_speed::high, eel::hal::pull_up_down::none);
  }
  DELETE_COPY_CTOR(pin_out);
  DELETE_COPY_ASSIGNMENT(pin_out);

  void write(eel::hal::pin_level lvl) {
    gpio_.write(lvl);
  }
  eel::hal::pin_level read() {
    return gpio_.read();
  }
  pin_out& operator<<(eel::hal::pin_level lvl) {
    gpio_.write(lvl);
    return *this;
  }
};
}
