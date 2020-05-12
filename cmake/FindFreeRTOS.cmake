# Select FreeRTOS components.
set(FreeRTOS_ROOT_PATH ${CMAKE_SOURCE_DIR}/src/ots/FreeRTOS)

set(FreeRTOS_SRCS
        croutine.c
        event_groups.c
        list.c
        queue.c
        stream_buffer.c
        tasks.c
        timers.c)
if (WIN32)
    list(APPEND FreeRTOS_SRCS MSVC-MingW/port.c)
    list(APPEND FreeRTOS_INCLUDE_DIRS ${FreeRTOS_ROOT_PATH}/Source/portable/MSVC-MingW)
endif()

if (EEL_FREERTOS_MEMORY_MANAGEMENT STREQUAL "HEAP1")
    message("-- FreeRTOS MemMang strategy: HEAP1")
    list(APPEND FreeRTOS_SRCS heap_1.c)
elseif (EEL_FREERTOS_MEMORY_MANAGEMENT STREQUAL "HEAP2")
    message("-- FreeRTOS MemMang strategy: HEAP2")
    list(APPEND FreeRTOS_SRCS heap_2.c)
elseif (EEL_FREERTOS_MEMORY_MANAGEMENT STREQUAL "HEAP3")
    message("-- FreeRTOS MemMang strategy: HEAP3")
    list(APPEND FreeRTOS_SRCS heap_3.c)
elseif (EEL_FREERTOS_MEMORY_MANAGEMENT STREQUAL "HEAP4")
    message("-- FreeRTOS MemMang strategy: HEAP4")
    list(APPEND FreeRTOS_SRCS heap_4.c)
elseif (EEL_FREERTOS_MEMORY_MANAGEMENT STREQUAL "HEAP5")
    message("-- FreeRTOS MemMang strategy: HEAP5")
    list(APPEND FreeRTOS_SRCS heap_5.c)
else()
    message(FATAL_ERROR "FreeRTOS FreeRTOS MemMang scheme not set. Should be one of: HEAP1, HEAP2, HEAP3, HEAP4 or HEAP5")
endif()

list(APPEND FreeRTOS_INCLUDE_DIRS
        ${FreeRTOS_ROOT_PATH}/Source/include)
foreach(SRC ${FreeRTOS_SRCS})
    find_file(FILE_${SRC} ${SRC}
            PATH_SUFFIXES Source Source/portable Source/portable/MemMang
            PATHS ${FreeRTOS_ROOT_PATH})
    list(APPEND FreeRTOS_SOURCES ${FILE_${SRC}})
endforeach()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(FreeRTOS DEFAULT_MSG FreeRTOS_INCLUDE_DIRS FreeRTOS_SOURCES)

