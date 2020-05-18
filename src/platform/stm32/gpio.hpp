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
  void set_direction();
  void set_mode();
};
}
