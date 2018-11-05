#include "stm32f4xx_hal.h"
#include "ch.h"

int main() {
  HAL_Init();
  chSysInit();

  __GPIOB_CLK_ENABLE();
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.Pin = GPIO_PIN_7;

  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
  GPIO_InitStructure.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

  for (;;)
  {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
    HAL_Delay(500);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
    HAL_Delay(500);
  }
}

