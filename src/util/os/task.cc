//
// Created by Amila Perera on 9/10/2019.
//

#include "util/os/task.hh"

#ifdef __cplusplus
extern "C" {
#endif
void task_func(void *arg) {
  auto *task = reinterpret_cast<eel::util::os::TaskInterface *>(arg);
  task->run();
}
#ifdef __cplusplus
}
#endif

