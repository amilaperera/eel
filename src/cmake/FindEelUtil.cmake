#set(EEL_UTIL_CORE_COMPONENTS core)
#
#if(NOT EelUtil_FIND_COMPONENTS)
#    set(EelUtil_FIND_COMPONENTS ${EEL_UTIL_CORE_COMPONENTS})
#    message(STATUS "No EelUtil components selected, defaulting to ${EelUtil_FIND_COMPONENTS}")
#else()
#    message(STATUS "EelUtil components: ${EelUtil_FIND_COMPONENTS}")
#endif()

set(EelUtil_SOURCES)
set(EelUtil_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(EelUtil DEFAULT_MSG EelUtil_INCLUDE_DIR)

