//
// Created by Amila Perera on 26/02/2019.
//

#include "hal/usart.hh"
namespace eel {
namespace hal {

Usart::Usart(usart::Peripheral peripheral, gpio::Pin tx, gpio::Pin rx) : usart_ll_{peripheral, tx, rx} {
}

void Usart::configure_tx(gpio::PullUpDown pud, gpio::OutputType type, gpio::OutputSpeed speed) {
  usart_ll_.configure_tx(pud, type, speed);
}

void Usart::configure_rx(gpio::PullUpDown pud, gpio::OutputType type, gpio::OutputSpeed speed) {
  usart_ll_.configure_rx(pud, type, speed);
}

void Usart::configure_tx_rx(gpio::PullUpDown pud, gpio::OutputType type, gpio::OutputSpeed speed) {
  configure_tx(pud, type, speed);
  configure_rx(pud, type, speed);
}

void Usart::configure(util::U32 baud_rate, usart::WordLength word_length, usart::Parity parity) {
  usart_ll_.configure(baud_rate, word_length, parity);
}

void Usart::write(const util::U8 *buffer, util::U32 size) {
  usart_ll_.write(buffer, size);
}

void Usart::read(util::U8 *buffer, util::U32 size) {
  usart_ll_.read(buffer, size);
}

}
}
