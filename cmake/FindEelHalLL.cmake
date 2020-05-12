# This will find the low level platform specific drivers
# according to the hal components that are requested by the
# high level driver.
# This cmake file is used by the high level EelHal package.
set(EelHalLL_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src)

set(EelHalLL_ROOT_PATH ${CMAKE_SOURCE_DIR}/src/platform)

set(EelHalLL_SRCS
        gpio/gpio.cc
        rcc/rcc.cc
        usart/usart.cc
        exti/exti.cc
        syscfg/syscfg.cc
        af_map.cc
   )

# TODO: Conditional enabling of platform specific drivers
# TODO: COnditional enabling of hal parts eg: gpio, rcc, i2c etc.
foreach(SRC ${EelHalLL_SRCS})
    find_file(FILE_${SRC} ${SRC}
            PATH_SUFFIXES ll f4
            PATHS ${EelHalLL_ROOT_PATH}/stm32)
    list(APPEND EelHalLL_SOURCES ${FILE_${SRC}})
endforeach ()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(EelHalLL DEFAULT_MSG EelHalLL_INCLUDE_DIR EelHalLL_SOURCES)

