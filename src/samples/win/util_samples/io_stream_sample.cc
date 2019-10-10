//
// Created by Amila Perera on 1/07/2019.
//

#include "util/streams/io_device_wrapper.hh"
#include "util/streams/io_stream.hh"
#include "util/ports/pc/console_device.hh"

using namespace eel::util;

int main() {
  ConsoleDevice console;
  auto io_device = make_io_device(&console);
  IOStream io_stream{&io_device};
  io_stream << "Test Program\n";
  io_stream << IOStream::info << "This is an Info level log\n" << IOStream::no_info;
  io_stream << IOStream::error << "This is an Error level log\n" << IOStream::no_error;
  io_stream << IOStream::warn << "This is " << IOStream::trace
            << "a multi-colored " << IOStream::info << "log " << IOStream::error
            << "line\n" << IOStream::trace << "Have a good day\n" << IOStream::debug << "Bye!!!\n" << IOStream::reset;

  io_stream << IOStream::red << "This is a red line\n";
  io_stream << IOStream::blue << "This is a blue line\n";
  io_stream << IOStream::yellow << "This is a yellow line\n";
  io_stream << IOStream::green << "This is a green line\n";
  io_stream << IOStream::cyan << "This is a cyan line\n";
  io_stream << IOStream::magenta << "This is a magenta line\n";
  io_stream << IOStream::white << "This is a white line\n";
  return 0;
}
