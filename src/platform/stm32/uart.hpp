
#pragma once
#include "platform/platform.hpp"
#include "platform/stm32/gpio.hpp"
#include "utils/types.hpp"
#include <utility>

namespace eel::hal::ll {

class uart {
 private:
  UART_HandleTypeDef handle_;
  USART_TypeDef* uartx_;
  eel::hal::ll::gpio tx_;
  eel::hal::ll::gpio rx_;
 public:
  uart(eel::hal::pin_name tx, eel::hal::pin_name rx);
  void init(int baudrate, parity p = parity::none, char_size cs = char_size::eight, stop_bits sb = stop_bits::one, flow_control fc = flow_control::none);
  void config_rx();
  void config_tx();
  void write(const char* s, std::size_t size);
  void read(char* s, std::size_t size);
};
}
