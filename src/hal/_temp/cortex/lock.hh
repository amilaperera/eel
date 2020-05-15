//
// Created by Amila Perera on 25/11/2018.
//
#pragma once

#include "util/preprocessor.hh"
#include "util/types.hh"
#include "cmsis/common/include/core_cm4.h"

namespace eel::hal{

// This supports nesting
class Lock {
 public:
  EEL_ALWAYS_INLINE Lock() : cpsr{__get_PRIMASK()} {
    __disable_irq();
  }

  EEL_ALWAYS_INLINE ~Lock() {
    __set_PRIMASK(cpsr);
  }
 private:
  eel::util::U32 cpsr;
};

}


