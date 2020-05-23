#include "hal/hal.hpp"
#include "hal/uart.hpp"
#include "utils/streams/io_device_wrapper.hpp"
#include "utils/streams/io_stream.hpp"

using namespace eel::utils;
using namespace eel::hal::literals;

int main() {
  eel::hal::init();
  eel::hal::uart serial(eel::hal::pin_name::D8, eel::hal::pin_name::D9, 115200);
  auto io_device = make_io_device(&serial);
  io_stream io_stream{&io_device};
  io_stream << "Test Program" << io_stream::endl;
  for (;;) {
    io_stream << io_stream::info << "This is an info level log\r\n" << io_stream::no_info;
    eel::hal::delay(1_s);
    io_stream << io_stream::error << "This is an error level log\r\n" << io_stream::no_error;
    eel::hal::delay(1_s);
    io_stream << io_stream::warn << "This is " << io_stream::trace
              << "a multi-colored " << io_stream::info << "log " << io_stream::error
              << "line\r\n" << io_stream::trace << "Have a good day\r\n" << io_stream::debug << "Bye!!!\r\n" << io_stream::reset;
    eel::hal::delay(1_s);
    io_stream << io_stream::red << "This is a red line\r\n";
    eel::hal::delay(1_s);
    io_stream << io_stream::blue << "This is a blue line\r\n";
    eel::hal::delay(1_s);
    io_stream << io_stream::yellow << "This is a yellow line\r\n";
    eel::hal::delay(1_s);
    io_stream << io_stream::green << "This is a green line\r\n";
    eel::hal::delay(1_s);
    io_stream << io_stream::cyan << "This is a cyan line\r\n";
    eel::hal::delay(1_s);
    io_stream << io_stream::magenta << "This is a magenta line\r\n";
    eel::hal::delay(1_s);
    io_stream << io_stream::white << "This is a white line\r\n";
    eel::hal::delay(10_s);
  }
  return 0;
}


