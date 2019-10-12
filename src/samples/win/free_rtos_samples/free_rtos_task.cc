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
using namespace eel::util::os_wrapper::literals;

struct MyTask : os_wrapper::Task {
  explicit MyTask(IOStream *s) : Task{100, 10, "MyTask"}, stream_{s} {}
  void run() override {
    auto last_wakeup_time = os_wrapper::tick_count();
    for (;;) {
      os_wrapper::task_delay_until(&last_wakeup_time, 1_s);
      stream_->Print("tick_count: %u\n", last_wakeup_time);
      *stream_ << IOStream::blue << "Hi from thread\n" << IOStream::reset;
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