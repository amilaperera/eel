# Parse MCU family
if (CMAKE_CROSSCOMPILING)
  if (NOT EEL_MCU)
    message(FATAL_ERROR "EEL_MCU must be defined.")
  else ()
    if (${EEL_MCU} MATCHES "^[sS][tT][mM]32.*")
      ParseStm32McuInfo()
      # Now parse CPU_FLAG
      if ("${STM32_FAMILY_UPPER}" STREQUAL "F1")
        set(CPU_FLAG "cortex-m3")
      else ()
        set(CPU_FLAG "cortex-m4")
      endif ()
    else ()
      message(FATAL_ERROR "Unsupported MCU family")
    endif ()
  endif ()
endif ()

# Parse STM32 specific information
function(ParseStm32McuInfo)
  # Guard condition to recursion happens otherwise in toolchain file
  if (NOT STM32_FAMILY)
    message(STATUS "STM32 MCU detected - ${EEL_MCU}")

    # TODO(Amila): Is REGEX MATCH really needed before REGEX REPLACE ?
    # REGEX REPLACE alone would give the full input as the group match when
    # there's no match.

    # Parse stm32 family
    string(REGEX MATCH "^[sS][tT][mM]32[fFlL][0-47].*$" STM32_FAMILY ${EEL_MCU})
    if (STM32_FAMILY)
      string(REGEX REPLACE "^[sS][tT][mM]32([fFlL][0-47]).*$" "\\1" STM32_FAMILY ${EEL_MCU})
    else ()
      unset(STM32_FAMILY)
    endif ()

    # Parse device number
    # Eg: STM32F446ZETx - the device number is 446
    string(REGEX MATCH "^[sS][tT][mM]32[fFlL][0-47][0-9][0-9].*$" STM32_DEV_NUM ${EEL_MCU})
    if (STM32_DEV_NUM)
      string(REGEX REPLACE "^[sS][tT][mM]32[fFlL]([0-47][0-9][0-9]).*$" "\\1" STM32_DEV_NUM ${EEL_MCU})
    else ()
      unset(STM32_DEV_NUM)
    endif ()

    # Parse the device letters.
    # Eg: STM32F446ZETx - the device letters are ZE
    string(REGEX MATCH "^[sS][tT][mM]32[fFlL][0-47][0-9][0-9][A-Za-z][A-Za-z].*$" STM32_DEV_LETTERS ${EEL_MCU})
    if (STM32_DEV_LETTERS)
      string(REGEX REPLACE "^[sS][tT][mM]32[fFlL][0-47][0-9][0-9]([A-Za-z][A-Za-z]).*$" "\\1" STM32_DEV_LETTERS ${EEL_MCU})
    else ()
      unset(STM32_DEV_LETTERS)
    endif ()

    if (NOT STM32_FAMILY)
      message(FATAL_ERROR "Unsupported STM32 family. Supported families are: F0, F1, F2, F3, F4, F7, L1, L4.")
    else ()
      # Set a couple of variables in the global scope
      string(TOLOWER "${STM32_FAMILY}" STM32_FAMILY_LOWER)
      string(TOUPPER "${STM32_FAMILY}" STM32_FAMILY_UPPER)
      set(STM32_FAMILY ${STM32_FAMILY} CACHE INTERNAL "stm32 family")
      set(STM32_FAMILY_LOWER ${STM32_FAMILY_LOWER} CACHE INTERNAL "stm32 family lower")
      set(STM32_FAMILY_UPPER ${STM32_FAMILY_UPPER} CACHE INTERNAL "stm32 family upper")
      message(STATUS "STM32 device family: ${STM32_FAMILY_UPPER}")
    endif ()

    if (NOT STM32_DEV_NUM OR NOT STM32_DEV_LETTERS)
      message(FATAL_ERROR "Unsupported ${STM32_FAMILY_UPPER} device.")
    else ()
      set(STM32_DEV_NUM ${STM32_DEV_NUM} CACHE INTERNAL "stm32 dev num")

      # Set a device letters
      string(TOLOWER "${STM32_DEV_LETTERS}" STM32_DEV_LETTERS_LOWER)
      string(TOUPPER "${STM32_DEV_LETTERS}" STM32_DEV_LETTERS_UPPER)
      set(STM32_DEV_LETTERS ${STM32_DEV_LETTERS} CACHE INTERNAL "stm32 dev letters")
      set(STM32_DEV_LETTERS_LOWER ${STM32_DEV_LETTERS_LOWER} CACHE INTERNAL "stm32 dev letters lower")
      set(STM32_DEV_LETTERS_UPPER ${STM32_DEV_LETTERS_UPPER} CACHE INTERNAL "stm32 dev letters upper")
      message(STATUS "STM32 device number: ${STM32_DEV_NUM}")
      message(STATUS "STM32 device letters: ${STM32_DEV_LETTERS_UPPER}")
    endif ()
  endif ()
endfunction()
