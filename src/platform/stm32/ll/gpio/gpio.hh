#pragma once

#include "platform/common_defs.hh"
#include "platform/memory_map.hh"
#include "util/types.hh"
#include "util/preprocessor.hh"

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

EEL_ALWAYS_INLINE void set_mode(util::U32 port_base, util::U32 pin, gpio::Mode mode) {
  eel::util::IO_U32 temp = gpio_reg(port_base)->MODER;
  temp &= ~(3U << (pin * 2U));
  temp |= (util::ToInt(mode) << (pin * 2U));
  gpio_reg(port_base)->MODER = temp;
}

EEL_ALWAYS_INLINE void set_pud(util::U32 port_base, util::U32 pin, gpio::PullUpDown pud) {
  auto temp = gpio_reg(port_base)->PUPDR;
  temp &= ~(3U << (pin * 2U));
  temp |= (util::ToInt(pud) << (pin * 2U));
  gpio_reg(port_base)->PUPDR = temp;
}

EEL_ALWAYS_INLINE void set_otype(util::U32 port_base, util::U32 pin, gpio::OutputType type) {
  auto temp = gpio_reg(port_base)->OTYPER;
  temp &= ~(1U << pin);
  temp |= (util::ToInt(type) << pin);
  gpio_reg(port_base)->OTYPER = temp;
}

EEL_ALWAYS_INLINE void set_ospeed(util::U32 port_base, util::U32 pin, gpio::OutputSpeed speed) {
  auto temp = gpio_reg(port_base)->OSPEEDR;
  temp &= ~(3U << (pin * 2U));
  temp |= (util::ToInt(speed) << (pin * 2U));
  gpio_reg(port_base)->OSPEEDR = temp;
}

EEL_ALWAYS_INLINE void set_af(util::U32 port_base, util::U32 pin, gpio::Af af) {
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
  explicit Gpio(gpio::Pin pin);
  void configure_output(gpio::PullUpDown pud, gpio::OutputType type, gpio::OutputSpeed speed);
  void configure_input(gpio::PullUpDown pud);
  void configure_af(gpio::Af af, gpio::PullUpDown pud,
                    gpio::OutputType type,
                    gpio::OutputSpeed speed);
  void write(bool status);
  bool read() const;
  void toggle();

 private:
  gpio::Port port_;
  util::U32 pin_;
  util::U32 port_base_;

  void configure(gpio::PullUpDown pud,
                 gpio::OutputType type,
                 gpio::OutputSpeed speed);
};

}
