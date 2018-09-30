project(C CXX ASM)
include(Utils)

find_package(STM32HAL COMPONENTS gpio REQUIRED)
find_package(CMSIS REQUIRED)

include_directories(${CMSIS_INCLUDE_DIRS} ${STM32HAL_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/config)

add_executable(blinky.elf main.cpp ${STM32HAL_SOURCES} ${CMSIS_SOURCES} config/stm32f1xx_it.c
  config/stm32f1xx_hal_msp.c)

SetTargetProperties(blinky.elf)
SET_LINKER_PROPERTIES()
ADD_POST_BUILD_COPY(blinky)
