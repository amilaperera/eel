//
// Created by Amila Perera on 26/02/2019.
//

#pragma once
#include "platform/hal_ll.hh"

namespace eel {
namespace hal {

class Usart {
 public:
  explicit Usart(usart::Peripheral peripheral, gpio::Pin tx, gpio::Pin rx);
  void ConfigureTx(gpio::Af af, gpio::PullUpDown pud, gpio::OutputType type, gpio::OutputSpeed speed);
  void ConfigureRx(gpio::Af af, gpio::PullUpDown pud, gpio::OutputType type, gpio::OutputSpeed speed);
  void Configure(util::U32 baud_rate, usart::WordLength word_length, usart::Parity parity = usart::Parity::kNone);
  void Send(util::U8 data);

 private:
  ll::Usart usart_ll;
};

}
}

