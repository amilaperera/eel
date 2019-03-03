#pragma once

#include "platform/stm32/f4/common_defs.hh"

namespace eel {
namespace hal {
namespace ll {

bool IsValidUsartTx(usart::Peripheral peripheral, gpio::Pin pin) {
  bool ret{false};
  switch (peripheral) {
    case usart::Peripheral::kUsart1:
      ret = (pin == gpio::Pin::A9 || pin == gpio::Pin::B6);
      break;
    case usart::Peripheral::kUsart2:
      ret = (pin == gpio::Pin::A2 || pin == gpio::Pin::D9);
      break;
    case usart::Peripheral::kUsart3:
      ret = (pin == gpio::Pin::B10 || pin == gpio::Pin::C10 || pin == gpio::Pin::D8);
      break;
    case usart::Peripheral::kUart4:
      ret = (pin == gpio::Pin::A1 || pin == gpio::Pin::C11);
      break;
    case usart::Peripheral::kUart5:
      ret = (pin == gpio::Pin::D2 || pin == gpio::Pin::E7);
      break;
    case usart::Peripheral::kUsart6:
      ret = (pin == gpio::Pin::C7 || pin == gpio::Pin::E8 || pin == gpio::Pin::G9);
      break;
  }
  return ret;
}

bool IsValidUsartRx(usart::Peripheral peripheral, gpio::Pin pin) {
  bool ret{false};
  switch (peripheral) {
    case usart::Peripheral::kUsart1:
      ret = (pin == gpio::Pin::A10 || pin == gpio::Pin::B7);
      break;
    case usart::Peripheral::kUsart2:
      ret = (pin == gpio::Pin::A3 || pin == gpio::Pin::D6);
      break;
    case usart::Peripheral::kUsart3:
      ret = (pin == gpio::Pin::B11 || pin == gpio::Pin::C5 || pin == gpio::Pin::C11  || pin == gpio::Pin::D9);
      break;
    case usart::Peripheral::kUart4:
      ret = (pin == gpio::Pin::A0 || pin == gpio::Pin::C10);
      break;
    case usart::Peripheral::kUart5:
      ret = (pin == gpio::Pin::C12 || pin == gpio::Pin::E5);
      break;
    case usart::Peripheral::kUsart6:
      ret = (pin == gpio::Pin::C6 || pin == gpio::Pin::G14);
      break;
  }
  return ret;
}

}
}
}
