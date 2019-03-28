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

void IOStream::print(const char *fmt, ...) {
  char buffer[kMaxPrintBufferSize] = {0};
  va_list argp;
  va_start(argp, fmt);
  if (std::vsnprintf(buffer, kMaxPrintBufferSize, fmt, argp) > 0) {
    io_device_->write(reinterpret_cast<const U8 *>(buffer), std::strlen(buffer));
  }
  va_end(argp);
}

IOStream& IOStream::operator<<(const char *str) {
  io_device_->write(reinterpret_cast<const U8 *>(str), std::strlen(str));
  return *this;
}

IOStream& IOStream::operator<<(char ch) {
  io_device_->write(reinterpret_cast<const U8 *>(&ch), 1);
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
  io_device_->read(reinterpret_cast<U8 *>(&ch), 1);
  return *this;
}

IOStream& IOStream::endl(IOStream &ios) {
  ios << "\r\n";
  return ios;
}

IOStream& IOStream::err(IOStream &ios) {
  ios << "\033[31m";
  return ios;
}

IOStream& IOStream::noerr(IOStream &ios) {
  return reset(ios);
}

IOStream& IOStream::warn(IOStream &ios) {
  ios << "\033[33m";
  return ios;
}

IOStream& IOStream::nowarn(IOStream &ios) {
  return reset(ios);
}

IOStream& IOStream::info(IOStream &ios) {
  ios << "\033[36m";
  return ios;
}

IOStream& IOStream::noinfo(IOStream &ios) {
  return reset(ios);
}

IOStream& IOStream::debug(IOStream &ios) {
  ios << "";
  return ios;
}

IOStream& IOStream::nodebug(IOStream &ios) {
  return reset(ios);
}

IOStream& IOStream::trace(IOStream &ios) {
  ios << "";
  return ios;
}

IOStream& IOStream::notrace(IOStream &ios) {
  return reset(ios);
}

IOStream& IOStream::reset(IOStream &ios) {
  ios << "\033[0m";
  return ios;
}

}
}
