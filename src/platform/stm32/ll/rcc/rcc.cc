#include "platform/stm32/ll/rcc/rcc.hh"

namespace eel {
namespace hal {
namespace ll {
namespace rcc {

void EnableGpioPort(eel::hal::gpio::Port port, bool status) {
  auto temp = RCCRegisterBlock()->RCC_AHB1ENR;
  if (status) {
    temp |= (1U << eel::util::ToInt(port));
  } else {
    temp &= ~(1U << eel::util::ToInt(port));
  }
  RCCRegisterBlock()->RCC_AHB1ENR = temp;
}

}
}
}
}
