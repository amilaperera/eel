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
namespace usart {

struct RCB {
  eel::util::IO_U32 SR;
  eel::util::IO_U32 DR;
  eel::util::IO_U32 BRR;
  eel::util::IO_U32 CR1;
  eel::util::IO_U32 CR2;
  eel::util::IO_U32 CR3;
  eel::util::IO_U32 GTPR;
};

EEL_ALWAYS_INLINE auto UsartRegisterBlock(eel::util::U32 peripheral) {
  return reinterpret_cast<usart::RCB *>(peripheral);
}

class Usart {
 public:
  explicit Usart(eel::hal::usart::Peripheral peripheral,
      eel::hal::gpio::Pin tx,
      eel::hal::gpio::Pin rx);
  void ConfigureTx(eel::hal::gpio::Af af,
                   eel::hal::gpio::PullUpDown pud,
                   eel::hal::gpio::OutputType type,
                   eel::hal::gpio::OutputSpeed speed);
  void ConfigureRx(eel::hal::gpio::Af af,
                   eel::hal::gpio::PullUpDown pud,
                   eel::hal::gpio::OutputType type,
                   eel::hal::gpio::OutputSpeed speed);
  void Configure(eel::util::U32 baud_rate, eel::hal::usart::WordLength word_length, eel::hal::usart::Parity parity = eel::hal::usart::Parity::kNone);
  void Send(eel::util::U8 data);
 private:
  eel::hal::usart::Peripheral peripheral_;
  eel::util::U32 usart_base_;
  eel::hal::ll::gpio::Gpio tx_;
  eel::hal::ll::gpio::Gpio rx_;

  void SetBaudRate(eel::util::U32 value);
  void SetWordLength(eel::hal::usart::WordLength word_length);
  void SetParity(eel::hal::usart::Parity parity);
  void SetMode(eel::hal::usart::Mode mode);
  EEL_ALWAYS_INLINE void SetWordLength(eel::util::U32 *cr1, eel::hal::usart::WordLength word_length);
  EEL_ALWAYS_INLINE void SetParity(eel::util::U32 *cr1, eel::hal::usart::Parity parity);
  EEL_ALWAYS_INLINE void SetMode(eel::util::U32 *cr1, eel::hal::usart::Mode mode);
  EEL_ALWAYS_INLINE void SetUartEnable(eel::util::U32 *cr1, bool status);
};

}
}
}
}
