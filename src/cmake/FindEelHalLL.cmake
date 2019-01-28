set(EelHalLL_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)

set(EelHalLL_ROOT_PATH ${CMAKE_CURRENT_LIST_DIR}/../platform)

set(EelHalLL_SOURCES ${EelHalLL_ROOT_PATH}/stm32/f4/gpio.cc)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(EelHalLL DEFAULT_MSG EelHalLL_INCLUDE_DIR EelHalLL_SOURCES)

