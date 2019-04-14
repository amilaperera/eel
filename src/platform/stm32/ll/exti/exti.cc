//
// Created by Amila Perera on 14/04/2019.
//

#include "platform/stm32/ll/exti/exti.hh"
#include "util/bit_manip.hh"

using eel::util::set_bit;
using eel::util::clear_bit;

namespace eel::hal::ll {

void Exti::set_trigger(ExtiLine line, Trigger trigger) {
  auto n{static_cast<eel::util::U32>(line)};
  switch (trigger) {
    case Trigger::kFalling:
      exti_reg()->FTSR = set_bit(exti_reg()->FTSR, n);
      exti_reg()->RTSR = clear_bit(exti_reg()->RTSR, n);
      break;
    case Trigger::kRising:
      exti_reg()->FTSR = clear_bit(exti_reg()->FTSR, n);
      exti_reg()->RTSR = set_bit(exti_reg()->RTSR, n);
      break;
    case Trigger::kBoth:
      exti_reg()->FTSR = set_bit(exti_reg()->FTSR, n);
      exti_reg()->RTSR = set_bit(exti_reg()->RTSR, n);
      break;
  }
}

void Exti::enable(ExtiLine line) {

}

void Exti::disable(ExtiLine line) {

}

}
