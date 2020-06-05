#pragma once

#include <cstring>
#include "ots/FreeRTOS/Source/include/FreeRTOS.h"
#include "ots/FreeRTOS/Source/include/task.h"
#include "utils/os_wrapper/ticks.hpp"
#include "utils/os_wrapper/free_rtos_types.hpp"
#include <utility>
#include "utils/preprocessor.hpp"

#ifdef __cplusplus
extern "C" {
#endif
void task_func(void *arg);
#ifdef __cplusplus
}
#endif

namespace eel::utils::os_wrapper {

inline void start_scheduler() {
  vTaskStartScheduler();
}

#ifdef INCLUDE_vTaskDelay
inline void task_delay(time_ticks t) {
  vTaskDelay(t.ticks);
}
#endif

#ifdef INCLUDE_vTaskDelayUntil
inline void task_delay_until(time_ticks *prev_wakeup_time, time_ticks time_increment) {
  vTaskDelayUntil(&(prev_wakeup_time->ticks), time_increment.ticks);
}
#endif

#ifdef INCLUDE_vTaskSuspend
inline void self_suspend() {
  // self-suspend
  vTaskSuspend(0);
}
#endif

#ifdef INCLUDE_uxTaskPriorityGet
inline priority get_self_priority() {
  // get priority of the calling task
  return priority{ uxTaskPriorityGet(0) };
}
#endif

#ifdef INCLUDE_vTaskPrioritySet
inline void set_self_priority(const priority& new_value) {
  // set priority of the calling task
  vTaskPrioritySet(0, new_value.value());
}
#endif

class task {
public:
  using native_handle_type = TaskHandle_t;

 private:
  native_handle_type handle_;

 public:
  friend void ::task_func(void *);

  explicit task(priority prio,
      stack_size stack_depth = stack_size(configMINIMAL_STACK_SIZE),
      const char *name = "UnNamedTask") :
      handle_{} {
    // TODO: hook the return value to an assert
    xTaskCreate(task_func, name, stack_depth.value(), this, prio.value(), &handle_);
  }

  virtual ~task() {
#ifdef INCLUDE_vTaskDelete
    if (handle_) {
      vTaskDelete(handle_);
    }
#endif
  }

  DELETE_COPY_CTOR(task);
  DELETE_COPY_ASSIGNMENT(task);

  // move operations
  task(task&& other) noexcept : handle_(std::exchange(other.handle_, nullptr)) {}
  task& operator=(task&& other) noexcept {
    if (this != &other) {
      handle_ = std::exchange(other.handle_, nullptr);
    }
    return *this;
  }

  virtual void run() = 0;

  [[nodiscard]] native_handle_type& native_handle() {
    return handle_;
  }

#ifdef INCLUDE_vTaskSuspend
  void suspend() {
    vTaskSuspend(handle_);
  }

  void resume() {
    vTaskResume(handle_);
  }
#endif

#ifdef INCLUDE_uxTaskPriorityGet
  [[nodiscard]]
  priority get_priority() const {
    return priority{uxTaskPriorityGet(handle_)};
  }
#endif

#ifdef INCLUDE_vTaskPrioritySet
  void set_priority(priority new_value) {
    vTaskPrioritySet(handle_, new_value.value());
  }
#endif

  [[nodiscard]]
  char* name() const {
    return pcTaskGetName(handle_);
  }

#ifdef INCLUDE_xTaskAbortDelay
  bool abort_delay() {
    return xTaskAbortDelay(handle_) == pdPASS;
  }
#endif

#if defined(INCLUDE_vTaskSuspend) && defined(INCLUDE_xTaskResumeFromISR)
  bool resume_from_isr() {
    return xTaskResumeFromISR(handle_) == pdPASS;
  }
#endif
};

}
