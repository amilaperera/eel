//
// Created by amila.perera on 20/05/2020.
//
#include "platform/stm32/uart.hpp"

namespace eel::hal::ll {
uart::uart(eel::hal::pin_name tx, eel::hal::pin_name rx) : tx_(tx), rx_(rx) {
}
}
