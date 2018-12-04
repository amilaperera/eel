#pragma once

#if defined(__GNUC__)
#define EEL_ALWAYS_INLINE __attribute__((always_inline)) inline
#else
#define EEL_ALWAYS_INLINE inline
#endif
