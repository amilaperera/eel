#set(EEL_UTIL_CORE_COMPONENTS core)
#
#if(NOT EelUtil_FIND_COMPONENTS)
#    set(EelUtil_FIND_COMPONENTS ${EEL_UTIL_CORE_COMPONENTS})
#    message(STATUS "No EelUtil components selected, defaulting to ${EelUtil_FIND_COMPONENTS}")
#else()
#    message(STATUS "EelUtil components: ${EelUtil_FIND_COMPONENTS}")
#endif()

set(EelUtil_ROOT_PATH ${CMAKE_CURRENT_LIST_DIR}/../util)

set(EelStreams_SOURCES streams/io_stream.cc)

set(EelUtil_SRCS
    ${EelStreams_SOURCES}
   )
set(EelUtil_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)

foreach(SRC ${EelUtil_SRCS})
    find_file(FILE_${SRC} ${SRC}
            PATHS ${EelUtil_ROOT_PATH})
    list(APPEND EelUtil_SOURCES ${FILE_${SRC}})
endforeach ()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(EelUtil DEFAULT_MSG EelUtil_INCLUDE_DIR EelUtil_SOURCES)

