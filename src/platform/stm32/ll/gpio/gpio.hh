#pragma once

#include "platform/stm32/f4/common_defs.hh"
#include "platform/stm32/f4/memory_map.hh"
#include "util/types.hh"
#include "util/preprocessor.hh"

namespace eel {
namespace hal {
namespace ll {
namespace gpio {

struct RCB {
  eel::util::IO_U32 MODER;
  eel::util::IO_U32 OTYPER;
  eel::util::IO_U32 OSPEEDR;
  eel::util::IO_U32 PUPDR;
  eel::util::IO_U32 IDR;
  eel::util::IO_U32 ODR;
  eel::util::IO_U32 BSRR;
  eel::util::IO_U32 LCKR;
  eel::util::IO_U32 AFLR;
  eel::util::IO_U32 AFHR;
};

EEL_ALWAYS_INLINE auto GpioRegisterBlock(eel::util::U32 port) {
  return reinterpret_cast<RCB*>(port);
}

EEL_ALWAYS_INLINE void SetPud(eel::util::U32 port_base, eel::util::U32 pin, eel::hal::gpio::PullUpDown pud) {
  auto temp = GpioRegisterBlock(port_base)->PUPDR;
  temp &= ~(3U << (pin * 2U));
  temp |= (util::ToInt(pud) << (pin * 2U));
  GpioRegisterBlock(port_base)->PUPDR = temp;
}

EEL_ALWAYS_INLINE void SetOType(eel::util::U32 port_base, eel::util::U32 pin, eel::hal::gpio::OutputType type) {
  auto temp = GpioRegisterBlock(port_base)->OTYPER;
  temp &= ~(1U << pin);
  temp |= (util::ToInt(type) << pin);
  GpioRegisterBlock(port_base)->OTYPER = temp;
}

EEL_ALWAYS_INLINE void SetOSpeed(eel::util::U32 port_base, eel::util::U32 pin, eel::hal::gpio::OutputSpeed speed) {
  auto temp = GpioRegisterBlock(port_base)->OSPEEDR;
  temp &= ~(3U << (pin * 2U));
  temp |= (util::ToInt(speed) << (pin * 2U));
  GpioRegisterBlock(port_base)->OSPEEDR = temp;
}

class Gpio {
 public:
  explicit Gpio(eel::hal::gpio::Pin pin);
  void SetMode(eel::hal::gpio::Mode mode);
  void ConfigureOutput(eel::hal::gpio::PullUpDown pud,
                       eel::hal::gpio::OutputType type,
                       eel::hal::gpio::OutputSpeed speed);
  void ConfigureInput(eel::hal::gpio::PullUpDown pud);
  void Write(bool status);
  bool Read() const;
  void Toggle();

 private:
  eel::hal::gpio::Port port_;
  eel::util::U32 pin_;
  eel::util::U32 port_base_;
};

}
}
}
}

