#include "hal/hal.hpp"
#include "hal/uart.hpp"
#include "utils/os_wrapper/task.hpp"
#include "utils/streams/io_device_wrapper.hpp"
#include "utils/streams/io_stream.hpp"
#include "samples/event_group_test.hpp"

using namespace eel::utils;
using namespace eel::utils::os_wrapper::literals;

int main() {
  eel::hal::init();

  eel::hal::uart serial(eel::hal::pin_name::D8, eel::hal::pin_name::D9, 115200);
  auto io_device = make_io_device(&serial);

  io_stream io{&io_device};

  mailbox_owner_task mb_owner;
  mailbox_reader_task mb_reader_task(&mb_owner, &io);

  os_wrapper::start_scheduler();
}
