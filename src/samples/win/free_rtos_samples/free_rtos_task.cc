#include "util/os_wrapper/task.hh"
#include "util/os_wrapper/queue.hh"
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

using MyQueue = os_wrapper::Queue<size_t, 10>;

struct SendingTask : os_wrapper::Task {
  explicit SendingTask(IOStream *s, MyQueue *queue) : Task{100, 10, "SendingTask"}, stream_{s}, queue_{queue} {}
  void run() override {
    auto last_wakeup_time = os_wrapper::tick_count();
    for (;;) {
      os_wrapper::task_delay_until(&last_wakeup_time, 1_s);
      *stream_ << "Sending....\n";
      queue_->send_to_back(last_wakeup_time, 10_ms);
    }
  }
 private:
  IOStream *stream_;
  MyQueue *queue_;
};

struct ReceivingTask : os_wrapper::Task {
  explicit ReceivingTask(IOStream *s, MyQueue *queue) : Task{100, 11, "ReceivingTask"}, stream_{s}, queue_{queue} {}
  void run() override {
    for (;;) {
      MyQueue::Type item{};
      queue_->receive(&item);
      stream_->Print("Item received by Receiving task: %u\n", item);
    }
  }
 private:
  IOStream *stream_;
  MyQueue *queue_;
};

int main() {
  // Create the output stream
  ConsoleDevice console;
  auto io_device = make_io_device(&console);
  IOStream io_stream{&io_device};

  io_stream << IOStream::yellow << "Basic task test\n" << IOStream::reset;

  // Create a queue to be shared between 2 tasks
  MyQueue queue;

  // Sending task
  SendingTask sending_task{&io_stream, &queue};

  // Receiving task
  ReceivingTask receiving_task{&io_stream, &queue};

  os_wrapper::start_scheduler();
}
