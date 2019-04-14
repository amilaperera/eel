//
// Created by Amila Perera on 17/02/2019.
//
#include <util/bit_manip.hh>
#include "platform/stm32/ll/usart/usart.hh"
#include "platform/af_map.hh"

namespace eel::hal::ll {

Usart::Usart(usart::Peripheral peripheral, gpio::Pin tx, gpio::Pin rx) :
  peripheral_{peripheral},
  usart_base_{},
  tx_{tx},
  rx_{rx} {
  // check validity of tx & rx
  // TODO: do platform specific assertions
  auto ret = check_usart_tx(peripheral_, tx);
  // assert tx_ret.first
  if (ret.first) {
    tx_af_ = ret.second;
  }
  ret = check_usart_rx(peripheral_, rx);
  // assert rx_ret.first
  if (ret.first) {
    rx_af_ = ret.second;
  }

  switch (peripheral) {
    case usart::Peripheral::kUsart1:
      usart_base_ = EEL_USART1_BASE;
      break;
    case usart::Peripheral::kUsart2:
      usart_base_ = EEL_USART2_BASE;
      break;
    case usart::Peripheral::kUsart3:
      usart_base_ = EEL_USART3_BASE;
      break;
    case usart::Peripheral::kUart4:
      usart_base_ = EEL_UART4_BASE;
      break;
    case usart::Peripheral::kUart5:
      usart_base_ = EEL_UART5_BASE;
      break;
    case usart::Peripheral::kUsart6:
      usart_base_ = EEL_USART6_BASE;
      break;
  }
  ll::Rcc::enable_usart(peripheral);
}

void Usart::configure_tx(gpio::PullUpDown pud, gpio::OutputType type, gpio::OutputSpeed speed) {
  tx_.configure_af(tx_af_, pud, type, speed);
}

void Usart::configure_rx(gpio::PullUpDown pud, gpio::OutputType type, gpio::OutputSpeed speed) {
  rx_.configure_af(rx_af_, pud, type, speed);
}

void Usart::configure(eel::util::U32 baud_rate, usart::WordLength word_length, usart::Parity parity) {
  // First the baud rate in BRR
  set_baud_rate(baud_rate);

  // Set all the CR1 register bits
  auto cr1 = usart_reg(usart_base_)->CR1;
  set_uart_enable(&cr1, true);
  set_word_length(&cr1, word_length);
  set_parity(&cr1, parity);
  set_mode(&cr1, usart::Mode::kTxRx);
  usart_reg(usart_base_)->CR1 = cr1;
}

void Usart::write(const util::U8 *buffer, util::U32 size) {
  for (auto i = 0UL; i < size; ++i) {
    write(buffer[i]);
  }
  // Wait for TC
  while ((usart_reg(usart_base_)->SR & eel::util::kBit6) == 0);
}

void Usart::read(util::U8 *buffer, util::U32 size) {
  for (auto i = 0UL; i < size; ++i) {
    auto data = read();
    buffer[i] = data;
  }
}

// private implementation
void Usart::set_baud_rate(eel::util::U32 value) {
  auto fclk{0UL};
  if (peripheral_ == usart::Peripheral::kUsart1 || peripheral_ == usart::Peripheral::kUsart6) {
    fclk = ll::Rcc::apb2_frequency();
  } else {
    fclk = ll::Rcc::apb1_frequency();
  }
  // TODO: have to revisit this calculation
  usart_reg(usart_base_)->BRR = (fclk + value/2) / value;
}

void Usart::set_uart_enable(eel::util::U32 *cr1, bool status) {
  *cr1 = eel::util::set_or_clear_bit(status, *cr1, 13);
}

void Usart::set_word_length(eel::util::U32 *cr1, usart::WordLength word_length) {
  *cr1 = eel::util::set_or_clear_bit(word_length == usart::WordLength::k9DataBits, *cr1, 12);
}

void Usart::set_parity(eel::util::U32 *cr1, usart::Parity parity) {
  // Parity enable/disable
  *cr1 = eel::util::set_or_clear_bit(parity != usart::Parity::kNone, *cr1, 10);
  // Paridy odd/even
  *cr1 = eel::util::set_or_clear_bit(parity == usart::Parity::kOdd, *cr1, 9);
}

void Usart::set_mode(eel::util::U32 *cr1, usart::Mode mode) {
  auto temp = *cr1 & ~(0x3U << 2);
  temp |= (eel::util::ToInt(mode) << 2);
  *cr1 = temp;
}

void Usart::write(eel::util::U8 data) {
  // Wait for TXE
  while ((usart_reg(usart_base_)->SR & eel::util::kBit7) == 0);
  // Now write to DR
  usart_reg(usart_base_)->DR = data & static_cast<eel::util::U8>(0xff);
}

util::U8 Usart::read() {
  // Wait for RXNE
  while ((usart_reg(usart_base_)->SR & eel::util::kBit5) == 0);
  // Now write to DR
  return static_cast<util::U8>(usart_reg(usart_base_)->DR & static_cast<eel::util::U8>(0xff));
}

}
