#pragma once

#if defined(__GNUC__)
#define EEL_ALWAYS_INLINE __attribute__((always_inline)) inline
#else
#define EEL_ALWAYS_INLINE inline
#endif

#define DELETE_COPY_CTOR(X) X(const X&) = delete
#define DELETE_COPY_ASSIGNMENT(X) X& operator=(const X&) = delete
#define DELETE_MOVE_CTOR(X) X(X&&) = delete
#define DELETE_MOVE_ASSIGNMENT(X) X& operator=(X&&) = delete
