if(EEL_F1_SAMPLES)
    # add_subdirectory(boards/stm32f103rb-nucleo/blinky_stm32)
endif()
if(EEL_F4_SAMPLES)
  if(EEL_USE_OS_NONE)
    # stm32 hal projects
    #add_subdirectory(boards/stm32f446ze-nucleo/blinky_stm32)
    add_subdirectory(boards/stm32f446ze-nucleo/usart_stm32)

    # eel hal projects
    #add_subdirectory(boards/stm32f446ze-nucleo/blinky)
    add_subdirectory(boards/stm32f446ze-nucleo/usart)
  endif()
  if(EEL_USE_OS_CHIBIOS)
    add_subdirectory(boards/stm32f446ze-nucleo/blinky_chibios)
  endif()
endif()
