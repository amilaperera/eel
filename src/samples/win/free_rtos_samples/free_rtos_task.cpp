#include "utils/os_wrapper/task.hpp"
#include "utils/os_wrapper/queue.hpp"
#include "utils/streams/io_device_wrapper.hpp"
#include "utils/streams/io_stream.hpp"
#include "utils/ports/pc/console_device.hpp"

#ifdef __cplusplus
extern "C" {
#endif
void vAssertCalled( unsigned long ulLine, const char * const pcFileName )
{
}
#ifdef __cplusplus
}
#endif

using namespace eel::utils;
using namespace eel::utils::os_wrapper::literals;

using my_queue = os_wrapper::queue<size_t, 10>;

struct sending_task : os_wrapper::task {
  explicit sending_task(io_stream *s, my_queue *queue) : task{100, 10, "sending_task"}, stream_{s}, queue_{queue} {}
  void run() override {
    auto last_wakeup_time = os_wrapper::tick_count();
    for (;;) {
      os_wrapper::task_delay_until(&last_wakeup_time, 1_s);
      *stream_ << "Sending....\n";
      queue_->send_to_back(last_wakeup_time, 10_ms);
    }
  }
 private:
  io_stream *stream_;
  my_queue *queue_;
};

struct recv_task : os_wrapper::task {
  explicit recv_task(io_stream *s, my_queue *queue) : task{100, 11, "recv_task"}, stream_{s}, queue_{queue} {}
  void run() override {
    for (;;) {
      my_queue::item_type item{};
      queue_->receive(&item);
      stream_->print("Item received by Receiving task: %u\n", item);
    }
  }
 private:
  io_stream *stream_;
  my_queue *queue_;
};

int main() {
  // Create the output stream
  console_device console;
  auto io_device = make_io_device(&console);
  io_stream io_stream{&io_device};

  io_stream << io_stream::yellow << "Basic task test\n" << io_stream::reset;

  // Create a queue to be shared between 2 tasks
  my_queue queue;

  // Sending task
  sending_task sending_task{&io_stream, &queue};

  // Receiving task
  recv_task receiving_task{&io_stream, &queue};

  os_wrapper::start_scheduler();
}
