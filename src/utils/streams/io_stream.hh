#pragma once
#include <cstddef>
#include "utils/types.hh"

namespace eel::utils {

class io_device_interface;

class io_stream {
 private:
  // private type aliasing
  using Manipulator = io_stream& (*)(io_stream&);
  io_device_interface *io_device_;
  static constexpr std::size_t kMaxPrintBufferSize{128 + 1};
  static constexpr const char* kCrLf = "\r\n";
  static constexpr const char* kColorRed = "\033[31m";
  static constexpr const char* kColorGreen = "\033[32m";
  static constexpr const char* kColorYellow = "\033[33m";
  static constexpr const char* kColorBlue = "\033[34m";
  static constexpr const char* kColorMagenta = "\033[35m";
  static constexpr const char* kColorCyan = "\033[36m";
  static constexpr const char* kColorWhite = "\033[37m";
  static constexpr const char* kColorReset = "\033[0m";

 public:
  explicit io_stream(io_device_interface *io_device);
  void print(const char *fmt, ...);
  // stream insertion
  io_stream& operator<<(const char *str);
  io_stream& operator<<(char ch);
  io_stream& operator<<(bool b);
  io_stream& operator<<(Manipulator manip);

  // stream extraction
  io_stream& operator>>(char &ch);

  // Manipulators
  static io_stream& endl(io_stream &ios);

  static io_stream& red(io_stream& ios);
  static io_stream& green(io_stream& ios);
  static io_stream& yellow(io_stream& ios);
  static io_stream& blue(io_stream& ios);
  static io_stream& magenta(io_stream& ios);
  static io_stream& cyan(io_stream& ios);
  static io_stream& white(io_stream& ios);

  static io_stream& error(io_stream &ios);
  static io_stream& no_error(io_stream &ios);
  static io_stream& warn(io_stream &ios);
  static io_stream& no_warn(io_stream &ios);
  static io_stream& info(io_stream &ios);
  static io_stream& no_info(io_stream &ios);
  static io_stream& debug(io_stream &ios);
  static io_stream& no_debug(io_stream &ios);
  static io_stream& trace(io_stream &ios);
  static io_stream& no_trace(io_stream &ios);

  static io_stream& reset(io_stream &ios);
};

}
