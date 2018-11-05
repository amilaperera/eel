# TODO: This should be generalized,
# currently considering F4
set(CHIBIOS_COMMON_SOURCES
  os/common/startup/ARMCMx/compilers/GCC/crt0_v7m.S
  os/common/ports/ARMCMx/chcore.c
  os/common/ports/ARMCMx/chcore_v7m.c
  os/common/ports/ARMCMx/compilers/GCC/chcoreasm_v7m.S
)

set(CHIBIOS_COMMON_INCLUDE
  os/common/startup/ARMCMx/devices/STM32F4xx
  # os/common/ext/ST/STM32F4xx
  os/common/oslib/include
  os/common/ports/ARMCMx
  os/common/ports/ARMCMx/compilers/GCC
)

list(APPEND CHIBIOS_COMMON_SOURCES
  os/common/startup/ARMCMx/compilers/GCC/crt1.c
  os/common/startup/ARMCMx/compilers/GCC/vectors.S
)

list(APPEND CHIBIOS_COMMON_INCLUDE
    os/license
    os/common/portability/GCC
    os/common/startup/ARMCMx/compilers/GCC
    os/common/ext/ARM/CMSIS/Core/Include
)

list(APPEND CHIBIOS_SOURCES_RT ${CHIBIOS_COMMON_SOURCES})

# Accumulate ChibiOS RT components
# ChibiOS core compoents
list(APPEND CHIBIOS_SOURCES_RT
  os/rt/src/chsys.c
  os/rt/src/chdebug.c
  os/rt/src/chtrace.c
  os/rt/src/chvt.c
  os/rt/src/chschd.c
  os/rt/src/chthreads.c)

# ChibiOS kernel optional components
set(CHIBIOS_SOURCES_RT_TM             os/rt/src/chtm.c)
set(CHIBIOS_SOURCES_RT_REGISTRY       os/rt/src/chregistry.c)
set(CHIBIOS_SOURCES_RT_SEMAPHORES     os/rt/src/chsem.c)
set(CHIBIOS_SOURCES_RT_MUTEXES        os/rt/src/chmtx.c)
set(CHIBIOS_SOURCES_RT_CONDVARS       os/rt/src/chcond.c)
set(CHIBIOS_SOURCES_RT_EVENTS         os/rt/src/chevents.c)
set(CHIBIOS_SOURCES_RT_MESSAGES       os/rt/src/chmsg.c)
set(CHIBIOS_SOURCES_RT_DYNAMIC        os/rt/src/chdynamic.c)
# TODO: Include CH_DBG_STATISTICS

# ChibiOS OSAL components
set(CHIBIOS_SOURCES_RT_MAILBOXES      os/common/oslib/src/chmboxes.c)
set(CHIBIOS_SOURCES_RT_MEMCORE        os/common/oslib/src/chmemcore.c)
set(CHIBIOS_SOURCES_RT_HEAP           os/common/oslib/src/chheap.c)
set(CHIBIOS_SOURCES_RT_MEMPOOLS       os/common/oslib/src/chmempools.c)
set(CHIBIOS_SOURCES_RT_FACTORY        os/common/oslib/src/chfactory.c)

set(CHIBIOS_INCLUDE_DIRS
  ${CHIBIOS_COMMON_INCLUDE}
  os/rt/include
  os/common/oslib/include)

foreach(COMP ${CHIBIOS_RT_COMPONENTS})
  if(CHIBIOS_SOURCES_RT_${COMP})
    list(APPEND CHIBIOS_SOURCES_RT ${CHIBIOS_SOURCES_RT_${COMP}})
  endif()
endforeach()

