#include "hal/hal.hpp"
#include "hal/uart.hpp"
#include "utils/os_wrapper/task.hpp"
#include "utils/streams/io_device_wrapper.hpp"
#include "utils/streams/io_stream.hpp"

using namespace eel::utils;
using namespace eel::utils::os_wrapper::literals;

struct init_task : os_wrapper::task {
  explicit init_task(io_stream *s) : task{10, 1024 * 20, "init task"}, stream_{s} {
  }
  void run() override {
    *stream_ << io_stream::yellow << "\r\nSingle task program\r\n" << io_stream::reset;
    for (;;) {
      *stream_ << io_stream::cyan << "Task running\r\n";
      os_wrapper::task_delay(1_s);
      *stream_ << io_stream::green << "Task running\r\n";
      os_wrapper::task_delay(1_s);
    }
  }
 private:
  io_stream *stream_;
};

int main() {
  eel::hal::init();
  eel::hal::uart serial(eel::hal::pin_name::D8, eel::hal::pin_name::D9, 115200);
  auto io_device = make_io_device(&serial);
  // Create the output stream
  io_stream io_stream{&io_device};

  // Create task
  init_task t(&io_stream);

  // Start scheduler
  os_wrapper::start_scheduler();
}
