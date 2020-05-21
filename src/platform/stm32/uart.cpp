//
// Created by amila.perera on 20/05/2020.
//
#include "platform/stm32/uart.hpp"

namespace eel::hal::ll {
uart::uart(eel::hal::pin_name tx, eel::hal::pin_name rx) : uart_init_(), uartx_(nullptr), tx_(tx), rx_(rx) {
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
  uart_init_.Instance = uartx_;
  uart_init_.Init.BaudRate = baudrate;
  uart_init_.Init.Parity = eel::utils::to_integral(p);
  uart_init_.Init.WordLength = eel::utils::to_integral(cs);
  uart_init_.Init.StopBits = eel::utils::to_integral(sb);
  uart_init_.Init.HwFlowCtl = eel::utils::to_integral(fc);
  uart_init_.Init.Mode = UART_MODE_TX_RX;
  uart_init_.Init.OverSampling = UART_OVERSAMPLING_16;
  HAL_UART_Init(&uart_init_);
}

void uart::config_rx() {
  tx_.init(hal::pin_mode::af_pp, hal::pin_speed::medium, hal::pin_pud::up);
}

void uart::config_tx() {
  tx_.init(hal::pin_mode::af_pp, hal::pin_speed::medium, hal::pin_pud::up);
}

}
