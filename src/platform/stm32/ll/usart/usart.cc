//
// Created by Amila Perera on 17/02/2019.
//
#include <util/bit_manip.hh>
#include "platform/stm32/ll/usart/usart.hh"
#include "platform/stm32/ll/rcc/rcc.hh"

namespace eel {
namespace hal {
namespace ll {

Usart::Usart(usart::Peripheral peripheral, gpio::Pin tx, gpio::Pin rx) :
  peripheral_{peripheral},
  usart_base_{},
  tx_{tx},
  rx_{rx} {
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
  // TODO: Enable clock
  ll::Rcc::EnableUsart(peripheral);
}

void Usart::ConfigureTx(gpio::Af af, gpio::PullUpDown pud, gpio::OutputType type, gpio::OutputSpeed speed) {
  tx_.ConfigureAf(af, pud, type, speed);
}

void Usart::ConfigureRx(gpio::Af af, gpio::PullUpDown pud, gpio::OutputType type, gpio::OutputSpeed speed) {
  rx_.ConfigureAf(af, pud, type, speed);
}

void Usart::Configure(eel::util::U32 baud_rate, usart::WordLength word_length, usart::Parity parity) {
  // First the baud rate in BRR
  SetBaudRate(baud_rate);

  // Set all the CR1 register bits
  auto cr1 = UsartRegisterBlock(usart_base_)->CR1;
  SetUartEnable(&cr1, true);
  SetWordLength(&cr1, word_length);
  SetParity(&cr1, parity);
  SetMode(&cr1, usart::Mode::kTxOnly);
  UsartRegisterBlock(usart_base_)->CR1 = cr1;
}

void Usart::Write(const util::U8 *buffer, util::U32 size) {
  for (auto i = 0UL; i < size; ++i) {
    Write(buffer[i]);
  }
  // Wait for TC
  while ((UsartRegisterBlock(usart_base_)->SR & eel::util::kBit6) == 0);
}

// private implementation
void Usart::SetBaudRate(eel::util::U32 value) {
  auto fclk{0UL};
  if (peripheral_ == usart::Peripheral::kUsart1 || peripheral_ == usart::Peripheral::kUsart6) {
    fclk = ll::Rcc::APB2Frequency();
  } else {
    fclk = ll::Rcc::APB1Frequency();
  }
  // TODO: have to revisit this calculation
  UsartRegisterBlock(usart_base_)->BRR = (fclk + value/2) / value;
}

void Usart::SetUartEnable(eel::util::U32 *cr1, bool status) {
  *cr1 = eel::util::SetOrClear(status, *cr1, 13);
}

void Usart::SetWordLength(eel::util::U32 *cr1, usart::WordLength word_length) {
  *cr1 = eel::util::SetOrClear(word_length == usart::WordLength::k9DataBits, *cr1, 12);
}

void Usart::SetParity(eel::util::U32 *cr1, usart::Parity parity) {
  // Parity enable/disable
  *cr1 = eel::util::SetOrClear(parity != usart::Parity::kNone, *cr1, 10);
  // Paridy odd/even
  *cr1 = eel::util::SetOrClear(parity == usart::Parity::kOdd, *cr1, 9);
}

void Usart::SetMode(eel::util::U32 *cr1, usart::Mode mode) {
  auto temp = *cr1 & ~(0x3U << 2);
  temp |= (eel::util::ToInt(mode) << 2);
  *cr1 = temp;
}

void Usart::Write(eel::util::U8 data) {
  // Wait for TXE
  while ((UsartRegisterBlock(usart_base_)->SR & eel::util::kBit7) == 0);
  // Now write to DR
  UsartRegisterBlock(usart_base_)->DR = data & static_cast<eel::util::U8>(0xff);
}

}
}
}
