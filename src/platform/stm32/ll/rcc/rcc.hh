#pragma once

#include "util/preprocessor.hh"
#include "util/types.hh"
#include "platform/common_defs.hh"
#include "platform/memory_map.hh"

namespace eel::hal::ll {

struct RccRCB {
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

EEL_ALWAYS_INLINE auto RccReg() {
  return reinterpret_cast<ll::RccRCB*>(EEL_RCC_BASE);
}

class Rcc {
 public:
  static void EnablePort(Port port, bool status = true);
  static void EnableUsart(UsartPeripheral peripheral, bool status = true);
  static eel::util::U32 AHBFrequency();
  static eel::util::U32 APB1Frequency();
  static eel::util::U32 APB2Frequency();
  static eel::util::U32 AHBPrescalar();
  static eel::util::U32 APB1Prescalar();
  static eel::util::U32 APB2Prescalar();
 private:
  static constexpr eel::util::U16 ahb_prescaler[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};
  static constexpr eel::util::U8 apb_prescaler[8] = {0, 0, 0, 0, 1, 2, 3, 4}; // for bit shifting
};

}

