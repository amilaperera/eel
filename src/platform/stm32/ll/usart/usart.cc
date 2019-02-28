//
// Created by Amila Perera on 17/02/2019.
//
#include <util/bit_manip.hh>
#include "platform/stm32/ll/usart/usart.hh"
#include "platform/stm32/ll/rcc/rcc.hh"

namespace eel {
namespace hal {
namespace ll {
namespace usart {

Usart::Usart(eel::hal::usart::Peripheral peripheral, eel::hal::gpio::Pin tx, eel::hal::gpio::Pin rx) :
  peripheral_{peripheral},
  usart_base_{},
  tx_{tx},
  rx_{rx} {
  switch (peripheral) {
    case eel::hal::usart::Peripheral::kUsart1:
      usart_base_ = EEL_USART1_BASE;
      break;
    case eel::hal::usart::Peripheral::kUsart2:
      usart_base_ = EEL_USART2_BASE;
      break;
    case eel::hal::usart::Peripheral::kUsart3:
      usart_base_ = EEL_USART3_BASE;
      break;
    case eel::hal::usart::Peripheral::kUart4:
      usart_base_ = EEL_UART4_BASE;
      break;
    case eel::hal::usart::Peripheral::kUart5:
      usart_base_ = EEL_UART5_BASE;
      break;
    case eel::hal::usart::Peripheral::kUsart6:
      usart_base_ = EEL_USART6_BASE;
      break;
  }
  // TODO: Enable clock
  eel::hal::ll::rcc::Rcc::EnableUsart(peripheral);
}

void Usart::ConfigureTx(eel::hal::gpio::Af af, eel::hal::gpio::PullUpDown pud, eel::hal::gpio::OutputType type, eel::hal::gpio::OutputSpeed speed) {
  tx_.ConfigureAf(af, pud, type, speed);
}

void Usart::ConfigureRx(eel::hal::gpio::Af af, eel::hal::gpio::PullUpDown pud, eel::hal::gpio::OutputType type, eel::hal::gpio::OutputSpeed speed) {
  rx_.ConfigureAf(af, pud, type, speed);
}

void Usart::Configure(eel::util::U32 baud_rate, eel::hal::usart::WordLength word_length, eel::hal::usart::Parity parity) {
  // UE
  auto temp = UsartRegisterBlock(usart_base_)->CR1;
  temp = eel::util::SetBit(temp, 13);
  UsartRegisterBlock(usart_base_)->CR1 = temp;
  // M bit
  SetWordLength(word_length);
  SetBaudRate(baud_rate);
  SetMode(eel::hal::usart::Mode::kTxRx);
  SetParity(parity);
}

void Usart::Send(eel::util::U8 data) {
  while ((UsartRegisterBlock(usart_base_)->SR & eel::util::kBit7) == 0);
  UsartRegisterBlock(usart_base_)->DR = data & static_cast<eel::util::U8>(0xff);
}


// private implementation
void Usart::SetBaudRate(eel::util::U32 value) {
  auto fclk{0UL};
  if (peripheral_ == eel::hal::usart::Peripheral::kUsart1 || peripheral_ == eel::hal::usart::Peripheral::kUsart6) {
    fclk = eel::hal::ll::rcc::Rcc::APB2Frequency();
  } else {
    fclk = eel::hal::ll::rcc::Rcc::APB1Frequency();
  }
  // TODO: have to revisit this calculation
  UsartRegisterBlock(usart_base_)->BRR = (fclk + value/2) / value;
}

void Usart::SetWordLength(eel::hal::usart::WordLength word_length) {
  auto temp = UsartRegisterBlock(usart_base_)->CR1;
  UsartRegisterBlock(usart_base_)->CR1 = eel::util::SetOrClear(word_length == eel::hal::usart::WordLength::k9DataBits, temp, 12);
}

void Usart::SetParity(eel::hal::usart::Parity parity) {
  auto temp = UsartRegisterBlock(usart_base_)->CR1;
  temp = eel::util::SetOrClear(parity != eel::hal::usart::Parity::kNone, temp, 10);
  UsartRegisterBlock(usart_base_)->CR1 = eel::util::SetOrClear(parity == eel::hal::usart::Parity::kOdd, temp, 9);
}

void Usart::SetMode(eel::hal::usart::Mode mode) {
  // set Tx-Rx mode
  auto temp = UsartRegisterBlock(usart_base_)->CR1;
  //temp = eel::util::SetBit(temp, 2); // RX Enable
  temp = eel::util::SetBit(temp, 3); // TX Enable
  UsartRegisterBlock(usart_base_)->CR1 = temp;
}

}
}
}
}
