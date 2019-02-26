//
// Created by Amila Perera on 26/02/2019.
//

#pragma once
#include "platform/hal_ll.hh"

namespace eel {
namespace hal {
namespace usart {

class Usart {
 public:
  explicit Usart(eel::hal::usart::Peripheral peripheral,
                 eel::hal::gpio::Pin tx,
                 eel::hal::gpio::Pin rx);
  void ConfigureTx(eel::hal::gpio::Af af,
                   eel::hal::gpio::PullUpDown pud,
                   eel::hal::gpio::OutputType type,
                   eel::hal::gpio::OutputSpeed speed);
  void ConfigureRx(eel::hal::gpio::Af af,
                   eel::hal::gpio::PullUpDown pud,
                   eel::hal::gpio::OutputType type,
                   eel::hal::gpio::OutputSpeed speed);
  void Configure(eel::util::U32 baud_rate, eel::hal::usart::WordLength word_length, eel::hal::usart::Parity parity = eel::hal::usart::Parity::kNone);
  void Send(eel::util::U8 data);

 private:
  eel::hal::ll::usart::Usart usart_ll;
};

}
}
}

