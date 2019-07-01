//
// Created by Amila Perera on 1/07/2019.
//

#include "util/streams/io_device_interface.hh"
#include "util/streams/io_stream.hh"
#include <iostream>

struct ConsoleDevice : eel::util::IODeviceInterface {
  void Write(const eel::util::U8 *buffer, eel::util::U32 size) override {
    std::cout.write(reinterpret_cast<const char *>(buffer),
                    static_cast<std::streamsize>(size));
  }
  void Read(eel::util::U8 *buffer, eel::util::U32 size) override {
    std::cin.read(reinterpret_cast<char *>(buffer),
                    static_cast<std::streamsize>(size));
  }
};

using namespace eel::util;

int main() {
  ConsoleDevice console;
  IOStream io_stream{&console};
  io_stream << "Test Program\n";
  io_stream << IOStream::Info << "This is an Info level log\n" << IOStream::NoInfo;
  io_stream << IOStream::Err << "This is an Error level log\n" << IOStream::NoErr;
  io_stream << IOStream::Warn << "This is " << IOStream::Trace
            << "a multi-colored " << IOStream::Info << "log " << IOStream::Err
            << "line\n" << IOStream::Reset;
  return 0;
}
