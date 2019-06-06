//
// Created by Amila Perera on 26/02/2019.
//

#pragma once
#include "platform/hal_ll.hh"

namespace eel::hal {

class Usart {
 public:
  explicit Usart(UsartPeripheral peripheral, Pin tx, Pin rx);
  void ConfigureTx(PullUpDown pud, OutputType type, OutputSpeed speed);
  void ConfigureRx(PullUpDown pud, OutputType type, OutputSpeed speed);
  void ConfigureTxRx(PullUpDown pud, OutputType type, OutputSpeed speed);
  void Configure(util::U32 baud_rate,
                 WordLength word_length = WordLength::k8DataBits,
                 Parity parity = Parity::kNone);
  void Write(const util::U8 *buffer, util::U32 size);
  void Read(util::U8 *buffer, util::U32 size);

 private:
  ll::Usart usart_ll_;
};

}
