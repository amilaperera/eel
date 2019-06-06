//
// Created by Amila Perera on 26/02/2019.
//

#include "hal/usart.hh"
namespace eel::hal {

Usart::Usart(UsartPeripheral peripheral, Pin tx, Pin rx) : usart_ll_{peripheral, tx, rx} {
}

void Usart::configure_tx(PullUpDown pud, OutputType type, OutputSpeed speed) {
  usart_ll_.configure_tx(pud, type, speed);
}

void Usart::configure_rx(PullUpDown pud, OutputType type, OutputSpeed speed) {
  usart_ll_.configure_rx(pud, type, speed);
}

void Usart::configure_tx_rx(PullUpDown pud, OutputType type, OutputSpeed speed) {
  configure_tx(pud, type, speed);
  configure_rx(pud, type, speed);
}

void Usart::configure(util::U32 baud_rate, WordLength word_length, Parity parity) {
  usart_ll_.configure(baud_rate, word_length, parity);
}

void Usart::write(const util::U8 *buffer, util::U32 size) {
  usart_ll_.write(buffer, size);
}

void Usart::read(util::U8 *buffer, util::U32 size) {
  usart_ll_.read(buffer, size);
}

}
