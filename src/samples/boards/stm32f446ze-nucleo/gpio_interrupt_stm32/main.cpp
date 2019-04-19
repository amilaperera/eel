#include "stm32f4xx_hal.h"

bool keep_on{false};

extern "C" void EXTI15_10_IRQHandler() {
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
}

extern "C" void HAL_GPIO_EXTI_Callback(uint16_t pin) {
 if (pin == GPIO_PIN_13) {
   keep_on = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_SET;
 }
}

int main() {
  HAL_Init();

  __GPIOB_CLK_ENABLE();
  __GPIOC_CLK_ENABLE();

  GPIO_InitTypeDef GPIO_InitStructure;

  // LED configuration
  GPIO_InitStructure.Pin = GPIO_PIN_7;
  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
  GPIO_InitStructure.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

  // button configuration
  GPIO_InitStructure.Pin = GPIO_PIN_13;
  GPIO_InitStructure.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStructure.Speed = GPIO_SPEED_LOW;
  GPIO_InitStructure.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0x0, 0x0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

  for (;;) {
    if (keep_on) {
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
    } else {
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
    }
  }
}

