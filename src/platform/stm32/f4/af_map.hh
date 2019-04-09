#pragma once

#include "platform/stm32/f4/common_defs.hh"
#include <utility>

namespace eel::hal::ll {

std::pair<bool, gpio::Af> check_usart_tx(usart::Peripheral peripheral, gpio::Pin pin);
std::pair<bool, gpio::Af> check_usart_rx(usart::Peripheral peripheral, gpio::Pin pin);

}
