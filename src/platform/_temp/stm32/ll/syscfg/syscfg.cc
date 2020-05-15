//
// Created by Amila Perera on 8/06/2019.
//

#include "platform/stm32/ll/syscfg/syscfg.hh"
namespace eel::hal::ll {
void SysCfg::SetExtiConfiguration(ExtiLine exti_line, Port port) {
  auto cr_idx = util::ToInt(exti_line) / 4;
  auto cr_offset = util::ToInt(exti_line) % 4;
  auto bits = util::ToInt(port);

  auto reg_val = SysCfgReg()->EXTICR[cr_idx];
  reg_val &= ~(0xfU << (cr_offset * 4U));
  reg_val |= (bits << (cr_offset * 4U));
  SysCfgReg()->EXTICR[cr_idx] = reg_val;
}
}

