//
// Created by Amila Perera on 17/02/2019.
//
#include "platform/stm32/ll/usart/usart.hh"
#include "platform/stm32/ll/rcc/rcc.hh"

namespace eel {
namespace hal {
namespace ll {
namespace usart {

Usart::Usart(eel::hal::usart::Peripheral peripheral, eel::hal::gpio::Pin tx, eel::hal::gpio::Pin rx) :
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

void Usart::Configure(eel::util::U32 baud_rate, eel::hal::usart::WordLength word_length, eel::hal::usart::Parity parity, eel::hal::usart::OverSampling over_sampling) {

}

}
}
}
}
