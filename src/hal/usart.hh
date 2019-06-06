//
// Created by Amila Perera on 26/02/2019.
//

#pragma once
#include "platform/hal_ll.hh"

namespace eel::hal {

class Usart {
 public:
  explicit Usart(UsartPeripheral peripheral, Pin tx, Pin rx);
  void configure_tx(PullUpDown pud, OutputType type, OutputSpeed speed);
  void configure_rx(PullUpDown pud, OutputType type, OutputSpeed speed);
  void configure_tx_rx(PullUpDown pud, OutputType type, OutputSpeed speed);
  void configure(util::U32 baud_rate,
                 WordLength word_length = WordLength::k8DataBits,
                 Parity parity = Parity::kNone);
  void write(const util::U8 *buffer, util::U32 size);
  void read(util::U8 *buffer, util::U32 size);

 private:
  ll::Usart usart_ll_;
};

}
