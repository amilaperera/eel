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

EEL_ALWAYS_INLINE auto PortRCB(eel::util::U32 port) {
  return reinterpret_cast<RCB*>(port);
}

class Gpio {
 public:
  explicit Gpio(eel::hal::gpio::Pin pin);
  void SetMode(eel::hal::gpio::Mode mode);
  void ConfigureOutput(eel::hal::gpio::PullUpDown pud,
                       eel::hal::gpio::OutputType type,
                       eel::hal::gpio::OutputSpeed speed);
  void Write(bool status);

 private:
  eel::util::U32 port_;
  eel::util::U32 pin_;
};

}
}
}
}

