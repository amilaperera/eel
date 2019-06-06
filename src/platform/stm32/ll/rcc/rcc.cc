#include "platform/stm32/ll/rcc/rcc.hh"
#include "util/bit_manip.hh"
#include "platform/mcu.hh"

namespace eel::hal::ll {

void Rcc::enable_port(Port port, bool status) {
  auto temp = rcc_reg()->RCC_AHB1ENR;
  if (status) {
    temp |= (1U << eel::util::ToInt(port));
  } else {
    temp &= ~(1U << eel::util::ToInt(port));
  }
  rcc_reg()->RCC_AHB1ENR = temp;
}

void Rcc::enable_usart(UsartPeripheral peripheral, bool status) {
  // usart2, usart3, uart4, uart5
  eel::util::IO_U32 temp{};
  switch (peripheral) {
    case UsartPeripheral::kUsart1:
      temp = rcc_reg()->RCC_APB2ENR;
      temp = eel::util::set_or_clear_bit(status, temp, 4);
      rcc_reg()->RCC_APB2ENR = temp;
      break;
    case UsartPeripheral::kUsart2:
      temp = rcc_reg()->RCC_APB1ENR;
      temp = eel::util::set_or_clear_bit(status, temp, 17);
      rcc_reg()->RCC_APB1ENR = temp;
      break;
    case UsartPeripheral::kUsart3:
      temp = rcc_reg()->RCC_APB1ENR;
      temp = eel::util::set_or_clear_bit(status, temp, 18);
      rcc_reg()->RCC_APB1ENR = temp;
      break;
    case UsartPeripheral::kUart4:
      temp = rcc_reg()->RCC_APB1ENR;
      temp = eel::util::set_or_clear_bit(status, temp, 19);
      rcc_reg()->RCC_APB1ENR = temp;
      break;
    case UsartPeripheral::kUart5:
      temp = rcc_reg()->RCC_APB1ENR;
      temp = eel::util::set_or_clear_bit(status, temp, 20);
      rcc_reg()->RCC_APB1ENR = temp;
      break;
    case UsartPeripheral::kUsart6:
      temp = rcc_reg()->RCC_APB2ENR;
      temp = eel::util::set_or_clear_bit(status, temp, 5);
      rcc_reg()->RCC_APB2ENR = temp;
      break;
  }
}

eel::util::U32 Rcc::ahb_prescalar() {
  // TODO: table is set for shifting
  //return ahb_prescaler[(RCCRegisterBlock()->RCC_CFGR >> 4) & 0xEU];
  return 0;
}

eel::util::U32 Rcc::apb1_prescalar() {
  // TODO: table is set for shifting
  //return apb_prescaler[(RCCRegisterBlock()->RCC_CFGR >> 10) & 0x7U];
  return 0;
}

eel::util::U32 Rcc::apb2_prescalar() {
  // TODO: table is set for shifting
  //return apb_prescaler[(RCCRegisterBlock()->RCC_CFGR >> 13) & 0x7U];
  return 0;
}

eel::util::U32 Rcc::ahb_frequency() {
  return SystemCoreClock >> ahb_prescaler[(rcc_reg()->RCC_CFGR >> 4) & 0xEU];
}

eel::util::U32 Rcc::apb1_frequency() {
  return ahb_frequency() >> apb_prescaler[(rcc_reg()->RCC_CFGR >> 10) & 0x7U];
}

eel::util::U32 Rcc::apb2_frequency() {
  return ahb_frequency() >> apb_prescaler[(rcc_reg()->RCC_CFGR >> 13) & 0x7U];
}

}
