#include "util/os_wrapper/task.hh"
#include "util/streams/io_device_wrapper.hh"
#include "util/streams/io_stream.hh"
#include "util/ports/pc/console_device.hh"

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

struct MyTask : os_wrapper::Task {
  explicit MyTask(IOStream *s) : Task{100, 10, "MyTask"}, stream_{s} {}
  void run() override {
    for (;;) {
      *stream_ << IOStream::blue << "Hi from thread\n" << IOStream::reset;
      vTaskDelay(10);
    }
  }
  IOStream *stream_;
};

int main() {
  ConsoleDevice console;
  auto io_device = make_io_device(&console);
  IOStream io_stream{&io_device};

  io_stream << IOStream::yellow << "Basic task test\n" << IOStream::reset;
  MyTask task{&io_stream};
  task.start();
  os_wrapper::start_scheduler();
}