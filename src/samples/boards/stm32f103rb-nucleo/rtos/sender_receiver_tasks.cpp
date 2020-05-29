#include "hal/hal.hpp"
#include "hal/uart.hpp"
#include "system_clock_config.hpp"
#include "samples/sender_receiver_tasks.hpp"

using namespace eel::utils;
using namespace eel::utils::os_wrapper::literals;

int main() {
  eel::hal::init();
  SystemClock_Config();

  eel::hal::uart serial(eel::hal::pin_name::A2, eel::hal::pin_name::A3, 115200);
  auto io_device = make_io_device(&serial);

  // Create the output stream
  io_stream io_stream{&io_device};

  // Create tasks
  receiver_task receiver(&io_stream);
  sender_task sender(&receiver);

  // Start scheduler
  os_wrapper::start_scheduler();
}
