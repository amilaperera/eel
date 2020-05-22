
#pragma once
#include "platform/platform.hpp"
#include "platform/driver_dispatcher.hpp"
#include "utils/preprocessor.hpp"
namespace eel::hal {
struct pin_out {
 private:
  eel::hal::ll::gpio gpio_;
 public:
  explicit pin_out(eel::hal::pin_name p) : gpio_(p) {
    gpio_.init(eel::hal::pin_mode::output_pp, eel::hal::pin_speed::high, eel::hal::pin_pud::none);
  }
  pin_out(eel::hal::pin_name p, eel::hal::pin_level lvl) : gpio_(p) {
    gpio_.init(eel::hal::pin_mode::output_pp, eel::hal::pin_speed::high, eel::hal::pin_pud::none);
    gpio_.write(lvl);
  }
  DELETE_COPY_CTOR(pin_out);
  DELETE_COPY_ASSIGNMENT(pin_out);

  void write(eel::hal::pin_level lvl) {
    gpio_.write(lvl);
  }
  eel::hal::pin_level read() {
    return gpio_.read();
  }
  void operator<<(eel::hal::pin_level lvl) {
    gpio_.write(lvl);
  }
  void operator>>(eel::hal::pin_level& lvl) {
    lvl = gpio_.read();
  }
  void toggle() {
    gpio_.toggle();
  }
};
}
