#include "utils/os_wrapper/task.hpp"
#include "utils/os_wrapper/queue.hpp"
#include "utils/streams/io_device_wrapper.hpp"
#include "utils/streams/io_stream.hpp"
#include "utils/ports/pc/console_device.hpp"
#include "samples/sender_receiver_tasks.hpp"

void vAssertCalled( unsigned long ulLine, const char * const pcFileName )
{
}

using namespace eel::utils;
using namespace eel::utils::os_wrapper::literals;

int main() {
  // Create the output stream
  console_device console;
  auto io_device = make_io_device(&console);
  io_stream stream{&io_device};

  // Create tasks
  receiver_task receiver(&stream);
  sender_task sender(&receiver);

  // Start scheduler
  os_wrapper::start_scheduler();
}
