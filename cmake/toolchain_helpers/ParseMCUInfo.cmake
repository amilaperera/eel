# Parse STM32 specific information
function(ParseStm32McuInfo)
  # Guard condition to recursion happens otherwise in toolchain file
  if (NOT STM32_FAMILY)
    message(STATUS "STM32 MCU detected - ${EelMcu}")

    # TODO(Amila): Is REGEX MATCH really needed before REGEX REPLACE ?
    # REGEX REPLACE alone would give the full input as the group match when
    # there's no match.

    # Parse stm32 family
    string(REGEX MATCH "^[sS][tT][mM]32[fFlL][0-47].*$" STM32_FAMILY ${EelMcu})
    if (STM32_FAMILY)
      string(REGEX REPLACE "^[sS][tT][mM]32([fFlL][0-47]).*$" "\\1" STM32_FAMILY ${EelMcu})
    else ()
      unset(STM32_FAMILY)
    endif ()

    # Parse device number
    # Eg: STM32F446ZETx - the device number is 446
    string(REGEX MATCH "^[sS][tT][mM]32[fFlL][0-47][0-9][0-9].*$" STM32_DEV_NUM ${EelMcu})
    if (STM32_DEV_NUM)
      string(REGEX REPLACE "^[sS][tT][mM]32[fFlL]([0-47][0-9][0-9]).*$" "\\1" STM32_DEV_NUM ${EelMcu})
    else ()
      unset(STM32_DEV_NUM)
    endif ()

    # Parse last 2 digits of device number
    # Eg: STM32F446ZETx - the device number is 46
    string(REGEX MATCH "^[sS][tT][mM]32[fFlL][0-47][0-9][0-9].*$" STM32_DEV_NUM_LAST_2_DIGITS ${EelMcu})
    if (STM32_DEV_NUM_LAST_2_DIGITS)
      string(REGEX REPLACE "^[sS][tT][mM]32[fFlL][0-47]([0-9][0-9]).*$" "\\1" STM32_DEV_NUM_LAST_2_DIGITS ${EelMcu})
    else ()
      unset(STM32_DEV_NUM_LAST_2_DIGITS)
    endif ()

    # Parse the device letters.
    # Eg: STM32F446ZETx - the device letters are ZE
    string(REGEX MATCH "^[sS][tT][mM]32[fFlL][0-47][0-9][0-9][A-Za-z][A-Za-z].*$" STM32_DEV_LETTERS ${EelMcu})
    if (STM32_DEV_LETTERS)
      string(REGEX REPLACE "^[sS][tT][mM]32[fFlL][0-47][0-9][0-9]([A-Za-z][A-Za-z]).*$" "\\1" STM32_DEV_LETTERS ${EelMcu})
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
      set(STM32_DEV_NUM_LAST_2_DIGITS ${STM32_DEV_NUM_LAST_2_DIGITS} CACHE INTERNAL "stm32 dev last 2 digits")

      # Set a device letters
      string(TOLOWER "${STM32_DEV_LETTERS}" STM32_DEV_LETTERS_LOWER)
      string(TOUPPER "${STM32_DEV_LETTERS}" STM32_DEV_LETTERS_UPPER)
      set(STM32_DEV_LETTERS ${STM32_DEV_LETTERS} CACHE INTERNAL "stm32 dev letters")
      set(STM32_DEV_LETTERS_LOWER ${STM32_DEV_LETTERS_LOWER} CACHE INTERNAL "stm32 dev letters lower")
      set(STM32_DEV_LETTERS_UPPER ${STM32_DEV_LETTERS_UPPER} CACHE INTERNAL "stm32 dev letters upper")
      message(STATUS "STM32 device number: ${STM32_DEV_NUM}")
      message(STATUS "STM32 device letters: ${STM32_DEV_LETTERS_UPPER}")

      set(EelMcuName STM32${STM32_FAMILY_UPPER}${STM32_DEV_NUM_LAST_2_DIGITS}${STM32_DEV_LETTERS_UPPER} CACHE INTERNAL "eel mcu name")
      set(EelMcuNameXX STM32${STM32_FAMILY_UPPER}${STM32_DEV_NUM_LAST_2_DIGITS}XX CACHE INTERNAL "eel mcu name xx")
      CreateConfigurationFile()
    endif ()
  endif ()
endfunction()

# MCU particular linker script paths
set(STM32F1_LINKER_SCRIPTS_PATH ${CMAKE_SOURCE_DIR}/src/ots/stm32_cube/f1/linker_scripts)
set(STM32F4_LINKER_SCRIPTS_PATH ${CMAKE_SOURCE_DIR}/src/ots/stm32_cube/f4/linker_scripts)

function(CreateConfigurationFile)
  configure_file(${CMAKE_SOURCE_DIR}/src/hal/config.hh.in config.hh)
  FILE(COPY ${CMAKE_BINARY_DIR}/config.hh DESTINATION ${CMAKE_SOURCE_DIR}/src/hal)
endfunction()

# Set linker script
function(SetLinkerScriptPath)
  if(NOT EEL_LINKER_SCRIPT)
    if("${EelMcu}" MATCHES "[sS][tT][mM]32[fF]103[rR][bB]")
      set(LINKER_SCRIPT "STM32F103RBTx_FLASH.ld")
    elseif("${EelMcu}" MATCHES "[sS][tT][mM]32[fF]446[zZ][eE]")
      set(LINKER_SCRIPT "STM32F446ZETx_FLASH.ld")
    endif()

    if(NOT LINKER_SCRIPT)
      message(FATAL_ERROR "Linker script couldn't be deduced by the MCU definitions.")
    else()
      if ("${STM32_FAMILY_UPPER}" STREQUAL "F1")
        set(EEL_LINKER_SCRIPT ${STM32F1_LINKER_SCRIPTS_PATH}/${LINKER_SCRIPT} CACHE INTERNAL "linker script")
      elseif ("${STM32_FAMILY_UPPER}" STREQUAL "F4")
        set(EEL_LINKER_SCRIPT ${STM32F4_LINKER_SCRIPTS_PATH}/${LINKER_SCRIPT} CACHE INTERNAL "linker script")
      endif ()
    endif()
  endif()
endfunction()

if (CMAKE_CROSSCOMPILING)
  # Parse MCU family
  if (NOT EelMcu)
    message(FATAL_ERROR "EelMcu must be defined.")
  else ()
    if (${EelMcu} MATCHES "^[sS][tT][mM]32.*")
      ParseStm32McuInfo()
      # Now parse CPU_FLAG
      if ("${STM32_FAMILY_UPPER}" STREQUAL "F1")
        set(CPU_FLAG "cortex-m3" CACHE INTERNAL "mcpu flag")
      else ()
        set(CPU_FLAG "cortex-m4" CACHE INTERNAL "mcpu flag")
      endif ()
    else ()
      message(FATAL_ERROR "Unsupported MCU family")
    endif ()
  endif ()

  # Set Linker script
  SetLinkerScriptPath()
endif ()

