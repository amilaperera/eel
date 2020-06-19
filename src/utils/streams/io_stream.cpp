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

  io_stream::io_stream(io_device_interface* io_device) : io_device_{ io_device }, stream_buffer_() {
}

void io_stream::print(const char *fmt, ...) {
  va_list args;
  va_start (args, fmt);
  stream_buffer_.copy(fmt, args);
  va_end (args);
  flush_if_needed();
}

void io_stream::print_ln(const char* fmt, ...) {
  va_list args;
  va_start (args, fmt);
  stream_buffer_.copy(detail::append_crlf, fmt, args);
  va_end (args);
  flush_if_needed();
}

io_stream& io_stream::operator<<(const char *str) {
  stream_buffer_.copy(str);
  flush_if_needed();
  return *this;
}

io_stream& io_stream::operator<<(char ch) {
  stream_buffer_.copy(ch);
  flush_if_needed();
  return *this;
}

io_stream& io_stream::operator<<(bool b) {
  *this << (b ? "true" : "false");
  return *this;
}

io_stream& io_stream::operator<<(int v) {
  char str[11 + 1]{ 0 };
  itoa(v, str, 10);
  return *this << str;
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
void io_stream::flush_if_needed() {
  if (stream_buffer_.buffer_full() || stream_buffer_.ended_with_crlf()) {
    io_device_->write(stream_buffer_.buffer(), stream_buffer_.size());
    stream_buffer_.reset();
  }
}

}
