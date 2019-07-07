project(gpio_interrupt C CXX ASM)
include(Utils)

find_package(EelHal REQUIRED)
find_package(EelUtil REQUIRED)
find_package(OpenOCD REQUIRED)

include_directories(${CMSIS_INCLUDE_DIRS}
        ${EelHal_INCLUDE_DIR}
        ${EelUtil_INCLUDE_DIR})

add_executable(${PROJECT_NAME}.elf
        main.cpp
        ${EelHal_SOURCES}
        ${EelUtil_SOURCES})

EelSetTargetProperties(${PROJECT_NAME}.elf)
ADD_POST_BUILD_COPY(${PROJECT_NAME})
ADD_OPENOCD_TARGETS(${PROJECT_NAME})
ADD_SIZE_INFO(${PROJECT_NAME})

