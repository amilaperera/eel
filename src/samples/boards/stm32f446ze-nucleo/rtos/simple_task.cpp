#include "hal/hal.hpp"
#include "hal/uart.hpp"
#include "samples/simple_task.hpp"

using namespace eel::utils;
using namespace eel::utils::os_wrapper::literals;

int main() {
  eel::hal::init();

  eel::hal::uart serial(eel::hal::pin_name::D8, eel::hal::pin_name::D9, 115200);
  auto io_device = make_io_device(&serial);

  // Create the output stream
  io_stream io_stream{&io_device};

  // Create task
  simple_task t(&io_stream);

  // Start scheduler
  os_wrapper::start_scheduler();
}
