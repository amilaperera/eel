include(${CMAKE_CURRENT_LIST_DIR}/../ConfigToolchain.cmake)

if (CMAKE_CROSSCOMPILING)
  if (NOT CPU_FLAG)
    if ("${STM32_FAMILY_UPPER}" STREQUAL "F1")
      set(CPU_FLAG "cortex-m3")
    else ()
      set(CPU_FLAG "cortex-m4")
    endif ()
  endif ()
endif ()

include(${CMAKE_CURRENT_LIST_DIR}/../DefineCompilerFlags.cmake)
