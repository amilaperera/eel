#include "stm32f1xx_hal.h"

#define ld2_Pin GPIO_PIN_5
#define ld2_GPIO_Port GPIOA

int main() {
  HAL_Init();

  GPIO_InitTypeDef GPIO_InitStruct;

  __HAL_RCC_GPIOA_CLK_ENABLE();

  GPIO_InitStruct.Pin = ld2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(ld2_GPIO_Port, &GPIO_InitStruct);

  while (1) {
    HAL_GPIO_WritePin(ld2_GPIO_Port, ld2_Pin, GPIO_PIN_SET);
    HAL_Delay(1000);
    HAL_GPIO_WritePin(ld2_GPIO_Port, ld2_Pin, GPIO_PIN_RESET);
    HAL_Delay(1000);
  }
}

