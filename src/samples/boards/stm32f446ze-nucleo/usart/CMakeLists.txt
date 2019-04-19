project(usart C CXX ASM)
include(Utils)

find_package(EelHal REQUIRED)
find_package(EelUtil REQUIRED)
find_package(OpenOCD REQUIRED)

include_directories(${CMSIS_INCLUDE_DIRS}
        ${EelHal_INCLUDE_DIR}
        ${EelUtil_INCLUDE_DIR})

add_executable(usart.elf usart.cpp ${EelHal_SOURCES} ${EelUtil_SOURCES})
EelSetTargetProperties(usart.elf)
ADD_POST_BUILD_COPY(usart)
ADD_OPENOCD_TARGETS(usart)
ADD_SIZE_INFO(usart)

add_executable(io_stream.elf io_stream.cc ${EelHal_SOURCES} ${EelUtil_SOURCES})
EelSetTargetProperties(io_stream.elf)
ADD_POST_BUILD_COPY(io_stream)
ADD_OPENOCD_TARGETS(io_stream)
ADD_SIZE_INFO(io_stream)

add_executable(gpio_interrupt.elf gpio_interrupt.cc ${EelHal_SOURCES} ${EelUtil_SOURCES})
EelSetTargetProperties(gpio_interrupt.elf)
ADD_POST_BUILD_COPY(gpio_interrupt)
ADD_OPENOCD_TARGETS(gpio_interrupt)
ADD_SIZE_INFO(gpio_interrupt)
