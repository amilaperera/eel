# TODO: Conditional enabling of platform specific drivers
# TODO: COnditional enabling of hal parts eg: gpio, rcc, i2c etc.
find_package(EelHalLL REQUIRED)

set(EelHal_ROOT_PATH ${CMAKE_CURRENT_LIST_DIR}/../hal)

set(EelHal_INCLUDE_DIR ${EelHalLL_INCLUDE_DIR} ${CMAKE_CURRENT_LIST_DIR}/..)
set(EelHal_SRCS
        gpio.cc
        rcc.cc
   )

foreach(SRC ${EelHal_SRCS})
    find_file(FILE_${SRC} ${SRC}
            PATHS ${EelHal_ROOT_PATH})
    list(APPEND EelHal_SOURCES ${FILE_${SRC}})
endforeach ()

# append LL sources
list(APPEND EelHal_SOURCES ${EelHalLL_SOURCES})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(EelHal DEFAULT_MSG EelHal_INCLUDE_DIR EelHal_SOURCES)

