# TODO: Conditional enabling of platform specific drivers
# TODO: COnditional enabling of hal parts eg: gpio, rcc, i2c etc.
find_package(EelHalLL REQUIRED)

set(EelHal_ROOT_PATH ${CMAKE_CURRENT_LIST_DIR}/../hal)

# device related CMSIS stuff
set(DeviceIncludeDir ${CMAKE_CURRENT_LIST_DIR}/../cmsis/common/include
        ${CMAKE_CURRENT_LIST_DIR}/../cmsis/Device/ST/STM32F4xx/Include)
set(DeviceSourceFiles ${CMAKE_CURRENT_LIST_DIR}/../cmsis/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c
        ${CMAKE_CURRENT_LIST_DIR}/../cmsis/Device/ST/STM32F4xx/Source/Templates/gcc/startup_stm32f446xx.s)

set(EelHal_INCLUDE_DIR ${EelHalLL_INCLUDE_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/..
        ${DeviceIncludeDir})
set(EelHal_SRCS
        sys_tick_timer.cc
        gpio.cc
        rcc.cc
        usart.cc
   )

foreach(SRC ${EelHal_SRCS})
    find_file(FILE_${SRC} ${SRC}
            PATHS ${EelHal_ROOT_PATH} ${EelHal_ROOT_PATH}/cortex)
    list(APPEND EelHal_SOURCES ${FILE_${SRC}})
endforeach ()

# append LL sources
list(APPEND EelHal_SOURCES ${EelHalLL_SOURCES} ${DeviceSourceFiles})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(EelHal DEFAULT_MSG EelHal_INCLUDE_DIR EelHal_SOURCES)

