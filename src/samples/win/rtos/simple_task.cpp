#include "utils/os_wrapper/task.hpp"
#include "utils/os_wrapper/queue.hpp"
#include "utils/streams/io_device_wrapper.hpp"
#include "utils/streams/io_stream.hpp"
#include "utils/ports/pc/console_device.hpp"
#include "samples/simple_task.hpp"

void vAssertCalled( unsigned long ulLine, const char * const pcFileName )
{
}


int main() {
  // Create the output stream
  console_device console;
  auto io_device = make_io_device(&console);
  io_stream io_stream{&io_device};

  io_stream << io_stream::yellow << "Basic task test\n" << io_stream::reset;

  simple_task t(&io_stream);

  os_wrapper::start_scheduler();
}
