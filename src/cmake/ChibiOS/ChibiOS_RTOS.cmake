# Set chibios root path
# Accumulate ChibiOS RT components
# ChibiOS core compoents
set(CHIBIOS_SOURCES_RT
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
  os/rt/include
  os/common/oslib/include)

foreach(COMP ${CHIBIOS_RT_COMPONENTS})
  if(CHIBIOS_SOURCES_RT_${COMP})
    list(APPEND CHIBIOS_SOURCES_RT ${CHIBIOS_SOURCES_RT_${COMP}})
  endif()
endforeach()

