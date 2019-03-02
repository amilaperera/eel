//
// Created by Amila Perera on 26/02/2019.
//

#include "hal/usart.hh"
namespace eel {
namespace hal {

Usart::Usart(usart::Peripheral peripheral, gpio::Pin tx, gpio::Pin rx) : usart_ll{peripheral, tx, rx} {
}

void Usart::ConfigureTx(gpio::Af af, gpio::PullUpDown pud, gpio::OutputType type, gpio::OutputSpeed speed) {
  usart_ll.ConfigureTx(af, pud, type, speed);
}

void Usart::ConfigureRx(gpio::Af af, gpio::PullUpDown pud, gpio::OutputType type, gpio::OutputSpeed speed) {
  usart_ll.ConfigureRx(af, pud, type, speed);
}

void Usart::Configure(util::U32 baud_rate, usart::WordLength word_length, usart::Parity parity) {
  usart_ll.Configure(baud_rate, word_length, parity);
}

void Usart::Send(util::U8 data) {
  usart_ll.Send(data);
}

}
}
