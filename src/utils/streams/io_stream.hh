#pragma once
#include <cstddef>
#include "utils/types.hh"

namespace eel::utils {

class IODeviceInterface;

class IOStream {
 private:
  // private type aliasing
  using Manipulator = IOStream& (*)(IOStream&);
  IODeviceInterface *io_device_;
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
  explicit IOStream(IODeviceInterface *io_device);
  void Print(const char *fmt, ...);
  // stream insertion
  IOStream& operator<<(const char *str);
  IOStream& operator<<(char ch);
  IOStream& operator<<(bool b);
  IOStream& operator<<(Manipulator manip);

  // stream extraction
  IOStream& operator>>(char &ch);

  // Manipulators
  static IOStream& endl(IOStream &ios);

  static IOStream& red(IOStream& ios);
  static IOStream& green(IOStream& ios);
  static IOStream& yellow(IOStream& ios);
  static IOStream& blue(IOStream& ios);
  static IOStream& magenta(IOStream& ios);
  static IOStream& cyan(IOStream& ios);
  static IOStream& white(IOStream& ios);

  static IOStream& error(IOStream &ios);
  static IOStream& no_error(IOStream &ios);
  static IOStream& warn(IOStream &ios);
  static IOStream& no_warn(IOStream &ios);
  static IOStream& info(IOStream &ios);
  static IOStream& no_info(IOStream &ios);
  static IOStream& debug(IOStream &ios);
  static IOStream& no_debug(IOStream &ios);
  static IOStream& trace(IOStream &ios);
  static IOStream& no_trace(IOStream &ios);

  static IOStream& reset(IOStream &ios);
};

}
