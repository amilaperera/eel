cmake_minimum_required(VERSION 3.8)

option(EEL_USE_OS_CHIBIOS "Use ChibiOS" OFF)
option(EEL_USE_OS_NONE "Do not use an OS" ON)

# make the flags mutually exclusive
if(EEL_USE_OS_CHIBIOS)
  set(EEL_USE_OS_NONE OFF)
endif()

if(EEL_USE_OS_CHIBIOS AND EEL_USE_OS_NONE)
  message(FATAL_ERROR "Only one of these configuration options are allowed to be enabled: EEL_USE_OS_NONE, EEL_USE_OS_CHIBIOS")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
add_subdirectory(samples)

