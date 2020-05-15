#pragma once

#include "util/bit_manip.hh"
#include "platform/memory_map.hh"
#include "util/preprocessor.hh"
#include "platform/stm32/ll/exti/exti.hh"
#include "platform/stm32/ll/gpio/gpio.hh"

namespace eel::hal::ll {
struct SysCfgRCB {
  eel::util::IO_U32 MEMRMP;
  eel::util::IO_U32 PMC;
  eel::util::IO_U32 EXTICR[4];
  eel::util::IO_U32 CMPCR;
  eel::util::IO_U32 CFGR;
};

EEL_ALWAYS_INLINE auto SysCfgReg() {
  return reinterpret_cast<SysCfgRCB*>(EEL_SYSCFG_BASE);
}

struct SysCfg {
  static void SetExtiConfiguration(ExtiLine exit_line, Port port);
};

}
