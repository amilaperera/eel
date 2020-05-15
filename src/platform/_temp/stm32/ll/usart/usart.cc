//
// Created by Amila Perera on 17/02/2019.
//
#include <util/bit_manip.hh>
#include "platform/stm32/ll/usart/usart.hh"
#include "platform/af_map.hh"

namespace eel::hal::ll {

Usart::Usart(UsartPeripheral peripheral, Pin tx, Pin rx) :
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
    case UsartPeripheral::kUsart1:
      usart_base_ = EEL_USART1_BASE;
      break;
    case UsartPeripheral::kUsart2:
      usart_base_ = EEL_USART2_BASE;
      break;
    case UsartPeripheral::kUsart3:
      usart_base_ = EEL_USART3_BASE;
      break;
    case UsartPeripheral::kUart4:
      usart_base_ = EEL_UART4_BASE;
      break;
    case UsartPeripheral::kUart5:
      usart_base_ = EEL_UART5_BASE;
      break;
    case UsartPeripheral::kUsart6:
      usart_base_ = EEL_USART6_BASE;
      break;
  }
  ll::Rcc::EnableUsart(peripheral);
}

void Usart::ConfigureTx(PullUpDown pud, OutputType type, OutputSpeed speed) {
  tx_.ConfigureAf(tx_af_, pud, type, speed);
}

void Usart::ConfigureRx(PullUpDown pud, OutputType type, OutputSpeed speed) {
  rx_.ConfigureAf(rx_af_, pud, type, speed);
}

void Usart::Configure(eel::util::U32 baud_rate, WordLength word_length, Parity parity) {
  // First the baud rate in BRR
  SetBaudRate(baud_rate);

  // Set all the CR1 register bits
  auto cr1 = UsartReg(usart_base_)->CR1;
  SetUsartEnable(&cr1, true);
  SetWordLength(&cr1, word_length);
  SetParity(&cr1, parity);
  SetMode(&cr1, UsartMode::kTxRx);
  UsartReg(usart_base_)->CR1 = cr1;
}

void Usart::Write(const util::U8 *buffer, util::U32 size) {
  for (auto i = 0UL; i < size; ++i) {
    Write(buffer[i]);
  }
  // Wait for TC
  while ((UsartReg(usart_base_)->SR & eel::util::kBit6) == 0);
}

void Usart::Read(util::U8 *buffer, util::U32 size) {
  for (auto i = 0UL; i < size; ++i) {
    auto data = Read();
    buffer[i] = data;
  }
}

// private implementation
void Usart::SetBaudRate(eel::util::U32 value) {
  auto fclk{0UL};
  if (peripheral_ == UsartPeripheral::kUsart1 || peripheral_ == UsartPeripheral::kUsart6) {
    fclk = ll::Rcc::APB2Frequency();
  } else {
    fclk = ll::Rcc::APB1Frequency();
  }
  // TODO: have to revisit this calculation
  UsartReg(usart_base_)->BRR = (fclk + value/2) / value;
}

void Usart::SetUsartEnable(eel::util::U32 *cr1, bool status) {
  *cr1 = eel::util::SetOrClearBit(status, *cr1, 13);
}

void Usart::SetWordLength(eel::util::U32 *cr1, WordLength word_length) {
  *cr1 = eel::util::SetOrClearBit(word_length == WordLength::k9DataBits, *cr1, 12);
}

void Usart::SetParity(eel::util::U32 *cr1, Parity parity) {
  // Parity enable/disable
  *cr1 = eel::util::SetOrClearBit(parity != Parity::kNone, *cr1, 10);
  // Paridy odd/even
  *cr1 = eel::util::SetOrClearBit(parity == Parity::kOdd, *cr1, 9);
}

void Usart::SetMode(eel::util::U32 *cr1, UsartMode mode) {
  auto temp = *cr1 & ~(0x3U << 2);
  temp |= (eel::util::ToInt(mode) << 2);
  *cr1 = temp;
}

void Usart::Write(eel::util::U8 data) {
  // Wait for TXE
  while ((UsartReg(usart_base_)->SR & eel::util::kBit7) == 0);
  // Now write to DR
  UsartReg(usart_base_)->DR = data & static_cast<eel::util::U8>(0xff);
}

util::U8 Usart::Read() {
  // Wait for RXNE
  while ((UsartReg(usart_base_)->SR & eel::util::kBit5) == 0);
  // Now write to DR
  return static_cast<util::U8>(UsartReg(usart_base_)->DR & static_cast<eel::util::U8>(0xff));
}

}
