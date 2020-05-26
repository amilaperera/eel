//
// Created by amila.perera on 26/05/2020.
//

#include "platform/stm32/gpio_interrupt.hpp"

namespace eel::hal::ll {
  void gpio_interrupt::init(eel::hal::pin_speed s, eel::hal::pin_pud p) {
    eel::hal::pin_mode m{eel::hal::pin_mode::it_rising};
    switch (mode_) {
      case eel::hal::interrupt_mode::falling:
        m = eel::hal::pin_mode::it_falling;
        break;
      case eel::hal::interrupt_mode::both:
        m = eel::hal::pin_mode::it_rising_falling;
        break;
      case eel::hal::interrupt_mode::rising:
        break;
    }
    gpio::init(m, s, p);
    set_interrupt(name_);
  }
}

extern "C" void EXTI15_10_IRQHandler() {
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_10);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_11);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_12);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_14);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_15);
}


