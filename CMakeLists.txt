cmake_minimum_required(VERSION 3.13)
project(eel)

option(EnableRtos "Enable RTOS" Off)
option(EnableSamples "Enable sample programs" On)
option(EnableStmSamples "Enalbe STM32 sample programs" On)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

if (EnableSamples OR EnableStmSamples)
  add_subdirectory(src/samples)
endif ()
