#pragma once

#include "platform/stm32/f4/common_defs.hh"
#include "platform/stm32/f4/memory_map.hh"
#include "util/types.hh"
#include "util/preprocessor.hh"
#include "platform/stm32/ll/gpio/gpio.hh"
#include "platform/stm32/ll/rcc/rcc.hh"

namespace eel {
namespace hal {
namespace ll {

struct UsartRCB {
  eel::util::IO_U32 SR;
  eel::util::IO_U32 DR;
  eel::util::IO_U32 BRR;
  eel::util::IO_U32 CR1;
  eel::util::IO_U32 CR2;
  eel::util::IO_U32 CR3;
  eel::util::IO_U32 GTPR;
};

EEL_ALWAYS_INLINE auto UsartRegisterBlock(eel::util::U32 peripheral) {
  return reinterpret_cast<UsartRCB *>(peripheral);
}

class Usart {
 public:
  explicit Usart(usart::Peripheral peripheral, gpio::Pin tx, gpio::Pin rx);
  void ConfigureTx(gpio::Af af,
                   gpio::PullUpDown pud,
                   gpio::OutputType type,
                   gpio::OutputSpeed speed);
  void ConfigureRx(gpio::Af af,
                   gpio::PullUpDown pud,
                   gpio::OutputType type,
                   gpio::OutputSpeed speed);
  void Configure(util::U32 baud_rate, usart::WordLength word_length, usart::Parity parity = usart::Parity::kNone);
  void Send(util::U8 data);
 private:
  usart::Peripheral peripheral_;
  util::U32 usart_base_;
  ll::Gpio tx_;
  ll::Gpio rx_;

  EEL_ALWAYS_INLINE void SetBaudRate(util::U32 value);
  EEL_ALWAYS_INLINE void SetWordLength(util::U32 *cr1, usart::WordLength word_length);
  EEL_ALWAYS_INLINE void SetParity(util::U32 *cr1, usart::Parity parity);
  EEL_ALWAYS_INLINE void SetMode(util::U32 *cr1, usart::Mode mode);
  EEL_ALWAYS_INLINE void SetUartEnable(util::U32 *cr1, bool status);
};

}
}
}
