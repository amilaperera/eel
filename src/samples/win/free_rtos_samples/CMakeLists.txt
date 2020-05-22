project(util_samples C CXX ASM)

set(EEL_FREERTOS_MEMORY_MANAGEMENT "HEAP4")

find_package(EelUtils REQUIRED)
find_package(FreeRTOS REQUIRED)
include_directories(${EelUtils_INCLUDE_DIR} ${FreeRTOS_INCLUDE_DIRS} ../free_rtos_samples/free_rtos_config)

add_executable(free_rtos_basic_sample free_rtos_basic_sample.cpp
    ${EelUtils_SOURCES} ${EelUtils_Os_SOURCES} ${FreeRTOS_SOURCES})
add_executable(free_rtos_task free_rtos_task.cpp
    ${EelUtils_SOURCES} ${EelUtils_Os_SOURCES} ${FreeRTOS_SOURCES})

target_compile_features(free_rtos_basic_sample PRIVATE cxx_std_17)
target_compile_features(free_rtos_task PRIVATE cxx_std_17)

