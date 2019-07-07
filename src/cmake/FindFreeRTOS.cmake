# Select FreeRTOS components.
set(FreeRTOS_ROOT_PATH ${CMAKE_CURRENT_LIST_DIR}/../ots/FreeRTOS)

set(FreeRTOS_SRCS
        croutine.c
        event_groups.c
        list.c
        queue.c
        stream_buffer.c
        tasks.c
        timers.c)
set(FreeRTOS_PORT_SRCS
        MSVC-MingW/port.c)

set(FreeRTOS_INCLUDE_DIR
        ${FreeRTOS_ROOT_PATH}/include)
foreach(SRC ${FreeRTOS_SRCS} ${FreeRTOS_PORT_SRCS})
    find_file(FILE_${SRC} ${SRC}
            PATH_SUFFIXES Source Source/portable
            PATHS ${FreeRTOS_ROOT_PATH})
    list(APPEND FreeRTOS_SOURCES ${FILE_${SRC}})
endforeach()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(FreeRTOS DEFAULT_MSG FreeRTOS_INCLUDE_DIR FreeRTOS_SOURCES)

