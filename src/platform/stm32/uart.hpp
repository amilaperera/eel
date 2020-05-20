
#pragma once
#include "platform/platform.hpp"
#include "utils/types.hh"

namespace eel::hal::ll {
class usart {
 private:
  USART_InitTypeDef usart_init_;
  USART_TypeDef* usartx_;
 public:
  usart(eel::hal::pin_name tx, eel::hal::pin_name rx);
};
}
