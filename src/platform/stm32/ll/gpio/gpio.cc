//
// Created by Amila Perera on 28/01/2019.
//
#include "platform/stm32/ll/gpio/gpio.hh"
#include "platform/stm32/ll/rcc/rcc.hh"
#include "platform/stm32/ll/exti/exti.hh"
#include "platform/stm32/ll/syscfg/syscfg.hh"
#include "util/types.hh"

namespace eel::hal::ll {

bool Gpio::IsInterruptSet(Pin pin) {
  return Exti::IsPending(static_cast<ExtiLine>(pin));
}

void Gpio::ClearInterrupt(Pin pin) {
  Exti::ClearPending(static_cast<ExtiLine>(pin));
}

Gpio::Gpio(Pin pin) : port_{static_cast<Port>(util::ToInt(pin) / 16)},
                                      pin_{util::ToInt(pin) % 16U} {
  switch (port_) {
    case Port::A:
      port_base_ = EEL_GPIOA_BASE;
      break;
    case Port::B:
      port_base_ = EEL_GPIOB_BASE;
      break;
    case Port::C:
      port_base_ = EEL_GPIOC_BASE;
      break;
    case Port::D:
      port_base_ = EEL_GPIOD_BASE;
      break;
    case Port::E:
      port_base_ = EEL_GPIOE_BASE;
      break;
    case Port::F:
      port_base_ = EEL_GPIOF_BASE;
      break;
    case Port::G:
      port_base_ = EEL_GPIOG_BASE;
      break;
    case Port::H:
      port_base_ = EEL_GPIOH_BASE;
      break;
  }

  ll::Rcc::EnablePort(port_, true);
}

void Gpio::ConfigureOutput(PullUpDown pud,
                           OutputType type,
                           OutputSpeed speed) {
  ll::SetMode(port_base_, pin_, eel::hal::PinMode::Output);
  Configure(pud, type, speed);
}

void Gpio::ConfigureInput(PullUpDown pud) {
  ll::SetMode(port_base_, pin_, PinMode::Input);
  SetPullUpDown(port_base_, pin_, pud);
}

void Gpio::ConfigureAf(AfMode af,
                       PullUpDown pud,
                       OutputType type,
                       OutputSpeed speed) {
  ll::SetMode(port_base_, pin_, eel::hal::PinMode::Alternate);
  SetAfMode(port_base_, pin_, af);
  Configure(pud, type, speed);
}

void Gpio::Write(bool status) {
  GpioReg(port_base_)->BSRR = status ? (1U << pin_) : (1U << (pin_ + 16U));
}

bool Gpio::Read() const {
  return (GpioReg(port_base_)->IDR & (1U << pin_)) != 0;
}

void Gpio::Toggle() {
  bool status = (GpioReg(port_base_)->ODR & (1U << pin_)) != 0;
  Write(!status);
}

void Gpio::ConfigureInterrupt(eel::hal::PinInterrupt interrupt_event) {
  ll::Exti::SetTrigger(static_cast<ExtiLine>(pin_), interrupt_event);
  ll::Exti::Enable(static_cast<ExtiLine>(pin_));
  ll::SysCfg::SetExtiConfiguration(static_cast<ExtiLine>(pin_), port_);
}

void Gpio::EnableInterrupt(eel::util::U32 priority) {
  NVIC_SetPriority(GetIRQn(), priority);
  NVIC_EnableIRQ(GetIRQn());
}

void Gpio::DisableInterrupt() {
  NVIC_DisableIRQ(GetIRQn());
}

// private implementation
void Gpio::Configure(PullUpDown pud,
                     OutputType type,
                     OutputSpeed speed) {
  SetPullUpDown(port_base_, pin_, pud);
  SetOutputType(port_base_, pin_, type);
  SetOutputSpeed(port_base_, pin_, speed);
}

IRQn_Type Gpio::GetIRQn() {
  IRQn_Type irqn{EXTI15_10_IRQn};
  switch (pin_) {
    case 0:
      irqn = EXTI0_IRQn;
      break;
    case 1:
      irqn = EXTI1_IRQn;
      break;
    case 2:
      irqn = EXTI2_IRQn;
      break;
    case 3:
      irqn = EXTI3_IRQn;
      break;
    case 4:
      irqn = EXTI4_IRQn;
      break;
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
      irqn = EXTI9_5_IRQn;
      break;
    default:
      break;
  }
  return irqn;
}

}
