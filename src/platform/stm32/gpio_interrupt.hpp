
#pragma once
#include "platform/stm32/gpio.hpp"
#include "utils/types.hpp"

#define GPIO_IRQ_BEGIN(PIN_NAME) extern "C" void HAL_GPIO_EXTI_Callback(uint16_t pin) { \
if (pin == eel::hal::ll::stm_pin(PIN_NAME)) {

#define GPIO_IRQ_END  }}

namespace eel::hal::ll {
class gpio_interrupt : public gpio {
 public:
  gpio_interrupt(eel::hal::pin_name pin, interrupt_mode mode) : gpio(pin), mode_(mode) {}
  void init(eel::hal::pin_speed s, eel::hal::pin_pud p);
  void set_priority(std::uint32_t prio);
 private:
  interrupt_mode mode_;
};
}
