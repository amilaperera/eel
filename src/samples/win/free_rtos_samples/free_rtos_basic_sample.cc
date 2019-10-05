//
// Created by Amila Perera on 1/07/2019.
//

#include "util/streams/io_device_wrapper.hh"
#include "util/streams/io_stream.hh"
#include "util/ports/pc/console_device.hh"
using namespace eel::util;
int main() {
  ConsoleDevice console;
  auto io_device = MakeIODevice(&console);
  IOStream io_stream{&io_device};
  io_stream << "Test Program\n";
  io_stream << IOStream::Info << "This is an Info level log\n" << IOStream::NoInfo;
  io_stream << IOStream::Err << "This is an Error level log\n" << IOStream::NoErr;
  io_stream << IOStream::Warn << "This is " << IOStream::Trace
            << "a multi-colored " << IOStream::Info << "log " << IOStream::Err
            << "line\n" << IOStream::Trace << "Have a good day\n" << IOStream::Debug <<"Bye!!!\n"<< IOStream::Reset;

  io_stream << IOStream::Red << "This is a red line\n";
  io_stream << IOStream::Blue << "This is a blue line\n";
  io_stream << IOStream::Yellow << "This is a yellow line\n";
  io_stream << IOStream::Green << "This is a green line\n";
  io_stream << IOStream::Cyan << "This is a cyan line\n";
  io_stream << IOStream::Magenta << "This is a magenta line\n";
  io_stream << IOStream::White << "This is a white line\n";
  return 0;
}
