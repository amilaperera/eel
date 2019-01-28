#include "hal/critical_section.hh"
#include "hal/gpio.hh"

int main() {
  HAL_Init();

  __GPIOB_CLK_ENABLE();
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.Pin = GPIO_PIN_7;

  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
  GPIO_InitStructure.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

  eel::hal::gpio::Gpio pin(eel::hal::gpio::Pin::A0);
  pin.SetDirection(eel::hal::gpio::Direction::kOutput);

  for (;;)
  {
    eel::hal::core::EnterCriticalSection();
    eel::hal::core::EnterCriticalSection();
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
    eel::hal::core::ExitCriticalSection();
    eel::hal::core::ExitCriticalSection();
    HAL_Delay(500);
    eel::hal::core::EnterCriticalSection();
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
    eel::hal::core::ExitCriticalSection();
    HAL_Delay(500);
  }
}

