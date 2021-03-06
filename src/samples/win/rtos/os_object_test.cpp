#include "utils/os_wrapper/task.hpp"
#include "utils/streams/io_device_wrapper.hpp"
#include "utils/streams/io_stream.hpp"
#include "utils/ports/pc/console_device.hpp"
#include "samples/os_object_test.hpp"

void vAssertCalled( unsigned long ulLine, const char * const pcFileName )
{
}

int main() {
  // Create the output stream
  console_device console;
  auto io_device = make_io_device(&console);
  io_stream io{&io_device};

  test_task tt(&io);

  os_wrapper::start_scheduler();
}
