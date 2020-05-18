find_package(STM32HAL COMPONENTS gpio REQUIRED)
find_package(CMSIS REQUIRED)

set(EelHal_ROOT_PATH ${CMAKE_SOURCE_DIR}/src/hal)
set(EelPlatform_ROOT_PATH ${CMAKE_SOURCE_DIR}/src/platform)

# device related CMSIS stuff
set(EelHal_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src ${STM32HAL_INCLUDE_DIR} ${CMSIS_INCLUDE_DIRS})
set(EelHal_SRCS gpio.cpp)

foreach(SRC ${EelHal_SRCS})
    find_file(FILE_${SRC} ${SRC}
            PATHS ${EelHal_ROOT_PATH} ${EelPlatform_ROOT_PATH}/stm32)
    list(APPEND EelHal_SOURCES ${FILE_${SRC}})
endforeach ()

# append LL sources
list(APPEND EelHal_SOURCES ${EelHalLL_SOURCES} ${STM32HAL_SOURCES} ${CMSIS_SOURCES})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(EelHal DEFAULT_MSG EelHal_INCLUDE_DIR EelHal_SOURCES)

