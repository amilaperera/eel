//
// Created by amila.perera on 17/05/2020.
//

#pragma once
#include "platform/platform.hpp"
namespace eel::hal {
struct pin_out {
 public:
  explicit pin_out(eel::hal::pin_name p) : gpio_(p) {
    gpio_.set_direction();
    gpio_.set_mode();
  }
 private:
  eel::hal::ll::gpio gpio_;
};
}
