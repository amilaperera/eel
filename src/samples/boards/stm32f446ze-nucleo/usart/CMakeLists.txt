project(uart_samples C CXX ASM)
include(Utils)

find_package(EelHal COMPONENTS gpio uart REQUIRED)
find_package(EelUtils REQUIRED)
find_package(OpenOCD REQUIRED)

add_executable(uart.elf
        main.cpp
        ${EelHal_SOURCES}
        config/stm32f4xx_it.c
        config/stm32f4xx_hal_msp.c)
target_include_directories(uart.elf PRIVATE ${CMAKE_SOURCE_DIR}/src ${EelHal_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/config)
target_compile_features(uart.elf PRIVATE cxx_std_17)

SetTargetProperties(uart.elf)
ADD_POST_BUILD_COPY(uart)
ADD_OPENOCD_TARGETS(uart)
ADD_SIZE_INFO(uart)

add_executable(io_stream.elf
    io_stream.cpp
    ${EelHal_SOURCES}
    ${EelUtils_SOURCES}
    config/stm32f4xx_it.c
    config/stm32f4xx_hal_msp.c)
target_include_directories(io_stream.elf PRIVATE ${CMAKE_SOURCE_DIR}/src ${EelUtils_INCLUDE_DIR} ${EelHal_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/config)
target_compile_features(io_stream.elf PRIVATE cxx_std_17)

SetTargetProperties(io_stream.elf)
ADD_POST_BUILD_COPY(io_stream)
ADD_OPENOCD_TARGETS(io_stream)
ADD_SIZE_INFO(io_stream)
