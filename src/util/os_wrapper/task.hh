#pragma once

#include <cstring>
#include "ots/FreeRTOS/Source/include/FreeRTOS.h"
#include "ots/FreeRTOS/Source/include/task.h"
#include "util/os_wrapper/ticks.hh"

#ifdef __cplusplus
extern "C" {
#endif
void task_func(void *arg);
#ifdef __cplusplus
}
#endif

namespace eel::util::os_wrapper {

inline void start_scheduler() {
  vTaskStartScheduler();
}

#ifdef INCLUDE_vTaskDelay
inline void task_delay(TickType_t t) {
  vTaskDelay(t);
}
#endif

#ifdef INCLUDE_vTaskDelayUntil
inline void task_delay_until(TickType_t *prev_wakeup_time, TickType_t time_increment) {
  vTaskDelayUntil(prev_wakeup_time, time_increment);
}
#endif

#ifdef INCLUDE_vTaskSuspend
inline void suspend() {
  // self-suspend
  vTaskSuspend(0);
}
#endif

#ifdef INCLUDE_uxTaskPriorityGet
inline UBaseType_t priority() {
  // get priority of the calling task
  return uxTaskPriorityGet(0);
}
#endif

#ifdef INCLUDE_vTaskPrioritySet
inline void set_priority(UBaseType_t new_value) {
  // set priority of the calling task
  vTaskPrioritySet(0, new_value);
}
#endif

class Task {
 public:
  friend void ::task_func(void *);

  explicit Task(UBaseType_t priority,
      unsigned short stack_depth = configMINIMAL_STACK_SIZE,
      const char *n = "UnNamedTask") :
      task_handle_{},
      init_priority_{priority},
      stack_depth_{stack_depth},
      name_{}  {
    std::strncpy(name_, n, sizeof(name_) - 1);
  }

  ~Task() {
#ifdef INCLUDE_vTaskDelete
    if (task_handle_) {
      vTaskDelete(task_handle_);
    }
#endif
  }

  Task(const Task&) = delete;
  Task& operator=(const Task&) = delete;

  bool start() {
    return xTaskCreate(task_func, name_, stack_depth_, this, init_priority_, &task_handle_) == pdPASS;
  }

#ifdef INCLUDE_vTaskSuspend
  void suspend() {
    vTaskSuspend(task_handle_);
  }

  void resume() {
    vTaskResume(task_handle_);
  }
#endif

#ifdef INCLUDE_uxTaskPriorityGet
  UBaseType_t priority() const {
    uxTaskPriorityGet(task_handle_);
  }
#endif

#ifdef INCLUDE_vTaskPrioritySet
  void set_priority(UBaseType_t new_value) {
    vTaskPrioritySet(task_handle_, new_value);
  }
#endif

#ifdef INCLUDE_xTaskAbortDelay
  bool abort_delay() {
    return xTaskAbortDelay(task_handle_) == pdPASS;
  }
#endif

#if defined(INCLUDE_vTaskSuspend) && defined(INCLUDE_xTaskResumeFromISR)
  bool resume_from_isr() {
    return xTaskResumeFromISR(task_handle_) == pdPASS;
  }
#endif

  virtual void run() = 0;

 private:
  TaskHandle_t task_handle_;
  UBaseType_t init_priority_;
  unsigned short stack_depth_;
  char name_[configMAX_TASK_NAME_LEN];
};

}
