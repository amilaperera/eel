if(STM32_FAMILY_UPPER STREQUAL "F1")
    set(HAL_COMPONENTS
        gpio)
    set(HAL_REQUIRED_COMPONENTS
        cortex pwr rcc)
    set(HAL_EX_COMPONENTS
        gpio)
    set(HAL_PREFIX stm32f1xx_)
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
    # append the required components to the components list
    list(APPEND STM32HAL_FIND_COMPONENTS ${cmp})
    # TODO: Remove duplicates
endforeach()

foreach(cmp ${STM32HAL_FIND_COMPONENTS})
    list(APPEND HAL_HEADERS ${HAL_PREFIX}hal_${cmp}.h)
    list(APPEND HAL_SOURCES ${HAL_PREFIX}hal_${cmp}.c)
    list(APPEND HAL_HEADERS ${HAL_PREFIX}hal_${cmp}_ex.h)
    list(APPEND HAL_SOURCES ${HAL_PREFIX}hal_${cmp}_ex.c)
endforeach()

list(REMOVE DUPLICATES HAL_HEADERS)
list(REMOVE DUPLICATES HAL_SOURCES)

find_path(STM32HAL_INCLUDE_DIR
    ${HAL_HEADERS}
    PATH_SUFFIXES stm32/${STM32_FAMILY_LOWER}
    HINTS 
    )
