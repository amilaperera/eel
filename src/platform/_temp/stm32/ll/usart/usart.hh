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

EEL_ALWAYS_INLINE auto UsartReg(eel::util::U32 peripheral) {
  return reinterpret_cast<UsartRCB *>(peripheral);
}

class Usart {
 public:
  explicit Usart(UsartPeripheral peripheral, Pin tx, Pin rx);
  void ConfigureTx(PullUpDown pud,
                   OutputType type,
                   OutputSpeed speed);
  void ConfigureRx(PullUpDown pud,
                   OutputType type,
                   OutputSpeed speed);
  void Configure(util::U32 baud_rate, WordLength word_length, Parity parity = Parity::kNone);
  void Write(const util::U8 *buffer, util::U32 size);
  void Read(util::U8 *buffer, util::U32 size);

 private:
  UsartPeripheral peripheral_;
  util::U32 usart_base_;
  ll::Gpio tx_;
  ll::Gpio rx_;
  AfMode tx_af_;
  AfMode rx_af_;

  EEL_ALWAYS_INLINE void SetBaudRate(util::U32 value);
  EEL_ALWAYS_INLINE void SetWordLength(util::U32 *cr1, WordLength word_length);
  EEL_ALWAYS_INLINE void SetParity(util::U32 *cr1, Parity parity);
  EEL_ALWAYS_INLINE void SetMode(util::U32 *cr1, UsartMode mode);
  EEL_ALWAYS_INLINE void SetUsartEnable(util::U32 *cr1, bool status);
  EEL_ALWAYS_INLINE void Write(util::U8 data);
  EEL_ALWAYS_INLINE util::U8 Read();
};

}
