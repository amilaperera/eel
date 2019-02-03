#pragma once

#include "util/preprocessor.hh"
#include "util/types.hh"
#include "platform/stm32/f4/common_defs.hh"
#include "platform/stm32/f4/memory_map.hh"

namespace eel {
namespace hal {
namespace ll {
namespace rcc {

struct RCB {
  eel::util::IO_U32 RCC_CR;
  eel::util::IO_U32 RCC_PLLCFGR;
  eel::util::IO_U32 RCC_CFGR;
  eel::util::IO_U32 RCC_CIR;
  eel::util::IO_U32 RCC_AHB1RSTR;
  eel::util::IO_U32 RCC_AHB2RSTR;
  eel::util::IO_U32 RCC_AHB3RSTR;
  eel::util::IO_U32 RESERVED0;
  eel::util::IO_U32 RCC_APB1RSTR;
  eel::util::IO_U32 RCC_APB2RSTR;
  eel::util::IO_U32 RESERVED1;
  eel::util::IO_U32 RESERVED2;
  eel::util::IO_U32 RCC_AHB1ENR;
  eel::util::IO_U32 RCC_AHB2ENR;
  eel::util::IO_U32 RCC_AHB3ENR;
  eel::util::IO_U32 RESERVED3;
  eel::util::IO_U32 RCC_APB1ENR;
  eel::util::IO_U32 RCC_APB2ENR;
  eel::util::IO_U32 RESERVED4;
  eel::util::IO_U32 RESERVED5;
  eel::util::IO_U32 RCC_AHB1LPENR;
  eel::util::IO_U32 RCC_AHB2LPENR;
  eel::util::IO_U32 RCC_AHB3LPENR;
  eel::util::IO_U32 RESERVED6;
  eel::util::IO_U32 RCC_APB1LPENR;
  eel::util::IO_U32 RCC_APB2LPENR;
  eel::util::IO_U32 RESERVED7;
  eel::util::IO_U32 RESERVED8;
  eel::util::IO_U32 RCC_BDCR;
  eel::util::IO_U32 RCC_CSR;
  eel::util::IO_U32 RESERVED9;
  eel::util::IO_U32 RESERVED10;
  eel::util::IO_U32 RCC_SSCGR;
  eel::util::IO_U32 RCC_PLLI2SCFGR;
  eel::util::IO_U32 RCC_PLLSAICFGR;
  eel::util::IO_U32 RCC_DCKCFGR;
  eel::util::IO_U32 RCC_CKGATENRR;
  eel::util::IO_U32 RCC_DCKCFGR2;
};

EEL_ALWAYS_INLINE auto RCCRegisterBlock() {
  return reinterpret_cast<eel::hal::ll::rcc::RCB*>(EEL_RCC_BASE);
}

EEL_ALWAYS_INLINE void SetGpioPort(eel::hal::gpio::Port port, bool status) {
  auto temp = RCCRegisterBlock()->RCC_AHB1ENR;
  if (status) {
    temp |= (1U << static_cast<eel::util::U8>(port));
  } else {
    temp &= ~(1U << static_cast<eel::util::U8>(port));
  }
  RCCRegisterBlock()->RCC_AHB1ENR = temp;
}

}
}
}
}
