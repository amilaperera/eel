//
// Created by Amila Perera on 14/04/2019.
//

#include "platform/stm32/ll/exti/exti.hh"
#include "util/bit_manip.hh"

using eel::util::SetBit;
using eel::util::ClearBit;
using eel::util::U32;

namespace eel::hal::ll {

void Exti::SetTrigger(ExtiLine line, Trigger trigger) {
  auto n{static_cast<U32>(line)};
  switch (trigger) {
    case Trigger::kFalling:ExtiReg()->FTSR = SetBit(ExtiReg()->FTSR, n);
      ExtiReg()->RTSR = ClearBit(ExtiReg()->RTSR, n);
      break;
    case Trigger::kRising:ExtiReg()->FTSR = ClearBit(ExtiReg()->FTSR, n);
      ExtiReg()->RTSR = SetBit(ExtiReg()->RTSR, n);
      break;
    case Trigger::kBoth:ExtiReg()->FTSR = SetBit(ExtiReg()->FTSR, n);
      ExtiReg()->RTSR = SetBit(ExtiReg()->RTSR, n);
      break;
  }
}

void Exti::Enable(ExtiLine line) {
  // enable interrupt
  ExtiReg()->IMR = SetBit(ExtiReg()->IMR, static_cast<U32>(line));
  // enable event
  ExtiReg()->EMR = SetBit(ExtiReg()->EMR, static_cast<U32>(line));
}

void Exti::Disable(ExtiLine line) {
  // disable interrupt
  ExtiReg()->IMR = ClearBit(ExtiReg()->IMR, static_cast<U32>(line));
  // disable event
  ExtiReg()->EMR = ClearBit(ExtiReg()->EMR, static_cast<U32>(line));
}

bool Exti::IsPending(ExtiLine line) {
  return eel::util::IsSet(ExtiReg()->PR, static_cast<U32>(line));
}

void Exti::ClearPending(ExtiLine line) {
  // the bit is cleared by writing 1
  ExtiReg()->PR = SetBit(ExtiReg()->PR, static_cast<U32>(line));
}

}
