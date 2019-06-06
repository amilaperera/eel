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

EEL_ALWAYS_INLINE auto gpio_reg(eel::util::U32 port) {
  return reinterpret_cast<GpioRCB*>(port);
}

EEL_ALWAYS_INLINE void set_mode(util::U32 port_base, util::U32 pin, PinMode mode) {
  eel::util::IO_U32 temp = gpio_reg(port_base)->MODER;
  temp &= ~(3U << (pin * 2U));
  temp |= (util::ToInt(mode) << (pin * 2U));
  gpio_reg(port_base)->MODER = temp;
}

EEL_ALWAYS_INLINE void set_pud(util::U32 port_base, util::U32 pin, PullUpDown pud) {
  auto temp = gpio_reg(port_base)->PUPDR;
  temp &= ~(3U << (pin * 2U));
  temp |= (util::ToInt(pud) << (pin * 2U));
  gpio_reg(port_base)->PUPDR = temp;
}

EEL_ALWAYS_INLINE void set_otype(util::U32 port_base, util::U32 pin, OutputType type) {
  auto temp = gpio_reg(port_base)->OTYPER;
  temp &= ~(1U << pin);
  temp |= (util::ToInt(type) << pin);
  gpio_reg(port_base)->OTYPER = temp;
}

EEL_ALWAYS_INLINE void set_ospeed(util::U32 port_base, util::U32 pin, OutputSpeed speed) {
  auto temp = gpio_reg(port_base)->OSPEEDR;
  temp &= ~(3U << (pin * 2U));
  temp |= (util::ToInt(speed) << (pin * 2U));
  gpio_reg(port_base)->OSPEEDR = temp;
}

EEL_ALWAYS_INLINE void set_af(util::U32 port_base, util::U32 pin, AfMode af) {
  auto pin_position{pin}, afr_idx{0UL};
  if (pin >= 8) {
    // We should write to AFHR, not AFLR. Therefore increment idx
    afr_idx = 1;
    pin_position = pin - 8;
  }
  auto temp = gpio_reg(port_base)->AFR[afr_idx];
  temp &= ~(0xFU << (pin_position * 4U));
  temp |= (util::ToInt(af) << (pin_position * 4U));
  gpio_reg(port_base)->AFR[afr_idx] = temp;
}

class Gpio {
 public:
  explicit Gpio(Pin pin);
  void configure_output(PullUpDown pud, OutputType type, OutputSpeed speed);
  void configure_input(PullUpDown pud);
  void configure_af(AfMode af, PullUpDown pud,
                    OutputType type,
                    OutputSpeed speed);
  void write(bool status);
  bool read() const;
  void toggle();
  void enable_interrupt(eel::util::U32 priority);
  void disable_interrupt();

 private:
  Port port_;
  util::U32 pin_;
  util::U32 port_base_;

  void configure(PullUpDown pud,
                 OutputType type,
                 OutputSpeed speed);

  IRQn_Type get_irqn();
};

}
