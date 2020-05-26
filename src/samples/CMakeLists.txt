# add windows samples
if (WIN32)
    add_subdirectory(win/util_samples)
    if (EnableRtos)
        add_subdirectory(win/free_rtos_samples)
    endif ()
endif ()
if (${EelMcuName} MATCHES STM32F103RB)
  # stm32 hal projects
  add_subdirectory(boards/stm32f103rb-nucleo/blinky_stm32)
  add_subdirectory(boards/stm32f103rb-nucleo/usart_stm32)
  # eel projects
  add_subdirectory(boards/stm32f103rb-nucleo/blinky)
  add_subdirectory(boards/stm32f103rb-nucleo/usart)
elseif (${EelMcuName} MATCHES STM32F446ZE)
  if(EnableRtos)
  else ()
      # stm32 hal projects
      add_subdirectory(boards/stm32f446ze-nucleo/blinky_stm32)
      add_subdirectory(boards/stm32f446ze-nucleo/gpio_interrupt_stm32)
      add_subdirectory(boards/stm32f446ze-nucleo/usart_stm32)

      # eel projects
      add_subdirectory(boards/stm32f446ze-nucleo/blinky)
      add_subdirectory(boards/stm32f446ze-nucleo/gpio_interrupt)
      add_subdirectory(boards/stm32f446ze-nucleo/usart)
  endif()
endif()

