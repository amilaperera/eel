set(EelUtils_ROOT_PATH ${CMAKE_SOURCE_DIR}/src/utils)

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
set(EelUtils_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src)

foreach(SRC ${EelOsNone_SOURCES})
    find_file(FILE_${SRC} ${SRC}
            PATHS ${EelUtils_ROOT_PATH})
    list(APPEND EelUtils_SOURCES ${FILE_${SRC}})
endforeach ()

foreach(SRC ${EelOs_SOURCES})
    find_file(FILE_${SRC} ${SRC}
            PATHS ${EelUtils_ROOT_PATH})
    list(APPEND EelUtils_Os_SOURCES ${FILE_${SRC}})
endforeach ()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(EelUtils DEFAULT_MSG EelUtils_INCLUDE_DIR EelUtils_SOURCES EelUtils_Os_SOURCES)

