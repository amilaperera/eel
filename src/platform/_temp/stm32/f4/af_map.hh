#pragma once

#include "platform/stm32/f4/common_defs.hh"
#include <utility>

namespace eel::hal::ll {

std::pair<bool, AfMode> check_usart_tx(UsartPeripheral peripheral, Pin pin);
std::pair<bool, AfMode> check_usart_rx(UsartPeripheral peripheral, Pin pin);

}
