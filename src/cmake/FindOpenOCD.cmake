unset(OPENOCD_EXECUTABLE)

# find OpenOCD on system path
find_program(OPENOCD_EXECUTABLE
  NAMES openocd open-ocd
  PATHS OpenOcd)

# We merge the output stream and error stream
if (OPENOCD_EXECUTABLE)
  execute_process(COMMAND "${OPENOCD_EXECUTABLE}" --version
    OUTPUT_VARIABLE OPENOCD_VERSION
    ERROR_VARIABLE OPENOCD_VERSION
    RESULT_VARIABLE OPENOCD_VERSION_RESULT
    ERROR_QUIET)

  # extract major, minor and patch
  if (NOT OPENOCD_VERSION_RESULT)
    string(REGEX REPLACE "^.*([0-9]+\\.[0-9]+\\.[0-9]+).*$" "\\1" OPENOCD_VERSION_STRING "${OPENOCD_VERSION}")
    string(REGEX REPLACE "^([0-9]+)\\.[0-9]+\\.[0-9]+" "\\1" OPENOCD_VERSION_MAJOR "${OPENOCD_VERSION_STRING}")
    string(REGEX REPLACE "^[0-9]+\\.([0-9]+)\\.[0-9]+" "\\1" OPENOCD_VERSION_MINOR "${OPENOCD_VERSION_STRING}")
    if (OPENOCD_VERSION_STRING MATCHES "^[0-9]+\\.[0-9]+\\.([0-9]+)")
      set(OPENOCD_VERSION_PATCH "${CMAKE_MATCH_1}")
    else()
      set(OPENOCD_VERSION_PATCH "0")
    endif()
  else ()
    message(STATUS "OpenOcd version information couldn't be extracted.")
  endif ()

  unset(OPENOCD_VERSION)
  unset(OPENOCD_VERSION_RESULT)

  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(OpenOCD DEFAULT_MSG OPENOCD_EXECUTABLE OPENOCD_VERSION_STRING)
else ()
  message(WARNING "OpenOCD not found. Please check if OpenOCD is installed on a system path.")
endif ()

