#include "stm32f4xx_hal.h"
#include "ch.h"

#if !defined(SYSTEM_CLOCK)
#define SYSTEM_CLOCK 8000000U
#endif

/*
 * @brief   System Timer handler.
 */
#ifdef __cplusplus
extern "C" {
#endif
CH_IRQ_HANDLER(SysTick_Handler) {

  CH_IRQ_PROLOGUE();

  chSysLockFromISR();
  chSysTimerHandlerI();
  chSysUnlockFromISR();

  CH_IRQ_EPILOGUE();
}
#ifdef __cplusplus
}
#endif

GPIO_InitTypeDef GPIO_InitStructure;

static THD_WORKING_AREA(waThread1, 512);
static THD_FUNCTION(Thread1, arg) {
  (void)arg;
  chRegSetThreadName("blinker");
  while (true) {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
    chThdSleepMilliseconds(100);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
    chThdSleepMilliseconds(100);
  }
}

int main() {
  HAL_Init();

  /*
   * Hardware initialization, in this simple demo just the systick timer is
   * initialized.
   */
  // SysTick->LOAD = SYSTEM_CLOCK / CH_CFG_ST_FREQUENCY - (systime_t)1;
  // SysTick->VAL = (uint32_t)0;
  // SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk |
                  // SysTick_CTRL_TICKINT_Msk;

  chSysInit();

  __GPIOB_CLK_ENABLE();

  GPIO_InitStructure.Pin = GPIO_PIN_7;

  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
  GPIO_InitStructure.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);

  /*
   * Normal main() thread activity, in this demo it does nothing except
   * sleeping in a loop and check the button state.
   */
  while (true) {
    chThdSleepMilliseconds(10);
  }
}

