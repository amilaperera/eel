set(TOOLCHAIN_HELPERS_PATH ${CMAKE_CURRENT_LIST_DIR}/toolchain_helpers)

include(${TOOLCHAIN_HELPERS_PATH}/ConfigToolchain.cmake)
include(${TOOLCHAIN_HELPERS_PATH}/ParseMCUInfo.cmake)
include(${TOOLCHAIN_HELPERS_PATH}/DefineCompilerFlags.cmake)
