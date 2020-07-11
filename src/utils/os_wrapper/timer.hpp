//
// Created by amila.perera on 06/07/2020.
//

#pragma once

#include "ots/FreeRTOS/Source/include/FreeRTOS.h"
#include "ots/FreeRTOS/Source/include/timers.h"
#include "utils/os_wrapper/ticks.hpp"
#include "utils/os_wrapper/free_rtos_types.hpp"
#include <utility>
#include <functional>

namespace eel::utils::os_wrapper {
#ifdef configUSE_TIMERS
namespace detail {
void one_shot_timer_callback(TimerHandle_t handle);
void periodic_timer_callback(TimerHandle_t handle);

enum class timer_type : bool {
  periodic = true,
  one_shot = false
};

struct timer_create_helper_base {
  using Callback = void (*)(TimerHandle_t);
};

template <detail::timer_type>
struct timer_create_helper;

template <>
struct timer_create_helper<detail::timer_type::one_shot> : public timer_create_helper_base {
  static Callback callback;
  static constexpr u_base_t value{pdFALSE};
};
template <>
struct timer_create_helper<detail::timer_type::periodic> : public timer_create_helper_base {
  static Callback callback;
  static constexpr u_base_t value{pdTRUE};
};

class timer_base {
 protected:
  TimerHandle_t handle_;
  std::function<void()> callback_;
 public:
  template <detail::timer_type T>
  timer_base(const char* name, os_wrapper::time_ticks t, std::function<void()> callback, timer_create_helper<T>) : handle_{}, callback_(std::move(callback)) {
    handle_ = xTimerCreate(name, t.ticks, detail::timer_create_helper<T>::value, this, detail::timer_create_helper<T>::callback);
  }

  bool start(os_wrapper::time_ticks time_out = os_wrapper::max_ticks()) {
    return xTimerStart(handle_, time_out.ticks) == pdTRUE;
  }
};
}

class one_shot_timer : public detail::timer_base {
 friend void detail::one_shot_timer_callback(TimerHandle_t handle);
 private:
  constexpr static const char* kDefaultName{"UnNamedOneShot"};
 public:
  one_shot_timer(time_ticks ticks, std::function<void()> callback, const char* name = kDefaultName) : detail::timer_base(name, ticks, std::move(callback), detail::timer_create_helper<detail::timer_type::one_shot>()) {}
};

class periodic_timer : public detail::timer_base {
  friend void detail::periodic_timer_callback(TimerHandle_t handle);
 private:
  constexpr static const char* kDefaultName{"UnNamedPeriodic"};
 public:
  periodic_timer(time_ticks ticks, std::function<void()> callback, const char* name = kDefaultName) : detail::timer_base(name, ticks, std::move(callback), detail::timer_create_helper<detail::timer_type::periodic>()) {}
};
#endif
}
