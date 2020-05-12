//
// Created by Amila Perera on 12/03/2019.
//
#include "utils/streams/io_stream.hh"
#include "utils/streams/io_device_interface.hh"
#include <cstring>
#include <cstdarg>
#include <cstdio>

namespace eel::util {

IOStream::IOStream(IODeviceInterface *io_device) : io_device_{io_device} {
}

void IOStream::Print(const char *fmt, ...) {
  char buffer[kMaxPrintBufferSize] = {0};
  va_list argp;
  va_start(argp, fmt);
  if (std::vsnprintf(buffer, kMaxPrintBufferSize, fmt, argp) > 0) {
    io_device_->Write(reinterpret_cast<const U8 *>(buffer), std::strlen(buffer));
  }
  va_end(argp);
}

IOStream& IOStream::operator<<(const char *str) {
  io_device_->Write(reinterpret_cast<const U8 *>(str), std::strlen(str));
  return *this;
}

IOStream& IOStream::operator<<(char ch) {
  io_device_->Write(reinterpret_cast<const U8 *>(&ch), 1);
  return *this;
}

IOStream& IOStream::operator<<(bool b) {
  *this << (b ? "true" : "false");
  return *this;
}

IOStream& IOStream::operator<<(Manipulator manip) {
  return manip(*this);
}

IOStream& IOStream::operator>>(char &ch) {
  io_device_->Read(reinterpret_cast<U8 *>(&ch), 1);
  return *this;
}

IOStream& IOStream::endl(IOStream &ios) {
  ios << kCrLf;
  return ios;
}

IOStream& IOStream::red(IOStream& ios) {
  ios << kColorRed;
  return ios;
}

IOStream& IOStream::green(IOStream& ios) {
  ios << kColorGreen;
  return ios;
}

IOStream& IOStream::yellow(IOStream& ios) {
  ios << kColorYellow;
  return ios;
}

IOStream& IOStream::blue(IOStream& ios) {
  ios << kColorBlue;
  return ios;
}

IOStream& IOStream::magenta(IOStream& ios) {
  ios << kColorMagenta;
  return ios;
}

IOStream& IOStream::cyan(IOStream& ios) {
  ios << kColorCyan;
  return ios;
}

IOStream& IOStream::white(IOStream& ios) {
  ios << kColorWhite;
  return ios;
}

IOStream& IOStream::reset(IOStream &ios) {
  ios << kColorReset;
  return ios;
}

IOStream& IOStream::error(IOStream &ios) { return red(ios); }
IOStream& IOStream::no_error(IOStream& ios) { return reset(ios); }
IOStream& IOStream::warn(IOStream &ios) { return yellow(ios); }
IOStream& IOStream::no_warn(IOStream &ios) { return reset(ios); }
IOStream& IOStream::info(IOStream& ios) { return cyan(ios); }
IOStream& IOStream::no_info(IOStream &ios) { return reset(ios); }
IOStream& IOStream::debug(IOStream& ios) { return green(ios); }
IOStream& IOStream::no_debug(IOStream &ios) { return reset(ios); }
IOStream& IOStream::trace(IOStream &ios) { return white(ios); }
IOStream& IOStream::no_trace(IOStream &ios) { return reset(ios); }

}
