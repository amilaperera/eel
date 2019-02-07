project(blinky C CXX ASM)
include(Utils)

#find_package(STM32HAL COMPONENTS gpio REQUIRED)
#find_package(CMSIS REQUIRED)
find_package(EelHal REQUIRED)
find_package(EelUtil REQUIRED)
find_package(OpenOCD REQUIRED)

include_directories(${CMSIS_INCLUDE_DIRS}
        ${EelHal_INCLUDE_DIR}
        ${EelUtil_INCLUDE_DIR}
        ${STM32HAL_INCLUDE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/config)

add_executable(${PROJECT_NAME}.elf
        main.cpp
        ${EelHal_SOURCES}
        ${EelUtil_SOURCES}
        #${STM32HAL_SOURCES}
        #${CMSIS_SOURCES}
        config/stm32f4xx_it.c
        config/stm32f4xx_hal_msp.c)

SetTargetProperties(${PROJECT_NAME}.elf)
ADD_POST_BUILD_COPY(${PROJECT_NAME})
ADD_OPENOCD_TARGETS(${PROJECT_NAME})
