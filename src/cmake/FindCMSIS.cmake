set(CMSIS_COMMON_HEADERS
  arm_common_tables.h
  arm_const_structs.h
  arm_math.h
  core_cmFunc.h
  core_cmInstr.h
  core_cmSimd.h)

string(SUBSTRING ${STM32_FAMILY_LOWER} 0 1 STM32_FAMILY_SUBSTR)
set(CMSIS_STARTUP_SOURCE_PREFIX startup_stm32${STM32_FAMILY_SUBSTR}${STM32_DEV_NUM})

if(${STM32_FAMILY_UPPER} STREQUAL "F1")
  list(APPEND CMSIS_COMMON_HEADERS core_cm3.h)

  set(CMSIS_DEVICE_HEADERS stm32f1xx.h system_stm32f1xx.h)
  set(CMSIS_DEVICE_SOURCES system_stm32f1xx.c)
  # Now append the startup source
  if(${STM32_DEV_NUM} STREQUAL "103")
    if(${STM32_DEV_LETTERS_UPPER} STREQUAL "RB")
      set(CMSIS_STARTUP_SOURCE ${CMSIS_STARTUP_SOURCE_PREFIX}xb.s)
    endif()
  endif()
endif()

# include dirs
set(CMSIS_INCLUDE_DIRS ${CMAKE_CURRENT_LIST_DIR}/../platform/stm32/common/CMSIS/Include)
set(CMSIS_INCLUDE_DIRS ${CMSIS_INCLUDE_DIRS}
  ${CMAKE_CURRENT_LIST_DIR}/../platform/stm32/${STM32_FAMILY_LOWER}/CMSIS/Device/ST/STM32${STM32_FAMILY_UPPER}xx/Include)

# export all the sources
foreach(SRC ${CMSIS_DEVICE_SOURCES} ${CMSIS_STARTUP_SOURCE})
  find_file(FILE_${SRC} ${SRC}
    PATHS ${CMAKE_CURRENT_LIST_DIR}/../platform/stm32/${STM32_FAMILY_LOWER}/CMSIS/Device/ST/STM32${STM32_FAMILY_UPPER}xx
    PATH_SUFFIXES Source/Templates Source/Templates/gcc)
  list(APPEND CMSIS_SOURCES ${FILE_${SRC}})
endforeach ()

message(STATUS "Startup source: ${CMSIS_STARTUP_SOURCE}")

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(CMSIS DEFAULT_MSG CMSIS_INCLUDE_DIRS CMSIS_SOURCES)

