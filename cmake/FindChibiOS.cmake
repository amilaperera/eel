# Select ChibiOS components.
# Currently HAL & RT
# TODO: NIL
set(CHIBIOS_ROOT_PATH ${CMAKE_SOURCE_DIR}/src/ots/ChibiOS_18.2.1)

if(NOT ChibiOS_FIND_COMPONENTS)
  set(ChibiOS_FIND_COMPONENTS HAL RT)
  message(STATUS "No ChibiOS components selected, using defaults: ${ChibiOS_FIND_COMPONENTS}")
else()
  message(STATUS "ChibiOS components: ${ChibiOS_FIND_COMPONENTS}")
endif()

LIST(FIND ChibiOS_FIND_COMPONENTS "HAL" CHIBIOS_HAL_ENABLED)
LIST(FIND ChibiOS_FIND_COMPONENTS "RT" CHIBIOS_RT_ENABLED)

# Find hal configuration file
if(NOT ${CHIBIOS_HAL_ENABLED} LESS 0)
  # HAL found
  if(NOT CHIBIOS_HAL_CONF_FILE)
    message(STATUS "CHIBIOS_HAL_CONF_FILE not specified. Trying to find it....")
    file(GLOB_RECURSE CHIBIOS_HAL_CONF_FILE "halconf.h")
    if(CHIBIOS_HAL_CONF_FILE STREQUAL "")
      message(FATAL_ERROR "Cannot find halconf.h, please specify it using CHIBIOS_HAL_CONF_FILE variable")
    else()
      message(STATUS "Found halconf.h: ${CHIBIOS_HAL_CONF_FILE}")
    endif()
  endif()

  # Detect enabled HAL components using hal configuration file
  file(STRINGS ${CHIBIOS_HAL_CONF_FILE} HALCONF_LINES REGEX "#define HAL_USE_([a-zA-Z_0-9]+) +TRUE")
  foreach(LINE ${HALCONF_LINES})
    string(REGEX REPLACE "#define HAL_USE_([a-zA-Z_0-9]+) +TRUE" "\\1" COMP ${LINE})
    list(APPEND CHIBIOS_HAL_COMPONENTS ${COMP})
  endforeach()

  message(STATUS "Detected ChibiOS HAL components:")
  foreach(COMP ${CHIBIOS_HAL_COMPONENTS})
    message(STATUS "\t${COMP}")
  endforeach()
endif()

# Find rt configuration file
if(NOT ${CHIBIOS_RT_ENABLED} LESS 0)
  if(NOT CHIBIOS_RT_CONF_FILE)
    message(STATUS "CHIBIOS_RT_CONF_FILE not specified. Trying to find it....")
    file(GLOB_RECURSE CHIBIOS_RT_CONF_FILE "chconf.h")
    if(CHIBIOS_RT_CONF_FILE STREQUAL "")
      message(FATAL_ERROR "Cannot find chconf.h, please specify it using CHIBIOS_RT_CONF_FILE variable")
    else()
      message(STATUS "Found chconf.h: ${CHIBIOS_RT_CONF_FILE}")
    endif()
  endif()

  # Detect enabled RT components using rt configuration file
  file(STRINGS ${CHIBIOS_RT_CONF_FILE} RT_CONF_LINES REGEX "#define CH_CFG_USE_([a-zA-Z_0-9]+) +TRUE")
  foreach(LINE ${RT_CONF_LINES})
    string(REGEX REPLACE "#define CH_CFG_USE_([a-zA-Z_0-9]+) +TRUE" "\\1" COMP ${LINE})
    list(APPEND CHIBIOS_RT_COMPONENTS ${COMP})
  endforeach()

  message(STATUS "Detected ChibiOS RT components:")
  foreach(COMP ${CHIBIOS_RT_COMPONENTS})
    message(STATUS "\t${COMP}")
  endforeach()
endif()


if(NOT ${CHIBIOS_HAL_ENABLED} LESS 0)
  # HAL found
endif()

if(NOT ${CHIBIOS_RT_ENABLED} LESS 0)
  # RT found
  include(${CMAKE_CURRENT_LIST_DIR}/ChibiOS/ChibiOS_RTOS.cmake)
endif()

# populate export variables with HAL sources
# TODO

# populate export variables with RT sources
foreach(SRC ${CHIBIOS_SOURCES_RT})
  find_file(FILE_${SRC}
    NAMES ${SRC}
    PATHS ${CHIBIOS_ROOT_PATH})
  list(APPEND ChibiOS_SOURCES ${FILE_${SRC}})
endforeach()

foreach(INCLUDE_DIR ${CHIBIOS_INCLUDE_DIRS})
  LIST(APPEND ChibiOS_INCLUDE_DIRS ${CHIBIOS_ROOT_PATH}/${INCLUDE_DIR})
endforeach()

# Set linker path and linker script
set(ChibiOS_LINKER_PATH ${CHIBIOS_ROOT_PATH}/os/common/startup/ARMCMx/compilers/GCC/ld CACHE INTERNAL "linker script path")
# Set ChibiOS linker script
if("${EEL_MCU}" MATCHES "[sS][tT][mM]32[fF]103[rR][bB]")
  # TODO: set
elseif("${EEL_MCU}" MATCHES "[sS][tT][mM]32[fF]446[zZ][eE]")
  set(ChibiOS_LINKER_SCRIPT ${ChibiOS_LINKER_PATH}/STM32F446xE.ld CACHE INTERNAL "linker script")
endif()


include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ChibiOS DEFAULT_MSG ChibiOS_INCLUDE_DIRS ChibiOS_SOURCES
  ChibiOS_LINKER_PATH ChibiOS_LINKER_SCRIPT)

