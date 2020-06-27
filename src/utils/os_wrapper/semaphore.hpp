#pragma once

#include "ots/FreeRTOS/Source/include/FreeRTOS.h"
#include "ots/FreeRTOS/Source/include/semphr.h"
#include "utils/os_wrapper/ticks.hpp"
#include "utils/os_wrapper/free_rtos_types.hpp"

namespace eel::utils::os_wrapper {
namespace detail {
struct binary_sem_tag {};
struct mutex_tag {};
struct recursive_mutex_tag {};
static const binary_sem_tag binary_sem;
static const mutex_tag mutex;
static const recursive_mutex_tag recursive_mutex;

class semaphore_common_base {
 protected:
  SemaphoreHandle_t handle_;
  explicit semaphore_common_base(const binary_sem_tag&) {
    handle_ = xSemaphoreCreateBinary();
  }
  explicit semaphore_common_base(u_base_t max_count, u_base_t init) {
    handle_ = xSemaphoreCreateCounting(max_count, init);
  }
  explicit semaphore_common_base(const mutex_tag&){
    handle_ = xSemaphoreCreateMutex();
  }
#if (configUSE_RECURSIVE_MUTEXES == 1)
  explicit semaphore_common_base(const recursive_mutex_tag&) {
    handle_ = xSemaphoreCreateRecursiveMutex();
  }
#endif
  ~semaphore_common_base() {
    vSemaphoreDelete(handle_);
  }
};

class semaphore_base : public semaphore_common_base {
 public:
  explicit semaphore_base(const binary_sem_tag& tag) : semaphore_common_base(tag) {}
  explicit semaphore_base(u_base_t max_count, u_base_t init) : semaphore_common_base(max_count, init) {}
  void give() {
    xSemaphoreGive(handle_);
  }
  bool give_from_isr() {
    s_base_t is_woken{pdFALSE};
    xSemaphoreGiveFromISR(handle_, &is_woken);
    return is_woken == pdTRUE;
  }
  void take(os_wrapper::time_ticks ticks_to_wait = os_wrapper::max_ticks()) {
    xSemaphoreTake(handle_, ticks_to_wait.ticks);
  }
  bool take_from_isr() {
    s_base_t is_woken{pdFALSE};
    xSemaphoreTakeFromISR(handle_, &is_woken);
    return is_woken == pdTRUE;
  }
};

class mutex_base : public semaphore_common_base {
 public:
  explicit mutex_base(const mutex_tag& tag) : semaphore_common_base(tag) {}
  explicit mutex_base(const recursive_mutex_tag& tag) : semaphore_common_base(tag) {}
};
}

class binary_semaphore final : public detail::semaphore_base {
 public:
  binary_semaphore() : detail::semaphore_base(detail::binary_sem) {
  }
  [[nodiscard]] bool available() const {
    return uxSemaphoreGetCount(handle_) == 1;
  }
};

class counting_semaphore final : public detail::semaphore_base {
 public:
  counting_semaphore(u_base_t max_count, u_base_t init) : detail::semaphore_base(max_count, init) {
  }
  [[nodiscard]] u_base_t count() const {
    return uxSemaphoreGetCount(handle_);
  }
};

class mutex final : public detail::mutex_base {
 public:
  mutex() : detail::mutex_base(detail::mutex) {}
  void give() {
    xSemaphoreGive(handle_);
  }
  void take(os_wrapper::time_ticks ticks_to_wait = os_wrapper::max_ticks()) {
    xSemaphoreTake(handle_, ticks_to_wait.ticks);
  }
};

#if (configUSE_RECURSIVE_MUTEXES == 1)
class recursive_mutex final : public detail::mutex_base {
 public:
  recursive_mutex() : detail::mutex_base(detail::recursive_mutex) {}
  void give() {
    xSemaphoreGiveRecursive(handle_);
  }
  void take(os_wrapper::time_ticks ticks_to_wait = os_wrapper::max_ticks()) {
    xSemaphoreTakeRecursive(handle_, ticks_to_wait.ticks);
  }
};
#endif

template <typename T>
class lock_guard final {
 private:
  T& m_;
 public:
  explicit lock_guard(T& m) : m_(m) { m_.take(); }
  ~lock_guard() { m_.give(); }
};
}
