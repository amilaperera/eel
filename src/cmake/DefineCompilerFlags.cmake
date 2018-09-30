# Setting flags common to both C & C++
set(COMMON_FLAGS "-mcpu=${CPU_FLAG} -mthumb -Wall -ffunction-sections" CACHE INTERNAL "common flags")
# Setting C specific flags
set(CMAKE_C_FLAGS "${COMMON_FLAGS} -std=gnu11" CACHE INTERNAL "c compiler flags")
# Setting C++ specific flags
set(CMAKE_CXX_FLAGS "${COMMON_FLAGS} -std=gnu++17 -Wno-write-strings -fno-exceptions -fno-rtti" CACHE INTERNAL "cxx compiler flags")
# Setting Asemmbler specific flags
set(CMAKE_ASM_FLAGS "-mcpu=${CPU_FLAG} -mthumb -x assembler-with-cpp" CACHE INTERNAL "asm compiler flags")
# Basic linker flags
set(CMAKE_EXE_LINKER_FLAGS "-specs=nano.specs" CACHE INTERNAL "executable linker flags")

set(CMAKE_C_FLAGS_DEBUG "-Og -g" CACHE INTERNAL "c compiler flags debug")
set(CMAKE_CXX_FLAGS_DEBUG "-Og -g" CACHE INTERNAL "cxx compiler flags debug")
set(CMAKE_ASM_FLAGS_DEBUG "-g" CACHE INTERNAL "asm compiler flags debug")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "" CACHE INTERNAL "linker flags debug")

set(CMAKE_C_FLAGS_RELEASE "-Os -flto" CACHE INTERNAL "c compiler flags release")
set(CMAKE_CXX_FLAGS_RELEASE "-Os -flto" CACHE INTERNAL "cxx compiler flags release")
set(CMAKE_ASM_FLAGS_RELEASE "" CACHE INTERNAL "asm compiler flags release")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "-flto" CACHE INTERNAL "linker flags release")

# Set linker script
if(CMAKE_CROSSCOMPILING)
  if(NOT EEL_LINKER_SCRIPT)
    if("${EEL_MCU}" MATCHES "[sS][tT][mM]32[fF]103[rR][bB]")
      set(LINKER_SCRIPT "STM32F103RBTx_FLASH.ld")
    endif()

    if(NOT LINKER_SCRIPT)
      message(FATAL_ERROR "Linker script couldn't be deduced by the MCU definitions.")
    else()
      set(EEL_LINKER_SCRIPT ${CMAKE_CURRENT_LIST_DIR}/../platform/stm32/f1/linker_scripts/${LINKER_SCRIPT})
    endif()
  endif()

endif()

