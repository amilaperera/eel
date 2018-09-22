set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Without this cmake complains about about non-existence of _exit() function when trying to compile a
# simple application at compiler checking
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# set toolchain binary extension
if (WIN32)
  set(TOOLCHAIN_BIN_EXTENSION ".exe")
endif ()

# First check the environment variable
set(TOOLCHAIN_PATH_TEMP $ENV{EEL_TOOLCHAIN_PATH})
if (TOOLCHAIN_PATH_TEMP)
  if (WIN32)
    string(REGEX REPLACE "\\\\" "/" TOOLCHAIN_PATH ${TOOLCHAIN_PATH_TEMP})
  else ()
    set(TOOLCHAIN_PATH ${TOOLCHAIN_PATH_TEMP})
  endif ()
  # create a prefix
  set(TOOLCHAIN_PATH_PREFIX "${TOOLCHAIN_PATH}/")
else ()
  # We assume that the toolchain binaries are found in the system PATH.
  message(STATUS "EEL_TOOLCHAIN_PATH not defined. eel assumes toolchain is in system path.")
endif ()

set(CMAKE_C_COMPILER "${TOOLCHAIN_PATH_PREFIX}arm-none-eabi-gcc${TOOLCHAIN_BIN_EXTENSION}" CACHE INTERNAL "c compiler")
set(CMAKE_CXX_COMPILER "${TOOLCHAIN_PATH_PREFIX}arm-none-eabi-g++${TOOLCHAIN_BIN_EXTENSION}" CACHE INTERNAL "cxx compiler")
set(CMAKE_ASM_COMPILER "${TOOLCHAIN_PATH_PREFIX}arm-none-eabi-gcc${TOOLCHAIN_BIN_EXTENSION}" CACHE INTERNAL "asm compiler")
set(CMAKE_BIN_SIZE "${TOOLCHAIN_PATH_PREFIX}arm-none-eabi-size${TOOLCHAIN_BIN_EXTENSION}" CACHE INTERNAL "size")
set(CMAKE_OBJCOPY "${TOOLCHAIN_PATH_PREFIX}arm-none-eabi-objcopy${TOOLCHAIN_BIN_EXTENSION}" CACHE INTERNAL "objcopy")
set(CMAKE_OBJDUMP "${TOOLCHAIN_PATH_PREFIX}arm-none-eabi-objdump${TOOLCHAIN_BIN_EXTENSION}" CACHE INTERNAL "objdump")

