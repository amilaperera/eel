#include "platform/stm32/uart.hpp"

namespace eel::hal::ll {
uart::uart(eel::hal::pin_name tx, eel::hal::pin_name rx) : handle_(), uartx_(nullptr), tx_(tx), rx_(rx) {
  for (auto const& row : uart_af_map) {
    if (tx == row.tx) {
      // assert(rx == row.rx)
      uartx_ = row.uartx;
      tx_.set_af(row.af);
      rx_.set_af(row.af);
      break;
    }
  }

  // enable clock
  if (uartx_ == USART1) {
    __HAL_RCC_USART1_CLK_ENABLE();
  } else if (uartx_ == USART2) {
    __HAL_RCC_USART2_CLK_ENABLE();
  } else if (uartx_ == USART3) {
    __HAL_RCC_USART3_CLK_ENABLE();
  }
  config_tx();
  config_rx();
}

void uart::init(int baudrate, parity p, char_size cs, stop_bits sb, flow_control fc) {
  handle_.Instance = uartx_;
  handle_.Init.BaudRate = baudrate;
  handle_.Init.Parity = eel::utils::to_integral(p);
  handle_.Init.WordLength = eel::utils::to_integral(cs);
  handle_.Init.StopBits = eel::utils::to_integral(sb);
  handle_.Init.HwFlowCtl = eel::utils::to_integral(fc);
  handle_.Init.Mode = UART_MODE_TX_RX;
  handle_.Init.OverSampling = UART_OVERSAMPLING_16;
  HAL_UART_Init(&handle_);
}

void uart::config_rx() {
  rx_.init(hal::pin_mode::af_pp, hal::pin_speed::medium, hal::pin_pud::up);
}

void uart::config_tx() {
  tx_.init(hal::pin_mode::af_pp, hal::pin_speed::medium, hal::pin_pud::up);
}

void uart::write(const char* s, std::size_t size) {
  HAL_UART_Transmit(&handle_, reinterpret_cast<uint8_t*>(const_cast<char*>(s)),
      static_cast<std::uint16_t>(size), HAL_MAX_DELAY);
}

void uart::read(char* s, std::size_t size) {
  HAL_UART_Receive(&handle_, reinterpret_cast<uint8_t*>(s),
       static_cast<std::uint16_t>(size), HAL_MAX_DELAY);
}

}
