find_package(EelHalLL REQUIRED)

set(EelHal_ROOT_PATH ${CMAKE_CURRENT_LIST_DIR}/../hal)

set(EelHal_INCLUDE_DIR ${EelHalLL_INCLUDE_DIR} ${CMAKE_CURRENT_LIST_DIR}/..)
set(EelHal_SOURCES ${EelHalLL_SOURCES} ${EelHal_ROOT_PATH}/gpio.cc)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(EelHal DEFAULT_MSG EelHal_INCLUDE_DIR EelHal_SOURCES)

