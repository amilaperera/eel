#pragma once

#include "util/types.hh"
#include "util/preprocessor.hh"
#include "platform/common_defs.hh"
#include "platform/memory_map.hh"
#include "platform/stm32/ll/gpio/gpio.hh"
#include "platform/stm32/ll/rcc/rcc.hh"

namespace eel::hal::ll {

struct UsartRCB {
  eel::util::IO_U32 SR;
  eel::util::IO_U32 DR;
  eel::util::IO_U32 BRR;
  eel::util::IO_U32 CR1;
  eel::util::IO_U32 CR2;
  eel::util::IO_U32 CR3;
  eel::util::IO_U32 GTPR;
};

EEL_ALWAYS_INLINE auto usart_reg(eel::util::U32 peripheral) {
  return reinterpret_cast<UsartRCB *>(peripheral);
}

class Usart {
 public:
  explicit Usart(UsartPeripheral peripheral, Pin tx, Pin rx);
  void configure_tx(PullUpDown pud,
                    OutputType type,
                    OutputSpeed speed);
  void configure_rx(PullUpDown pud,
                    OutputType type,
                    OutputSpeed speed);
  void configure(util::U32 baud_rate, WordLength word_length, Parity parity = Parity::kNone);
  void write(const util::U8 *buffer, util::U32 size);
  void read(util::U8 *buffer, util::U32 size);

 private:
  UsartPeripheral peripheral_;
  util::U32 usart_base_;
  ll::Gpio tx_;
  ll::Gpio rx_;
  AfMode tx_af_;
  AfMode rx_af_;

  EEL_ALWAYS_INLINE void set_baud_rate(util::U32 value);
  EEL_ALWAYS_INLINE void set_word_length(util::U32 *cr1, WordLength word_length);
  EEL_ALWAYS_INLINE void set_parity(util::U32 *cr1, Parity parity);
  EEL_ALWAYS_INLINE void set_mode(util::U32 *cr1, UsartMode mode);
  EEL_ALWAYS_INLINE void set_uart_enable(util::U32 *cr1, bool status);
  EEL_ALWAYS_INLINE void write(util::U8 data);
  EEL_ALWAYS_INLINE util::U8 read();
};

}
