//
// Created by Amila Perera on 12/03/2019.
//
#include "utils/streams/io_stream.hpp"
#include "utils/streams/io_device_interface.hpp"
#include <cstring>
#include <cstdarg>
#include <cstdio>
#include <algorithm>

namespace eel::utils {

  io_stream::io_stream(io_device_interface* io_device) : io_device_{ io_device }, buffer_{0}, buffer_write_idx_{} {
}

void io_stream::print(const char *fmt, ...) {
  char buffer[kMaxPrintBufferSize] = {0};
  va_list argp;
  va_start(argp, fmt);
  if (std::vsnprintf(buffer, kMaxPrintBufferSize, fmt, argp) > 0) {
    io_device_->write(buffer, std::strlen(buffer));
  }
  va_end(argp);
}

io_stream& io_stream::operator<<(const char *str) {
  auto len = std::min(std::strlen(str), kMaxPrintBufferSize - 1);
  std::copy(str, str + len, buffer_ + buffer_write_idx_);
  buffer_write_idx_ += len;
  flush_if_needed();
  return *this;
}

io_stream& io_stream::operator<<(char ch) {
  if (buffer_write_idx_ < kMaxPrintBufferSize - 1) {
    buffer_[buffer_write_idx_] = ch;
  }
  flush_if_needed();
  return *this;
}

io_stream& io_stream::operator<<(bool b) {
  *this << (b ? "true" : "false");
  return *this;
}

io_stream& io_stream::operator<<(Manipulator manip) {
  return manip(*this);
}

io_stream& io_stream::operator>>(char &ch) {
  io_device_->read(&ch, 1);
  return *this;
}

io_stream& io_stream::endl(io_stream &ios) {
  ios << kCrLf;
  return ios;
}

io_stream& io_stream::red(io_stream& ios) {
  ios << kColorRed;
  return ios;
}

io_stream& io_stream::green(io_stream& ios) {
  ios << kColorGreen;
  return ios;
}

io_stream& io_stream::yellow(io_stream& ios) {
  ios << kColorYellow;
  return ios;
}

io_stream& io_stream::blue(io_stream& ios) {
  ios << kColorBlue;
  return ios;
}

io_stream& io_stream::magenta(io_stream& ios) {
  ios << kColorMagenta;
  return ios;
}

io_stream& io_stream::cyan(io_stream& ios) {
  ios << kColorCyan;
  return ios;
}

io_stream& io_stream::white(io_stream& ios) {
  ios << kColorWhite;
  return ios;
}

io_stream& io_stream::reset(io_stream &ios) {
  ios << kColorReset;
  return ios;
}

io_stream& io_stream::error(io_stream &ios) { return red(ios); }
io_stream& io_stream::no_error(io_stream& ios) { return reset(ios); }
io_stream& io_stream::warn(io_stream &ios) { return yellow(ios); }
io_stream& io_stream::no_warn(io_stream &ios) { return reset(ios); }
io_stream& io_stream::info(io_stream& ios) { return cyan(ios); }
io_stream& io_stream::no_info(io_stream &ios) { return reset(ios); }
io_stream& io_stream::debug(io_stream& ios) { return green(ios); }
io_stream& io_stream::no_debug(io_stream &ios) { return reset(ios); }
io_stream& io_stream::trace(io_stream &ios) { return white(ios); }
io_stream& io_stream::no_trace(io_stream &ios) { return reset(ios); }

// private impl
inline bool io_stream::is_buffer_ended_with_crlf() {
  return buffer_write_idx_ > 1 && (buffer_[buffer_write_idx_ - 2] == '\r' && buffer_[buffer_write_idx_ - 1] == '\n');
}

inline void io_stream::flush_if_needed() {
  if (buffer_write_idx_ >= kMaxPrintBufferSize - 1 || is_buffer_ended_with_crlf()) {
    io_device_->write(buffer_, std::strlen(buffer_));
    std::fill_n(buffer_, kMaxPrintBufferSize, 0x00);
    buffer_write_idx_ = 0;
  }
}

}
