project(blinky_chibios C CXX ASM)
include(Utils)

find_package(STM32HAL COMPONENTS gpio REQUIRED)
find_package(CMSIS REQUIRED)
find_package(ChibiOS COMPONENTS RT REQUIRED)
find_package(OpenOCD REQUIRED)

add_definitions(-DCORTEX_USE_FPU=FALSE)
message(STATUS "ChibiOS SOURCES: ${ChibiOS_SOURCES}")
message(STATUS "ChibiOS INCLUDE_DIRS: ${ChibiOS_INCLUDE_DIRS}")

include_directories(${CMSIS_INCLUDE_DIRS}
  ${STM32HAL_INCLUDE_DIR}
  ${ChibiOS_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR}/config)

add_executable(${PROJECT_NAME}.elf
  main.cpp
  ${STM32HAL_SOURCES}
  ${ChibiOS_SOURCES}
  ${CMSIS_SOURCES}
  # config/stm32f4xx_it.c
  config/stm32f4xx_hal_msp.c
  )

SetTargetProperties(${PROJECT_NAME}.elf)
ADD_POST_BUILD_COPY(${PROJECT_NAME})
ADD_OPENOCD_TARGETS(${PROJECT_NAME})
