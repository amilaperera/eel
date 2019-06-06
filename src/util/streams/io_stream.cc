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
  ios << "\r\n";
  return ios;
}

IOStream& IOStream::Err(IOStream &ios) {
  ios << "\033[31m";
  return ios;
}

IOStream& IOStream::NoErr(IOStream &ios) {
  return Reset(ios);
}

IOStream& IOStream::Warn(IOStream &ios) {
  ios << "\033[33m";
  return ios;
}

IOStream& IOStream::NoWarn(IOStream &ios) {
  return Reset(ios);
}

IOStream& IOStream::Info(IOStream &ios) {
  ios << "\033[36m";
  return ios;
}

IOStream& IOStream::NoInfo(IOStream &ios) {
  return Reset(ios);
}

IOStream& IOStream::Debug(IOStream &ios) {
  ios << "";
  return ios;
}

IOStream& IOStream::NoDebug(IOStream &ios) {
  return Reset(ios);
}

IOStream& IOStream::Trace(IOStream &ios) {
  ios << "";
  return ios;
}

IOStream& IOStream::NoTrace(IOStream &ios) {
  return Reset(ios);
}

IOStream& IOStream::Reset(IOStream &ios) {
  ios << "\033[0m";
  return ios;
}

}
