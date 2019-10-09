#include <iostream>
#include "util/os/task.hh"

#ifdef __cplusplus
extern "C" {
#endif
void vAssertCalled( unsigned long ulLine, const char * const pcFileName )
{
}
#ifdef __cplusplus
}
#endif

using namespace eel::util;

struct MyTask : os::TaskInterface {
  MyTask() : TaskInterface{100, 100, "MyTask"} {}
  void run() override {
    for (;;) {
      std::cout << "Task\n";
    }
  }
};

int main() {
  MyTask task;
  task.start();
  os::start();
}