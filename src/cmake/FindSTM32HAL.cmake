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
endif()

foreach(cmp ${HAL_REQUIRED_COMPONENTS})
    # append the required components to the components list
    list(APPEND STM32HAL_FIND_COMPONENTS ${cmp})
    # TODO: Remove duplicates
endforeach()

foreach(cmp ${STM32HAL_FIND_COMPONENTS})
endforeach()
