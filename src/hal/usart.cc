//
// Created by Amila Perera on 26/02/2019.
//

#include "hal/usart.hh"
namespace eel {
namespace hal {
namespace usart {

Usart::Usart(eel::hal::usart::Peripheral peripheral, eel::hal::gpio::Pin tx, eel::hal::gpio::Pin rx) : usart_ll{peripheral, tx, rx} {
}

void Usart::ConfigureTx(eel::hal::gpio::Af af, eel::hal::gpio::PullUpDown pud, eel::hal::gpio::OutputType type, eel::hal::gpio::OutputSpeed speed) {
  usart_ll.ConfigureTx(af, pud, type, speed);
}

void Usart::ConfigureRx(eel::hal::gpio::Af af, eel::hal::gpio::PullUpDown pud, eel::hal::gpio::OutputType type, eel::hal::gpio::OutputSpeed speed) {
  usart_ll.ConfigureRx(af, pud, type, speed);
}

void Usart::Configure(eel::util::U32 baud_rate, eel::hal::usart::WordLength word_length, eel::hal::usart::Parity parity) {
  usart_ll.Configure(baud_rate, word_length, parity);
}

void Usart::Send(eel::util::U8 data) {
  usart_ll.Send(data);
}

}
}
}
