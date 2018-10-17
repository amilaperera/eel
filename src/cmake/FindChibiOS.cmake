if(NOT ChibiOS_FIND_COMPONENTS)
  set(ChibiOS_FIND_COMPONENTS HAL RT)
  message(STATUS "No ChibiOS components selected, using defaults: ${ChibiOS_FIND_COMPONENTS}")
else()
  message(STATUS "STM32HAL components: ${ChibiOS_FIND_COMPONENTS}")
endif()

# Find hal configuration file
if(NOT CHIBIOS_HAL_CONF_FILE)
  message(STATUS "CHIBIOS_HAL_CONF_FILE not specified. Trying to find it....")
  file(GLOB_RECURSE CHIBIOS_HAL_CONF_FILE "halconf.h")
  if(CHIBIOS_HAL_CONF_FILE STREQUAL "")
    message(FATAL_ERROR "Cannot find halconf.h, please specify it using CHIBIOS_HAL_CONF_FILE variable")
  else()
    message(STATUS "Found halconf.h: ${CHIBIOS_HAL_CONF_FILE}")
  endif()
endif()

# Find rt configuration file
if(NOT CHIBIOS_RT_CONF_FILE)
  message(STATUS "CHIBIOS_RT_CONF_FILE not specified. Trying to find it....")
  file(GLOB_RECURSE CHIBIOS_RT_CONF_FILE "chconf.h")
  if(CHIBIOS_RT_CONF_FILE STREQUAL "")
    message(FATAL_ERROR "Cannot find chconf.h, please specify it using CHIBIOS_RT_CONF_FILE variable")
  else()
    message(STATUS "Found chconf.h: ${CHIBIOS_RT_CONF_FILE}")
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
