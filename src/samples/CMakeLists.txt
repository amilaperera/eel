# add windows samples
if (WIN32)
  add_subdirectory(win/util_samples)
  if (EnableRtos)
    add_subdirectory(win/free_rtos_samples)
  endif ()
endif ()

# add MCU target specific samples
if (${EelMcuName} MATCHES STM32F103RB)
  if (EnableRtos)
    add_subdirectory(boards/stm32f103rb-nucleo/rtos)
  else ()
    add_subdirectory(boards/stm32f103rb-nucleo/blinky)
    add_subdirectory(boards/stm32f103rb-nucleo/gpio_interrupt)
    add_subdirectory(boards/stm32f103rb-nucleo/usart)

    # Vendor specific samples if any for the particular target
    if (EnableStm32Samples)
      add_subdirectory(boards/stm32f103rb-nucleo/blinky_stm32)
      add_subdirectory(boards/stm32f103rb-nucleo/usart_stm32)
    endif ()
  endif ()
elseif (${EelMcuName} MATCHES STM32F446ZE)
  if (EnableRtos)
    add_subdirectory(boards/stm32f446ze-nucleo/rtos)
  else ()
    add_subdirectory(boards/stm32f446ze-nucleo/blinky)
    add_subdirectory(boards/stm32f446ze-nucleo/gpio_interrupt)
    add_subdirectory(boards/stm32f446ze-nucleo/usart)

    # Vendor specific samples if any for the particular target
    if (EnableStm32Samples)
      # stm32 hal projects
      add_subdirectory(boards/stm32f446ze-nucleo/blinky_stm32)
      add_subdirectory(boards/stm32f446ze-nucleo/gpio_interrupt_stm32)
      add_subdirectory(boards/stm32f446ze-nucleo/usart_stm32)
    endif ()
  endif ()
endif ()

