project(util_samples C CXX ASM)

set(EEL_FREERTOS_MEMORY_MANAGEMENT "HEAP4")

find_package(EelUtils REQUIRED)
find_package(FreeRTOS REQUIRED)
include_directories(${EelUtils_INCLUDE_DIR} ${FreeRTOS_INCLUDE_DIRS} ../rtos/config)

add_executable(os_object_test os_object_test.cpp
    ${EelUtils_SOURCES} ${EelUtils_Os_SOURCES} ${FreeRTOS_SOURCES})
add_executable(free_rtos_basic_sample free_rtos_basic_sample.cpp
    ${EelUtils_SOURCES} ${EelUtils_Os_SOURCES} ${FreeRTOS_SOURCES})
add_executable(simple_task simple_task.cpp
    ${EelUtils_SOURCES} ${EelUtils_Os_SOURCES} ${FreeRTOS_SOURCES})
add_executable(sender_receiver_tasks sender_receiver_tasks.cpp
    ${EelUtils_SOURCES} ${EelUtils_Os_SOURCES} ${FreeRTOS_SOURCES})

target_compile_features(os_object_test PRIVATE cxx_std_17)
target_compile_features(free_rtos_basic_sample PRIVATE cxx_std_17)
target_compile_features(simple_task PRIVATE cxx_std_17)
target_compile_features(sender_receiver_tasks PRIVATE cxx_std_17)

