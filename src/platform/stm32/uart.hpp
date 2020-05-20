
#pragma once
#include "platform/platform.hpp"
#include "utils/types.hh"

namespace eel::hal::ll {
class uart {
 private:
  UART_HandleTypeDef usart_init_;
  USART_TypeDef* usartx_;
  eel::hal::pin_name tx_;
  eel::hal::pin_name rx_;
 public:
  uart(eel::hal::pin_name tx, eel::hal::pin_name rx);
};
}
