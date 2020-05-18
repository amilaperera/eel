//
// Created by amila.perera on 17/05/2020.
//

#pragma once
#include "platform/platform.hpp"
#include "utils/types.hh"

namespace eel::hal::ll {
class gpio {
 private:
  GPIO_InitTypeDef gpio_init_;
  GPIO_TypeDef *gpiox_;
 public:
  explicit gpio(eel::hal::pin_name pin);
  void initialize(eel::hal::pin_mode m, eel::hal::pin_speed s, eel::hal::pull_up_down p);
  void set_mode(eel::hal::pin_mode m);
  void set_speed(eel::hal::pin_speed s);
  void set_pull_up_down(eel::hal::pull_up_down p);
};
}
