#include "platform/stm32/ll/rcc/rcc.hh"
#include "util/bit_manip.hh"
#include "platform/mcu.hh"

namespace eel::hal::ll {

void Rcc::EnablePort(Port port, bool status) {
  auto temp = RccReg()->RCC_AHB1ENR;
  if (status) {
    temp |= (1U << eel::util::ToInt(port));
  } else {
    temp &= ~(1U << eel::util::ToInt(port));
  }
  RccReg()->RCC_AHB1ENR = temp;
}

void Rcc::EnableUsart(UsartPeripheral peripheral, bool status) {
  // usart2, usart3, uart4, uart5
  eel::util::IO_U32 temp{};
  switch (peripheral) {
    case UsartPeripheral::kUsart1:
      temp = RccReg()->RCC_APB2ENR;
      temp = eel::util::SetOrClearBit(status, temp, 4);
      RccReg()->RCC_APB2ENR = temp;
      break;
    case UsartPeripheral::kUsart2:
      temp = RccReg()->RCC_APB1ENR;
      temp = eel::util::SetOrClearBit(status, temp, 17);
      RccReg()->RCC_APB1ENR = temp;
      break;
    case UsartPeripheral::kUsart3:
      temp = RccReg()->RCC_APB1ENR;
      temp = eel::util::SetOrClearBit(status, temp, 18);
      RccReg()->RCC_APB1ENR = temp;
      break;
    case UsartPeripheral::kUart4:
      temp = RccReg()->RCC_APB1ENR;
      temp = eel::util::SetOrClearBit(status, temp, 19);
      RccReg()->RCC_APB1ENR = temp;
      break;
    case UsartPeripheral::kUart5:
      temp = RccReg()->RCC_APB1ENR;
      temp = eel::util::SetOrClearBit(status, temp, 20);
      RccReg()->RCC_APB1ENR = temp;
      break;
    case UsartPeripheral::kUsart6:
      temp = RccReg()->RCC_APB2ENR;
      temp = eel::util::SetOrClearBit(status, temp, 5);
      RccReg()->RCC_APB2ENR = temp;
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
  return SystemCoreClock >> ahb_prescaler[(RccReg()->RCC_CFGR >> 4) & 0xEU];
}

eel::util::U32 Rcc::APB1Frequency() {
  return AHBFrequency() >> apb_prescaler[(RccReg()->RCC_CFGR >> 10) & 0x7U];
}

eel::util::U32 Rcc::APB2Frequency() {
  return AHBFrequency() >> apb_prescaler[(RccReg()->RCC_CFGR >> 13) & 0x7U];
}

}
