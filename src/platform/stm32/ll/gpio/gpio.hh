#pragma once

#include "platform/common_defs.hh"
#include "platform/memory_map.hh"
#include "util/types.hh"
#include "util/preprocessor.hh"
#include "platform/mcu.hh"

namespace eel::hal::ll {

struct GpioRCB {
  eel::util::IO_U32 MODER;
  eel::util::IO_U32 OTYPER;
  eel::util::IO_U32 OSPEEDR;
  eel::util::IO_U32 PUPDR;
  eel::util::IO_U32 IDR;
  eel::util::IO_U32 ODR;
  eel::util::IO_U32 BSRR;
  eel::util::IO_U32 LCKR;
  eel::util::IO_U32 AFR[2]; // AFLR & AFHR - collectively called AFR
};

EEL_ALWAYS_INLINE auto GpioReg(eel::util::U32 port) {
  return reinterpret_cast<GpioRCB*>(port);
}

EEL_ALWAYS_INLINE void SetMode(util::U32 port_base, util::U32 pin, PinMode mode) {
  eel::util::IO_U32 temp = GpioReg(port_base)->MODER;
  temp &= ~(3U << (pin * 2U));
  temp |= (util::ToInt(mode) << (pin * 2U));
  GpioReg(port_base)->MODER = temp;
}

EEL_ALWAYS_INLINE void SetPullUpDown(util::U32 port_base, util::U32 pin, PullUpDown pud) {
  auto temp = GpioReg(port_base)->PUPDR;
  temp &= ~(3U << (pin * 2U));
  temp |= (util::ToInt(pud) << (pin * 2U));
  GpioReg(port_base)->PUPDR = temp;
}

EEL_ALWAYS_INLINE void SetOutputType(util::U32 port_base, util::U32 pin, OutputType type) {
  auto temp = GpioReg(port_base)->OTYPER;
  temp &= ~(1U << pin);
  temp |= (util::ToInt(type) << pin);
  GpioReg(port_base)->OTYPER = temp;
}

EEL_ALWAYS_INLINE void SetOutputSpeed(util::U32 port_base, util::U32 pin, OutputSpeed speed) {
  auto temp = GpioReg(port_base)->OSPEEDR;
  temp &= ~(3U << (pin * 2U));
  temp |= (util::ToInt(speed) << (pin * 2U));
  GpioReg(port_base)->OSPEEDR = temp;
}

EEL_ALWAYS_INLINE void SetAfMode(util::U32 port_base, util::U32 pin, AfMode af) {
  auto pin_position{pin}, afr_idx{0UL};
  if (pin >= 8) {
    // We should write to AFHR, not AFLR. Therefore increment idx
    afr_idx = 1;
    pin_position = pin - 8;
  }
  auto temp = GpioReg(port_base)->AFR[afr_idx];
  temp &= ~(0xFU << (pin_position * 4U));
  temp |= (util::ToInt(af) << (pin_position * 4U));
  GpioReg(port_base)->AFR[afr_idx] = temp;
}

class Gpio {
 public:
  static bool IsInterruptSet(Pin pin);
  static void ClearInterrupt(Pin pin);

  explicit Gpio(Pin pin);
  void ConfigureOutput(PullUpDown pud, OutputType type, OutputSpeed speed);
  void ConfigureInput(PullUpDown pud);
  void ConfigureAf(AfMode af, PullUpDown pud,
                   OutputType type,
                   OutputSpeed speed);
  void Write(bool status);
  bool Read() const;
  void Toggle();
  void ConfigureInterrupt(eel::hal::PinInterrupt interrupt_event);
  void EnableInterrupt(eel::util::U32 priority);
  void DisableInterrupt();

 private:
  Port port_;
  util::U32 pin_;
  util::U32 port_base_;

  void Configure(PullUpDown pud,
                 OutputType type,
                 OutputSpeed speed);

  IRQn_Type GetIRQn();
};

}
