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

#if (configUSE_TIMERS == 1)
namespace eel::utils::os_wrapper {
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
 private:
  template <typename Func, typename ... Ts>
  bool from_isr_impl_caller(Func f, bool *flag, Ts&& ... ts) {
    os_wrapper::s_base_t is_woken{pdFALSE};
    auto ret = std::invoke(f, this, std::forward<Ts>(ts)..., &is_woken);
    *flag = (is_woken == pdTRUE);
    return ret == pdTRUE;
  }

  bool start_from_isr_impl(os_wrapper::s_base_t *is_woken) {
    return xTimerStartFromISR(handle_, is_woken) == pdTRUE;
  }

  bool stop_from_isr_impl(os_wrapper::s_base_t *is_woken) {
    return xTimerStopFromISR(handle_, is_woken) == pdTRUE;
  }

  bool reset_from_isr_impl(os_wrapper::s_base_t *is_woken) {
    return xTimerResetFromISR(handle_, is_woken) == pdTRUE;
  }

  bool change_timer_from_isr_impl(tick_t new_tick_period, os_wrapper::s_base_t *is_woken) {
    return xTimerChangePeriodFromISR(handle_, new_tick_period, is_woken);
  }

 protected:
  TimerHandle_t handle_;
  std::function<void()> callback_;

 public:
  template <detail::timer_type T>
  timer_base(const char* name, os_wrapper::time_ticks t, std::function<void()> callback, timer_create_helper<T>) : handle_{}, callback_(std::move(callback)) {
    handle_ = xTimerCreate(name, t.ticks, detail::timer_create_helper<T>::value, this, detail::timer_create_helper<T>::callback);
  }

  ~timer_base() {
    // NOTE: No configurability in blocking time, since we
    xTimerDelete(handle_, os_wrapper::max_ticks().ticks);
  }

  bool start(time_ticks time_out = os_wrapper::max_ticks()) {
    return xTimerStart(handle_, time_out.ticks) == pdTRUE;
  }

  bool stop(time_ticks time_out = os_wrapper::max_ticks()) {
    return xTimerStop(handle_, time_out.ticks) == pdTRUE;
  }

  bool change_period(time_ticks new_period, time_ticks time_out = os_wrapper::max_ticks()) {
    return xTimerChangePeriod(handle_, new_period.ticks, time_out.ticks) == pdTRUE;
  }

  bool reset(time_ticks time_out = os_wrapper::max_ticks()) {
    return xTimerReset(handle_, time_out.ticks) == pdTRUE;
  }

  [[nodiscard]] bool is_active() const {
    return xTimerIsTimerActive(handle_) == pdTRUE;
  }

  [[nodiscard]] const char* get_name() const {
    return pcTimerGetName(handle_);
  }

  [[nodiscard]] time_ticks get_period() const {
    return {xTimerGetPeriod(handle_)};
  }

  [[nodiscard]] time_ticks get_expiry_time() const {
    return {xTimerGetExpiryTime(handle_)};
  }

  bool start_from_isr(bool *is_higher_priority_task_woken) {
    return from_isr_impl_caller(&timer_base::start_from_isr_impl, is_higher_priority_task_woken);
  }

  bool stop_from_isr(bool *is_higher_priority_task_woken) {
    return from_isr_impl_caller(&timer_base::stop_from_isr_impl, is_higher_priority_task_woken);
  }

  bool change_period_from_isr(time_ticks new_period, bool *is_higher_priority_task_woken) {
    return from_isr_impl_caller(&timer_base::change_timer_from_isr_impl,
                                is_higher_priority_task_woken,
                                new_period.ticks);
  }

  bool reset_from_isr(bool *is_higher_priority_task_woken) {
    return from_isr_impl_caller(&timer_base::reset_from_isr_impl, is_higher_priority_task_woken);
  }
};
}

enum class timer_start_policy {
  auto_start, deferred
};

class one_shot_timer final : public detail::timer_base {
  friend void detail::one_shot_timer_callback(TimerHandle_t handle);
 private:
  constexpr static const char* kDefaultName{"UnNamedOneShot"};
 public:
  one_shot_timer(timer_start_policy policy, time_ticks ticks, std::function<void()> callback, const char* name = kDefaultName) :
      detail::timer_base(name, ticks, std::move(callback), detail::timer_create_helper<detail::timer_type::one_shot>()) {
    if (policy == timer_start_policy::auto_start) {
      start();
    }
  }

  one_shot_timer(time_ticks ticks, std::function<void()> callback, const char* name = kDefaultName) :
      one_shot_timer(timer_start_policy::auto_start, ticks, std::move(callback), name) {
  }
};

class periodic_timer final : public detail::timer_base {
  friend void detail::periodic_timer_callback(TimerHandle_t handle);
 private:
  constexpr static const char* kDefaultName{"UnNamedPeriodic"};
 public:
  periodic_timer(timer_start_policy policy, time_ticks ticks, std::function<void()> callback, const char* name = kDefaultName) :
      detail::timer_base(name, ticks, std::move(callback), detail::timer_create_helper<detail::timer_type::periodic>()) {
    if (policy == timer_start_policy::auto_start) {
      start();
    }
  }

  periodic_timer(time_ticks ticks, std::function<void()> callback, const char* name = kDefaultName) :
      periodic_timer(timer_start_policy::auto_start, ticks, std::move(callback), name) {
  }
};
}
#endif
