//
// Created by Amila Perera on 1/07/2019.
//

#include "utils/streams/io_device_wrapper.hpp"
#include "utils/streams/io_stream.hpp"
#include "utils/ports/pc/console_device.hpp"

using namespace eel::utils;

int main() {
  console_device console;
  auto io_device = make_io_device(&console);
  io_stream io_stream{&io_device};
  io_stream << "Test Program\r\n";
  io_stream << io_stream::info << "This is an Info level log\r\n" << io_stream::no_info;
  io_stream << io_stream::error << "This is an Error level log\r\n" << io_stream::no_error;
  io_stream << io_stream::warn << "This is " << io_stream::trace
            << "a multi-colored " << io_stream::info << "log " << io_stream::error
            << "line\r\n" << io_stream::trace << "Have a good day\r\n" << io_stream::debug << "Bye!!!\r\n" << io_stream::reset;

  io_stream << io_stream::red << "This is a red line\r\n";
  io_stream << io_stream::blue << "This is a blue line\r\n";
  io_stream << io_stream::yellow << "This is a yellow line\r\n";
  io_stream << io_stream::green << "This is a green line\r\n";
  io_stream << io_stream::cyan << "This is a cyan line\r\n";
  io_stream << io_stream::magenta << "This is a magenta line\r\n";
  io_stream << io_stream::white << "This is a white line\r\n";
  io_stream << "This is a string with int " << 34 << io_stream::endl;
  io_stream.print("This is a string with some numerals %d %c", 34, 'a');
  io_stream << io_stream::endl;
  io_stream.print_ln("This line should automatically flushed %d %d %c 0x%02x", 234, 432, 'b', 88);
  return 0;
}
