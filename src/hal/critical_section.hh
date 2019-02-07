//
// Created by Amila Perera on 25/11/2018.
//
#pragma once

#include "util/preprocessor.hh"
#include "cmsis/include/core_cm4.h"

namespace eel {
namespace hal{
namespace core {

EEL_ALWAYS_INLINE void EnterCriticalSection() {
  // TODO: Support nesting
  __disable_irq();
}

EEL_ALWAYS_INLINE void ExitCriticalSection() {
  // TODO: Support nesting
  __enable_irq();
}

}
}
}


