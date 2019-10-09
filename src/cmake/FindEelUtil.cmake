set(EelUtil_ROOT_PATH ${CMAKE_CURRENT_LIST_DIR}/../util)

set(EelStreams_SOURCES streams/io_stream.cc)
set(EelOsTask_SOURCES os/task.cc)
if (WIN32)
    set(EelPorts_SOURCES ports/pc/console_device.cc)
endif()

set(EelUtil_SRCS
    ${EelStreams_SOURCES}
    ${EelPorts_SOURCES}
    ${EelOsTask_SOURCES}
   )
set(EelUtil_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)

foreach(SRC ${EelUtil_SRCS})
    find_file(FILE_${SRC} ${SRC}
            PATHS ${EelUtil_ROOT_PATH})
    list(APPEND EelUtil_SOURCES ${FILE_${SRC}})
endforeach ()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(EelUtil DEFAULT_MSG EelUtil_INCLUDE_DIR EelUtil_SOURCES)

