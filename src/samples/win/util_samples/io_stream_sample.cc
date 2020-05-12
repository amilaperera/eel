//
// Created by Amila Perera on 1/07/2019.
//

#include "utils/streams/io_device_wrapper.hh"
#include "utils/streams/io_stream.hh"
#include "utils/ports/pc/console_device.hh"

using namespace eel::utils;

int main() {
  console_device console;
  auto io_device = make_io_device(&console);
  io_stream io_stream{&io_device};
  io_stream << "Test Program\n";
  io_stream << io_stream::info << "This is an Info level log\n" << io_stream::no_info;
  io_stream << io_stream::error << "This is an Error level log\n" << io_stream::no_error;
  io_stream << io_stream::warn << "This is " << io_stream::trace
            << "a multi-colored " << io_stream::info << "log " << io_stream::error
            << "line\n" << io_stream::trace << "Have a good day\n" << io_stream::debug << "Bye!!!\n" << io_stream::reset;

  io_stream << io_stream::red << "This is a red line\n";
  io_stream << io_stream::blue << "This is a blue line\n";
  io_stream << io_stream::yellow << "This is a yellow line\n";
  io_stream << io_stream::green << "This is a green line\n";
  io_stream << io_stream::cyan << "This is a cyan line\n";
  io_stream << io_stream::magenta << "This is a magenta line\n";
  io_stream << io_stream::white << "This is a white line\n";
  return 0;
}
