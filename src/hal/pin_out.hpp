//
// Created by amila.perera on 17/05/2020.
//

#pragma once
#include "platform/platform.hpp"
namespace eel::hal {
struct pin_out {
 public:
  explicit pin_out(eel::hal::pin_name p) : gpio_(p) {
    gpio_.initialize(eel::hal::pin_mode::output_pp, eel::hal::pin_speed::high, eel::hal::pull_up_down::none);
  }
 private:
  eel::hal::ll::gpio gpio_;
};
}
