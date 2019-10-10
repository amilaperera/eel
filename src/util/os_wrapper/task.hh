#pragma once

#include <cstring>
#include "ots/FreeRTOS/Source/include/FreeRTOS.h"
#include "ots/FreeRTOS/Source/include/task.h"

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

class Task {
 public:
  explicit Task(UBaseType_t priority,
      unsigned short stack_depth = configMINIMAL_STACK_SIZE,
      const char *n = "UnNamedTask") :
    task_handle_{},
    priority_{priority},
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
    return xTaskCreate(task_func, name_, stack_depth_, this, priority_, &task_handle_) == pdPASS;
  }

  TaskHandle_t native_handle() {
    return task_handle_;
  }

  virtual void run() = 0;

 private:
  TaskHandle_t task_handle_;
  UBaseType_t priority_;
  unsigned short stack_depth_;
  char name_[configMAX_TASK_NAME_LEN];
};

}
