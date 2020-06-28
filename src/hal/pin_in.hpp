#pragma once
#include "platform/platform.hpp"
#include "platform/driver_dispatcher.hpp"
#include "utils/preprocessor.hpp"
namespace eel::hal {
struct pin_in {
 private:
  eel::hal::ll::gpio_interrupt gpio_interrupt_;
 public:
  explicit pin_in(eel::hal::pin_name p, eel::hal::interrupt_mode mode) : gpio_interrupt_(p, mode) {
    gpio_interrupt_.init(eel::hal::pin_speed::high, eel::hal::pin_pud::none);
  }
  DELETE_COPY_CTOR(pin_in);
  DELETE_COPY_ASSIGNMENT(pin_in);

  void set_priority(std::uint32_t prio) {
    gpio_interrupt_.set_priority(prio);
  }
  eel::hal::pin_level read() {
    return gpio_interrupt_.read();
  }
  void operator>>(eel::hal::pin_level& lvl) {
    lvl = gpio_interrupt_.read();
  }
};
}

