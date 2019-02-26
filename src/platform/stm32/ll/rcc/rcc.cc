#include "platform/stm32/ll/rcc/rcc.hh"
#include "util/bit_manip.hh"
#include "stm32f446xx.h"

namespace eel {
namespace hal {
namespace ll {
namespace rcc {

void Rcc::EnableGpioPort(eel::hal::gpio::Port port, bool status) {
  auto temp = RCCRegisterBlock()->RCC_AHB1ENR;
  if (status) {
    temp |= (1U << eel::util::ToInt(port));
  } else {
    temp &= ~(1U << eel::util::ToInt(port));
  }
  RCCRegisterBlock()->RCC_AHB1ENR = temp;
}

void Rcc::EnableUsart(eel::hal::usart::Peripheral peripheral, bool status) {
  // usart2, usart3, uart4, uart5
  eel::util::IO_U32 temp{};
  switch (peripheral) {
    case eel::hal::usart::Peripheral::kUsart1:
      temp = RCCRegisterBlock()->RCC_APB2ENR;
      temp = eel::util::SetOrClear(status, temp, 4);
      RCCRegisterBlock()->RCC_APB2ENR = temp;
      break;
    case eel::hal::usart::Peripheral::kUsart2:
      temp = RCCRegisterBlock()->RCC_APB1ENR;
      temp = eel::util::SetOrClear(status, temp, 17);
      RCCRegisterBlock()->RCC_APB1ENR = temp;
      break;
    case eel::hal::usart::Peripheral::kUsart3:
      temp = RCCRegisterBlock()->RCC_APB1ENR;
      temp = eel::util::SetOrClear(status, temp, 18);
      RCCRegisterBlock()->RCC_APB1ENR = temp;
      break;
    case eel::hal::usart::Peripheral::kUart4:
      temp = RCCRegisterBlock()->RCC_APB1ENR;
      temp = eel::util::SetOrClear(status, temp, 19);
      RCCRegisterBlock()->RCC_APB1ENR = temp;
      break;
    case eel::hal::usart::Peripheral::kUart5:
      temp = RCCRegisterBlock()->RCC_APB1ENR;
      temp = eel::util::SetOrClear(status, temp, 20);
      RCCRegisterBlock()->RCC_APB1ENR = temp;
      break;
    case eel::hal::usart::Peripheral::kUsart6:
      temp = RCCRegisterBlock()->RCC_APB2ENR;
      temp = eel::util::SetOrClear(status, temp, 5);
      RCCRegisterBlock()->RCC_APB2ENR = temp;
      break;
  }
}

eel::util::U32 Rcc::AHBPrescalar() {
  // TODO: table is set for shifting
  //return ahb_prescaler[(RCCRegisterBlock()->RCC_CFGR >> 4) & 0xEU];
  return 0;
}

eel::util::U32 Rcc::APB1Prescalar() {
  // TODO: table is set for shifting
  //return apb_prescaler[(RCCRegisterBlock()->RCC_CFGR >> 10) & 0x7U];
  return 0;
}

eel::util::U32 Rcc::APB2Prescalar() {
  // TODO: table is set for shifting
  //return apb_prescaler[(RCCRegisterBlock()->RCC_CFGR >> 13) & 0x7U];
  return 0;
}

eel::util::U32 Rcc::AHBFrequency() {
  return SystemCoreClock >> ahb_prescaler[(RCCRegisterBlock()->RCC_CFGR >> 4) & 0xEU];
}

eel::util::U32 Rcc::APB1Frequency() {
  return AHBFrequency() >> apb_prescaler[(RCCRegisterBlock()->RCC_CFGR >> 10) & 0x7U];
}

eel::util::U32 Rcc::APB2Frequency() {
  return AHBFrequency() >> apb_prescaler[(RCCRegisterBlock()->RCC_CFGR >> 13) & 0x7U];
}

}
}
}
}
