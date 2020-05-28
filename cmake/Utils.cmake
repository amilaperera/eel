function(SetTargetProperties Target)
  if("${STM32_FAMILY_UPPER}" STREQUAL "F1")
    if ("${STM32_DEV_NUM}" STREQUAL "103")
      set(TARGET_DEFS "STM32F103")
    endif()

    if("${STM32_DEV_LETTERS_UPPER}" STREQUAL "RB")
      set(TARGET_DEFS "${TARGET_DEFS}xB")
    endif()
  elseif("${STM32_FAMILY_UPPER}" STREQUAL "F4")
    if ("${STM32_DEV_NUM}" STREQUAL "446")
      set(TARGET_DEFS "STM32F446")
    endif()

    if("${STM32_DEV_LETTERS_UPPER}" STREQUAL "ZE")
      set(TARGET_DEFS "${TARGET_DEFS}xx")
    endif()
  endif()

  if (TARGET_DEFS)
    target_compile_options(${Target} PUBLIC -D${TARGET_DEFS} -DUSE_HAL_DRIVER)
  endif()

  # Set linker properties
  if(EEL_USE_OS_CHIBIOS)
    # FIXME: Map file should be renamed according to project name
    # NOTE: --defsym=<symbol=expression>
    #         Creates a global symbol in the output file
    set_target_properties(${Target} PROPERTIES LINK_FLAGS "-mcpu=${CPU_FLAG} -mthumb -fomit-frame-pointer -falign-functions=16 -ffunction-sections -fdata-sections -fno-common -flto -nostartfiles -Wl,-Map=project.map,--cref,--no-warn-mismatch,--library-path=${ChibiOS_LINKER_PATH},--script=${ChibiOS_LINKER_SCRIPT},--gc-sections,--defsym=__process_stack_size__=0x400,--defsym=__main_stack_size__=0x400")
  else()
    set_target_properties(${Target} PROPERTIES LINK_FLAGS "${EEL_MCU_FLAGS} -specs=nano.specs -specs=nosys.specs -T${EEL_LINKER_SCRIPT} -lc -lm -Wl,-Map=${Target}.map,--cref -Wl,--gc-sections")
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

macro(ADD_SIZE_INFO BINARY)
  if (CMAKE_BIN_SIZE)
    add_custom_command(
            TARGET ${BINARY}.elf
            POST_BUILD
            COMMAND "${CMAKE_BIN_SIZE}" --format=berkeley ${BINARY}.elf)
  endif ()
endmacro()

