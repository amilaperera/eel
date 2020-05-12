set(EelUtil_ROOT_PATH ${CMAKE_SOURCE_DIR}/src/util)

# OS NONE
set(EelStreams_SOURCES streams/io_stream.cc)
if (WIN32)
    set(EelPorts_SOURCES ports/pc/console_device.cc)
endif()

# OS
set(EelOsTask_SOURCES os_wrapper/task.cc)

# Collate OS & OS None
set(EelOsNone_SOURCES ${EelStreams_SOURCES} ${EelPorts_SOURCES})
set(EelOs_SOURCES ${EelOsTask_SOURCES})

set(EelUtil_SRCS
    ${EelOsNone_SOURCES}
    ${EelOs_SOURCES}
   )
set(EelUtil_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src)

foreach(SRC ${EelOsNone_SOURCES})
    find_file(FILE_${SRC} ${SRC}
            PATHS ${EelUtil_ROOT_PATH})
    list(APPEND EelUtil_SOURCES ${FILE_${SRC}})
endforeach ()

foreach(SRC ${EelOs_SOURCES})
    find_file(FILE_${SRC} ${SRC}
            PATHS ${EelUtil_ROOT_PATH})
    list(APPEND EelUtil_OS_SOURCES ${FILE_${SRC}})
endforeach ()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(EelUtil DEFAULT_MSG EelUtil_INCLUDE_DIR EelUtil_SOURCES EelUtil_OS_SOURCES)

