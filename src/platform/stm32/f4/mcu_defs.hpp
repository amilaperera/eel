//
// Created by amila.perera on 17/05/2020.
//

#pragma once
#include <cinttypes>
#include "platform/stm32/stm32_hal.hpp"
#include "utils/types.hpp"

namespace eel::hal {
enum class pin_level : bool {low = false, high = true};

enum class af : uint8_t {
  af0, af1, af2, af3, af4, af5, af6, af7, af8, af9, af10, af11, af12, af13, af14, af15
};

enum class interrupt_mode : uint8_t {
  rising, falling, both
};

#if defined(HAL_GPIO_MODULE_ENABLED)
enum class pin_name {
  A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15,
  B0, B1, B2, B3, B4, B5, B6, B7, B8, B9, B10, B11, B12, B13, B14, B15,
  C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14, C15,
  D0, D1, D2, D3, D4, D5, D6, D7, D8, D9, D10, D11, D12, D13, D14, D15,
  E0, E1, E2, E3, E4, E5, E6, E7, E8, E9, E10, E11, E12, E13, E14, E15,
  F0, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13, F14, F15,
  G0, G1, G2, G3, G4, G5, G6, G7, G8, G9, G10, G11, G12, G13, G14, G15,
};
inline GPIO_TypeDef* get_gpiox(int port_value) {
  switch (port_value) {
    case 0: return GPIOA;
    case 1: return GPIOB;
    case 2: return GPIOC;
    case 3: return GPIOD;
    case 4: return GPIOE;
    case 5: return GPIOF;
    case 6: return GPIOG;
    default: break;
  }
  return nullptr;
}
inline void enable_clock(int port_value) {
  switch (port_value) {
    case 0: __HAL_RCC_GPIOA_CLK_ENABLE(); break;
    case 1: __HAL_RCC_GPIOB_CLK_ENABLE(); break;
    case 2: __HAL_RCC_GPIOC_CLK_ENABLE(); break;
    case 3: __HAL_RCC_GPIOD_CLK_ENABLE(); break;
    case 4: __HAL_RCC_GPIOE_CLK_ENABLE(); break;
    case 5: __HAL_RCC_GPIOF_CLK_ENABLE(); break;
    case 6: __HAL_RCC_GPIOG_CLK_ENABLE(); break;
    default: break;
  }
}

enum class pin_mode : std::uint32_t {
  input = GPIO_MODE_INPUT,
  output_pp = GPIO_MODE_OUTPUT_PP,
  output_od = GPIO_MODE_OUTPUT_OD,
  af_pp = GPIO_MODE_AF_PP,
  af_od = GPIO_MODE_AF_OD,
  analog = GPIO_MODE_ANALOG,
  it_rising = GPIO_MODE_IT_RISING,
  it_falling = GPIO_MODE_IT_FALLING,
  it_rising_falling = GPIO_MODE_IT_RISING_FALLING,
  evt_rising = GPIO_MODE_EVT_RISING,
  evt_falling = GPIO_MODE_EVT_FALLING,
  evt_rising_falling = GPIO_MODE_EVT_RISING_FALLING,
};

enum class pin_speed : std::uint32_t {
  low =  GPIO_SPEED_LOW,
  medium =  GPIO_SPEED_MEDIUM,
  fast =   GPIO_SPEED_FAST,
  high =  GPIO_SPEED_HIGH,
};

enum class pin_pud : std::uint32_t  {
  none = GPIO_NOPULL,
  up = GPIO_PULLUP,
  down = GPIO_PULLDOWN,
};

inline void set_interrupt(eel::hal::pin_name name) {
  IRQn_Type irqn_type(EXTI15_10_IRQn);
  switch (eel::utils::to_integral(name) % 16) {
    case 0: irqn_type = EXTI0_IRQn; break;
    case 1: irqn_type = EXTI1_IRQn; break;
    case 2: irqn_type = EXTI2_IRQn; break;
    case 3: irqn_type = EXTI3_IRQn; break;
    case 4: irqn_type = EXTI4_IRQn; break;
    case 5: case 6: case 7: case 8: case 9: irqn_type = EXTI9_5_IRQn; break;
    default: break;
  }
  HAL_NVIC_SetPriority(irqn_type, 0x0, 0x0);
  HAL_NVIC_EnableIRQ(irqn_type);
}

#endif

#if defined(HAL_UART_MODULE_ENABLED)

struct uart_af {
  eel::hal::pin_name tx;
  eel::hal::pin_name rx;
  USART_TypeDef* uartx;
  eel::hal::af af;
};

inline static const uart_af uart_af_map[] = {
    {pin_name::B10, pin_name::B11, USART3, af::af7},
    {pin_name::C10, pin_name::C11, USART3, af::af7},
    {pin_name::D8, pin_name::D9, USART3, af::af7}
};

enum class parity : std::uint32_t {
  none = UART_PARITY_NONE,
  even = UART_PARITY_EVEN,
  odd = UART_PARITY_ODD
};

enum class stop_bits : std::uint32_t {
  one = UART_STOPBITS_1,
  two = UART_STOPBITS_2,
};
enum class char_size : std::uint32_t {
 eight = UART_WORDLENGTH_8B,
 nine = UART_WORDLENGTH_9B
};

enum class flow_control : std::uint32_t {
  none = UART_HWCONTROL_NONE,
  rts = UART_HWCONTROL_RTS,
  cts = UART_HWCONTROL_CTS,
  rts_cts = UART_HWCONTROL_RTS_CTS
};
#endif

}
