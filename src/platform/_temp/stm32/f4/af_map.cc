//
// Created by Amila Perera on 9/04/2019.
//
#include "platform/stm32/f4/af_map.hh"

namespace eel::hal::ll {
std::pair<bool, AfMode> check_usart_tx(UsartPeripheral peripheral, Pin pin) {
  std::pair<bool, AfMode> result{false, AfMode::k0};
  switch (peripheral) {
    case UsartPeripheral::kUsart1:
      result = std::make_pair(pin == Pin::A9 || pin == Pin::B6, AfMode::k7);
      break;
    case UsartPeripheral::kUsart2:
      result = std::make_pair(pin == Pin::A2 || pin == Pin::D5, AfMode::k7);
      break;
    case UsartPeripheral::kUsart3:
      result = std::make_pair(pin == Pin::B10 || pin == Pin::C10 || pin == Pin::D8, AfMode::k7);
      break;
    case UsartPeripheral::kUart4:
      result = std::make_pair(pin == Pin::A0 || pin == Pin::C10, AfMode::k8);
      break;
    case UsartPeripheral::kUart5:
      result = std::make_pair(pin == Pin::C12 || pin == Pin::E8, AfMode::k8);
      break;
    case UsartPeripheral::kUsart6:
      result = std::make_pair(pin == Pin::C6 || pin == Pin::G14, AfMode::k8);
      break;
  }
  return result;
}

std::pair<bool, AfMode> check_usart_rx(UsartPeripheral peripheral, Pin pin) {
  std::pair<bool, AfMode> result{false, AfMode::k0};
  switch (peripheral) {
    case UsartPeripheral::kUsart1:
      result = std::make_pair(pin == Pin::A10 || pin == Pin::B7, AfMode::k7);
      break;
    case UsartPeripheral::kUsart2:
      result = std::make_pair(pin == Pin::A3 || pin == Pin::D6, AfMode::k7);
      break;
    case UsartPeripheral::kUsart3:
      result = std::make_pair(pin == Pin::B11 || pin == Pin::C5 || pin == Pin::C11  || pin == Pin::D9, AfMode::k7);
      break;
    case UsartPeripheral::kUart4:
      result = std::make_pair(pin == Pin::A1 || pin == Pin::C11, AfMode::k8);
      break;
    case UsartPeripheral::kUart5:
      result = std::make_pair(pin == Pin::D2 || pin == Pin::E7, AfMode::k8);
      break;
    case UsartPeripheral::kUsart6:
      result = std::make_pair(pin == Pin::C7 || pin == Pin::G9, AfMode::k8);
      break;
  }
  return result;
}

}
