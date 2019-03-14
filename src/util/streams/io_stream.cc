//
// Created by Amila Perera on 12/03/2019.
//
#include "util/streams/io_stream.hh"
#include "util/streams/io_device_interface.hh"
#include <cstring>
#include <cstdarg>
#include <cstdio>

namespace eel {
namespace util {

IOStream::IOStream(IODeviceInterface *io_device) : io_device_{io_device} {
}

void IOStream::Print(const char *fmt, ...) {
  char buffer[kMaxPrintBufferSize] = {0};
  va_list argp;
  va_start(argp, fmt);
  if (std::vsnprintf(buffer, kMaxPrintBufferSize, fmt, argp) > 0) {
    io_device_->Write(reinterpret_cast<const U8 *>(buffer), std::strlen(buffer));
  }
}

IOStream& IOStream::operator<<(const char *str) {
  io_device_->Write(reinterpret_cast<const U8 *>(str), std::strlen(str));
  return *this;
}

IOStream& IOStream::operator<<(bool b) {
  *this << (b ? "true" : "false");
  return *this;
}

IOStream& IOStream::operator<<(Manipulator manip) {
  return manip(*this);
}

IOStream& IOStream::Endl(IOStream &ios) {
  ios << "\r\n";
  return ios;
}

}
}
