#pragma once

#include <cstring>
#include "ots/FreeRTOS/Source/include/FreeRTOS.h"
#include "ots/FreeRTOS/Source/include/task.h"
#include "utils/os_wrapper/ticks.hpp"
#include "utils/os_wrapper/free_rtos_types.hpp"

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
inline void task_delay(tick_t t) {
  vTaskDelay(t);
}
#endif

#ifdef INCLUDE_vTaskDelayUntil
inline void task_delay_until(tick_t *prev_wakeup_time, tick_t time_increment) {
  vTaskDelayUntil(prev_wakeup_time, time_increment);
}
#endif

#ifdef INCLUDE_vTaskSuspend
inline void self_suspend() {
  // self-suspend
  vTaskSuspend(0);
}
#endif

#ifdef INCLUDE_uxTaskPriorityGet
inline base_t get_self_priority() {
  // get priority of the calling task
  return uxTaskPriorityGet(0);
}
#endif

#ifdef INCLUDE_vTaskPrioritySet
inline void set_self_priority(base_t new_value) {
  // set priority of the calling task
  vTaskPrioritySet(0, new_value);
}
#endif

class task {
 public:
  friend void ::task_func(void *);
  template <typename StackType>
  explicit task(priority prio,
      stack_size<StackType> stack_depth = stack_size(word_size(configMINIMAL_STACK_SIZE)),
      const char *name = "UnNamedTask") :
      handle_{} {
    // TODO: hook the return value to an assert
    xTaskCreate(task_func, name, stack_depth.size(), this, prio.get_priority(), &handle_);
  }

  ~task() {
#ifdef INCLUDE_vTaskDelete
    if (handle_) {
      vTaskDelete(handle_);
    }
#endif
  }

  task(const task&) = delete;
  task& operator=(const task&) = delete;
  // TODO: can make it movable

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
  base_t priority() const {
    return uxTaskPriorityGet(handle_);
  }
#endif

#ifdef INCLUDE_vTaskPrioritySet
  void set_priority(base_t new_value) {
    vTaskPrioritySet(handle_, new_value);
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

  virtual void run() = 0;

 private:
  TaskHandle_t handle_;
};

}
