//
// Created by Amila Perera on 26/02/2019.
//

#include "hal/usart.hh"
namespace eel::hal {

Usart::Usart(UsartPeripheral peripheral, Pin tx, Pin rx) : usart_ll_{peripheral, tx, rx} {
}

void Usart::ConfigureTx(PullUpDown pud, OutputType type, OutputSpeed speed) {
  usart_ll_.ConfigureTx(pud, type, speed);
}

void Usart::ConfigureRx(PullUpDown pud, OutputType type, OutputSpeed speed) {
  usart_ll_.ConfigureRx(pud, type, speed);
}

void Usart::ConfigureTxRx(PullUpDown pud, OutputType type, OutputSpeed speed) {
  ConfigureTx(pud, type, speed);
  ConfigureRx(pud, type, speed);
}

void Usart::Configure(util::U32 baud_rate, WordLength word_length, Parity parity) {
  usart_ll_.Configure(baud_rate, word_length, parity);
}

void Usart::Write(const util::U8 *buffer, util::U32 size) {
  usart_ll_.Write(buffer, size);
}

void Usart::Read(util::U8 *buffer, util::U32 size) {
  usart_ll_.Read(buffer, size);
}

}
