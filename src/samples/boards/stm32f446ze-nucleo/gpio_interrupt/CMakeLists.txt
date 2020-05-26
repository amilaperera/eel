project(gpio_interrupt C CXX ASM)
include(Utils)

find_package(EelHal COMPONENTS gpio REQUIRED)
find_package(OpenOCD REQUIRED)

add_executable(${PROJECT_NAME}.elf
    main.cpp
    ${STM32HAL_SOURCES}
    ${EelHal_SOURCES}
    config/stm32f4xx_it.c
    config/stm32f4xx_hal_msp.c)
target_include_directories(${PROJECT_NAME}.elf PRIVATE ${CMAKE_SOURCE_DIR}/src ${EelHal_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/config)

SetTargetProperties(${PROJECT_NAME}.elf)
ADD_POST_BUILD_COPY(${PROJECT_NAME})
ADD_OPENOCD_TARGETS(${PROJECT_NAME})
ADD_SIZE_INFO(${PROJECT_NAME})

