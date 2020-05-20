project(usart C CXX ASM)
include(Utils)

find_package(EelHal COMPONENTS gpio uart REQUIRED)
find_package(OpenOCD REQUIRED)

include_directories(${CMSIS_INCLUDE_DIRS}
        ${STM32HAL_INCLUDE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/config)

add_executable(${PROJECT_NAME}.elf
        main.cpp
        ${STM32HAL_SOURCES}
        ${CMSIS_SOURCES}
        config/stm32f4xx_it.c
        config/stm32f4xx_hal_msp.c)

SetTargetProperties(${PROJECT_NAME}.elf)
ADD_POST_BUILD_COPY(${PROJECT_NAME})
ADD_OPENOCD_TARGETS(${PROJECT_NAME})
ADD_SIZE_INFO(${PROJECT_NAME})
