
#pragma once
#include "platform/platform.hpp"
#include "utils/types.hpp"

namespace eel::hal::ll {
class gpio {
 protected:
  GPIO_InitTypeDef handle_;
  GPIO_TypeDef *gpiox_;
  eel::hal::pin_name name_;
 public:
  explicit gpio(eel::hal::pin_name pin);
  void init(eel::hal::pin_mode m, eel::hal::pin_speed s, eel::hal::pin_pud p);
  void set_af(eel::hal::af a);
  [[nodiscard]] eel::hal::pin_name name() const;
  void write(eel::hal::pin_level lvl);
  eel::hal::pin_level read();
  void toggle();
  void set_mode(eel::hal::pin_mode m);
  void set_speed(eel::hal::pin_speed s);
  void set_pud(eel::hal::pin_pud p);
};

[[nodiscard]] inline std::uint16_t stm_pin(eel::hal::pin_name pin) {
  return static_cast<std::uint16_t>(1U << static_cast<std::uint16_t>(eel::utils::to_integral(pin) % 16));
}
}

