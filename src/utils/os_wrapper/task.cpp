//
// Created by Amila Perera on 9/10/2019.
//

#include "utils/os_wrapper/task.hpp"

#ifdef __cplusplus
extern "C" {
#endif
void task_func(void *arg) {
  auto *task = reinterpret_cast<eel::utils::os_wrapper::task *>(arg);
  task->run();
#ifdef INCLUDE_vTaskDelete
  // Ideally Task::run() should never return.
  // If it ever returns here, the task should be deleted here i.e.
  // we don't need to wait until the destructor is called
  vTaskDelete(0); // self deletion
  task->handle_ = {}; // this will avoid issues with subsequent destruction
#endif
}
#ifdef __cplusplus
}
#endif

