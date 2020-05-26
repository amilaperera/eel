
#pragma once
#include "platform/stm32/gpio.hpp"
#include "utils/types.hpp"


#define GPIO_IRQ_BEGIN(PIN_NAME) extern "C" void HAL_GPIO_EXTI_Callback(uint16_t pin) { \
if (pin == (static_cast<std::uint16_t>(1) << static_cast<std::uint16_t>(eel::utils::to_integral(PIN_NAME) % 16))) {

#define GPIO_IRQ_END  }}

namespace eel::hal::ll {
class gpio_interrupt : public gpio {
 public:
  gpio_interrupt(eel::hal::pin_name pin, interrupt_mode mode) : gpio(pin), mode_(mode) {}
  void init(eel::hal::pin_speed s, eel::hal::pin_pud p);
 private:
  interrupt_mode mode_;
};
}
