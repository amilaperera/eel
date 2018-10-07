if(STM32_FAMILY_UPPER STREQUAL "F1")
    set(HAL_REQUIRED_COMPONENTS
        cortex pwr rcc)
    set(HAL_COMPONENTS
        gpio)
    set(HAL_EX_COMPONENTS
        rcc
        gpio)
    # common prefix for f1
    set(HAL_PREFIX stm32f1xx_)
elseif(STM32_FAMILY_UPPER STREQUAL "F4")
    set(HAL_REQUIRED_COMPONENTS
        cortex pwr rcc)
    set(HAL_COMPONENTS
        gpio)
    set(HAL_EX_COMPONENTS
        rcc)
    # common prefix for f1
    set(HAL_PREFIX stm32f4xx_)
endif()

if(NOT STM32HAL_FIND_COMPONENTS)
    set(STM32HAL_FIND_COMPONENTS ${HAL_COMPONENTS})
    message(STATUS "No STM32HAL components selected, using all: ${STM32HAL_FIND_COMPONENTS}")
else()
    message(STATUS "STM32HAL components: ${STM32HAL_FIND_COMPONENTS}")
endif()

set(HAL_HEADERS ${HAL_PREFIX}hal.h ${HAL_PREFIX}hal_def.h)
set(HAL_SOURCES ${HAL_PREFIX}hal.c)

foreach(cmp ${HAL_REQUIRED_COMPONENTS})
    list(APPEND STM32HAL_FIND_COMPONENTS ${cmp})
endforeach()

foreach(cmp ${STM32HAL_FIND_COMPONENTS})
    list(APPEND HAL_HEADERS ${HAL_PREFIX}hal_${cmp}.h)
    list(APPEND HAL_SOURCES ${HAL_PREFIX}hal_${cmp}.c)
    # add ex component
    list (FIND HAL_EX_COMPONENTS ${cmp} FOUND_INDEX)
    if(NOT ${FOUND_INDEX} LESS 0)
      list(APPEND HAL_HEADERS ${HAL_PREFIX}hal_${cmp}_ex.h)
      list(APPEND HAL_SOURCES ${HAL_PREFIX}hal_${cmp}_ex.c)
    endif()
endforeach()

# Now remove all the duplicates
list(REMOVE_DUPLICATES HAL_HEADERS)
list(REMOVE_DUPLICATES HAL_SOURCES)

# export include directory
set(STM32HAL_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/../platform/stm32/${STM32_FAMILY_LOWER}/STM32${STM32_FAMILY_UPPER}xx_HAL_Driver/Inc)

# export all the sources
foreach(SRC ${HAL_SOURCES})
  find_file(FILE_${SRC} ${SRC}
    PATH_SUFFIXES Src
    PATHS ${CMAKE_CURRENT_LIST_DIR}/../platform/stm32/${STM32_FAMILY_LOWER}/STM32${STM32_FAMILY_UPPER}xx_HAL_Driver)
  list(APPEND STM32HAL_SOURCES ${FILE_${SRC}})
endforeach ()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(STM32HAL DEFAULT_MSG STM32HAL_INCLUDE_DIR STM32HAL_SOURCES)

