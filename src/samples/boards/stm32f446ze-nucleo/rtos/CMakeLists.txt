project(rtos_samples C CXX ASM)
include(Utils)
set(EEL_FREERTOS_MEMORY_MANAGEMENT "HEAP4")

find_package(EelHal COMPONENTS gpio uart REQUIRED)
find_package(FreeRTOS REQUIRED)
find_package(EelUtils REQUIRED)
find_package(OpenOCD REQUIRED)

add_executable(simple_task.elf
    simple_task.cpp
    ${EelHal_SOURCES}
    ${EelUtils_SOURCES}
    ${FreeRTOS_SOURCES}
    ${EelUtils_Os_SOURCES}
    config/stm32f4xx_it.c
    config/stm32f4xx_hal_msp.c)
target_include_directories(simple_task.elf PRIVATE
    ${EelHal_INCLUDE_DIR}
    ${EelUtils_INCLUDE_DIR}
    ${FreeRTOS_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/config)
target_compile_features(simple_task.elf PRIVATE cxx_std_17)

SetTargetProperties(simple_task.elf)
ADD_POST_BUILD_COPY(simple_task)
ADD_OPENOCD_TARGETS(simple_task)
ADD_SIZE_INFO(simple_task)

