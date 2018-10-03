function(SetTargetProperties Target)
  if("${STM32_FAMILY_UPPER}" STREQUAL "F1")
    if ("${STM32_DEV_NUM}" STREQUAL "103")
      set(TARGET_DEFS "STM32F103")
    endif()

    if("${STM32_DEV_LETTERS_UPPER}" STREQUAL "RB")
      set(TARGET_DEFS "${TARGET_DEFS}xB")
    endif()
  endif()

  if (TARGET_DEFS)
    message(STATUS "Target Definitions: ${TARGET_DEFS}")
    target_compile_options(${Target} PUBLIC -D${TARGET_DEFS} -DUSE_HAL_DRIVER)
  endif()
endfunction()

macro(ADD_POST_BUILD_COPY BINARY)
  set(HEX_FILE ${BINARY}.hex)
  set(BIN_FILE ${BINARY}.bin)
  add_custom_command(TARGET ${BINARY}.elf
    POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -Oihex ${BINARY}.elf ${HEX_FILE}
    COMMAND ${CMAKE_OBJCOPY} -Obinary ${BINARY}.elf ${BIN_FILE}
    COMMENT "\nBuilding ${HEX_FILE} \nBuilding ${BIN_FILE}\n")
  unset(HEX_FILE)
  unset(BIN_FILE)
endmacro()

macro(SET_LINKER_PROPERTIES)
  message(STATUS "Linker script: ${EEL_LINKER_SCRIPT}")
  set(CMAKE_EXE_LINKER_FLAGS "-mcpu=cortex-m3 -mthumb -specs=nano.specs -T${EEL_LINKER_SCRIPT} -lc -lm -lnosys -Wl,--gc-sections" CACHE INTERNAL "executable linker flags")
endmacro()

macro(ADD_OPENOCD_TARGETS BINARY)
  if (OPENOCD_EXECUTABLE)
    set(OPENOCD_TARGET_CONFIG "target/stm32${STM32_FAMILY_LOWER}x.cfg")

    # Flash the program to target & reset
    add_custom_target(${BINARY}_flash
      DEPENDS ${BINARY}.elf
      COMMAND "${OPENOCD_EXECUTABLE}" -f interface/stlink-v2-1.cfg -f ${OPENOCD_TARGET_CONFIG}
      -c "program ${BINARY}.elf verify reset exit")
  endif ()
  unset(OPENOCD_TARGET_CONFIG)
endmacro()
