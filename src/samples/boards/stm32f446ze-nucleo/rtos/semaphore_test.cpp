#include "hal/hal.hpp"
#include "hal/uart.hpp"
#include "utils/os_wrapper/task.hpp"
#include "utils/streams/io_device_wrapper.hpp"
#include "utils/streams/io_stream.hpp"
#include "samples/semaphore_test.hpp"

using namespace eel::utils;
using namespace eel::utils::os_wrapper::literals;

int main() {
  eel::hal::init();

  eel::hal::uart serial(eel::hal::pin_name::D8, eel::hal::pin_name::D9, 115200);
  auto io_device = make_io_device(&serial);

  io_stream io{&io_device};

  task_1 t1(io);
  task_2 t2(t1);

  os_wrapper::start_scheduler();
}
