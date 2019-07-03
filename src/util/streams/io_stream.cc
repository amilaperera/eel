//
// Created by Amila Perera on 12/03/2019.
//
#include "util/streams/io_stream.hh"
#include "util/streams/io_device_interface.hh"
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

IOStream& IOStream::Endl(IOStream &ios) {
  ios << kCrLf;
  return ios;
}

IOStream& IOStream::Red(IOStream& ios) {
  ios << kColorRed;
  return ios;
}

IOStream& IOStream::Green(IOStream& ios) {
  ios << kColorGreen;
  return ios;
}

IOStream& IOStream::Yellow(IOStream& ios) {
  ios << kColorYellow;
  return ios;
}

IOStream& IOStream::Blue(IOStream& ios) {
  ios << kColorBlue;
  return ios;
}

IOStream& IOStream::Magenta(IOStream& ios) {
  ios << kColorMagenta;
  return ios;
}

IOStream& IOStream::Cyan(IOStream& ios) {
  ios << kColorCyan;
  return ios;
}

IOStream& IOStream::White(IOStream& ios) {
  ios << kColorWhite;
  return ios;
}

IOStream& IOStream::Reset(IOStream &ios) {
  ios << kColorReset;
  return ios;
}

IOStream& IOStream::Err(IOStream &ios) { return Red(ios); }
IOStream& IOStream::NoErr(IOStream& ios) { return Reset(ios); }
IOStream& IOStream::Warn(IOStream &ios) { return Yellow(ios); }
IOStream& IOStream::NoWarn(IOStream &ios) { return Reset(ios); }
IOStream& IOStream::Info(IOStream& ios) { return Cyan(ios); }
IOStream& IOStream::NoInfo(IOStream &ios) { return Reset(ios); }
IOStream& IOStream::Debug(IOStream& ios) { return Green(ios); }
IOStream& IOStream::NoDebug(IOStream &ios) { return Reset(ios); }
IOStream& IOStream::Trace(IOStream &ios) { return White(ios); }
IOStream& IOStream::NoTrace(IOStream &ios) { return Reset(ios); }

}
