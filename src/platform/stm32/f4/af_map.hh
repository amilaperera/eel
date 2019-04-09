#pragma once

#include "platform/stm32/f4/common_defs.hh"
#include <utility>

namespace eel::hal::ll {

inline std::pair<bool, gpio::Af> check_usart_tx(usart::Peripheral peripheral, gpio::Pin pin) {
  std::pair<bool, gpio::Af> result{false, gpio::Af::k0};
  switch (peripheral) {
    case usart::Peripheral::kUsart1:
      result = std::make_pair(pin == gpio::Pin::A9 || pin == gpio::Pin::B6, gpio::Af::k7);
      break;
    case usart::Peripheral::kUsart2:
      result = std::make_pair(pin == gpio::Pin::A2 || pin == gpio::Pin::D5, gpio::Af::k7);
      break;
    case usart::Peripheral::kUsart3:
      result = std::make_pair(pin == gpio::Pin::B10 || pin == gpio::Pin::C10 || pin == gpio::Pin::D8, gpio::Af::k7);
      break;
    case usart::Peripheral::kUart4:
      result = std::make_pair(pin == gpio::Pin::A0 || pin == gpio::Pin::C10, gpio::Af::k8);
      break;
    case usart::Peripheral::kUart5:
      result = std::make_pair(pin == gpio::Pin::C12 || pin == gpio::Pin::E8, gpio::Af::k8);
      break;
    case usart::Peripheral::kUsart6:
      result = std::make_pair(pin == gpio::Pin::C6 || pin == gpio::Pin::G14, gpio::Af::k8);
      break;
  }
  return result;
}

inline std::pair<bool, gpio::Af> check_usart_rx(usart::Peripheral peripheral, gpio::Pin pin) {
  std::pair<bool, gpio::Af> result{false, gpio::Af::k0};
  switch (peripheral) {
    case usart::Peripheral::kUsart1:
      result = std::make_pair(pin == gpio::Pin::A10 || pin == gpio::Pin::B7, gpio::Af::k7);
      break;
    case usart::Peripheral::kUsart2:
      result = std::make_pair(pin == gpio::Pin::A3 || pin == gpio::Pin::D6, gpio::Af::k7);
      break;
    case usart::Peripheral::kUsart3:
      result = std::make_pair(pin == gpio::Pin::B11 || pin == gpio::Pin::C5 || pin == gpio::Pin::C11  || pin == gpio::Pin::D9, gpio::Af::k7);
      break;
    case usart::Peripheral::kUart4:
      result = std::make_pair(pin == gpio::Pin::A1 || pin == gpio::Pin::C11, gpio::Af::k8);
      break;
    case usart::Peripheral::kUart5:
      result = std::make_pair(pin == gpio::Pin::D2 || pin == gpio::Pin::E7, gpio::Af::k8);
      break;
    case usart::Peripheral::kUsart6:
      result = std::make_pair(pin == gpio::Pin::C7 || pin == gpio::Pin::G9, gpio::Af::k8);
      break;
  }
  return result;
}

}
