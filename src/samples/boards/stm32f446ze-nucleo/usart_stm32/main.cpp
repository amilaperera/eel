#include <cstring>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_conf.h"

int main() {
  HAL_Init();

  // TX RX configuration
  // On board -
  // USART3
  // Tx - PD8
  // Rx - PD9
  __GPIOD_CLK_ENABLE();
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.Pin = GPIO_PIN_8 | GPIO_PIN_9;
  GPIO_InitStructure.Mode = GPIO_MODE_AF_PP; // OD ? for RX
  GPIO_InitStructure.Alternate = GPIO_AF7_USART3;
  GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_MEDIUM;
  GPIO_InitStructure.Pull = GPIO_PULLUP; // Not sure ??
  HAL_GPIO_Init(GPIOD, &GPIO_InitStructure);

  // usart configuration
  __HAL_RCC_USART3_CLK_ENABLE();
  UART_HandleTypeDef usart;
  usart.Instance = USART3;
  usart.Init.BaudRate = 115200;
  usart.Init.Parity = UART_PARITY_NONE;
  usart.Init.WordLength = UART_WORDLENGTH_8B;
  usart.Init.StopBits = UART_STOPBITS_1;
  usart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  usart.Init.Mode = UART_MODE_TX_RX;
  usart.Init.OverSampling = UART_OVERSAMPLING_16;

  if (HAL_UART_Init(&usart) != HAL_OK) {
    asm("bkpt 255");
  }
  const char *p = "\r\nWelcome !!!\r\n";
  HAL_UART_Transmit(&usart, (uint8_t *)(p), std::strlen(p), HAL_MAX_DELAY);
  for (;;) {
    uint8_t ch;
    HAL_UART_Receive(&usart, &ch, 1, HAL_MAX_DELAY);
    HAL_UART_Transmit(&usart, &ch, 1, HAL_MAX_DELAY);
  }
}

