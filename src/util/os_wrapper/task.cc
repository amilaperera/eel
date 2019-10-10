//
// Created by Amila Perera on 9/10/2019.
//

#include "util/os_wrapper/task.hh"

#ifdef __cplusplus
extern "C" {
#endif
void task_func(void *arg) {
  auto *task = reinterpret_cast<eel::util::os_wrapper::Task *>(arg);
  task->run();
}
#ifdef __cplusplus
}
#endif

