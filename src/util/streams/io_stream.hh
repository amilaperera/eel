#pragma once
#include <cstddef>
#include "util/types.hh"

namespace eel::util {

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
  static IOStream& Endl(IOStream &ios);

  static IOStream& Red(IOStream& ios);
  static IOStream& Green(IOStream& ios);
  static IOStream& Yellow(IOStream& ios);
  static IOStream& Blue(IOStream& ios);
  static IOStream& Magenta(IOStream& ios);
  static IOStream& Cyan(IOStream& ios);
  static IOStream& White(IOStream& ios);

  static IOStream& Err(IOStream &ios);
  static IOStream& NoErr(IOStream &ios);
  static IOStream& Warn(IOStream &ios);
  static IOStream& NoWarn(IOStream &ios);
  static IOStream& Info(IOStream &ios);
  static IOStream& NoInfo(IOStream &ios);
  static IOStream& Debug(IOStream &ios);
  static IOStream& NoDebug(IOStream &ios);
  static IOStream& Trace(IOStream &ios);
  static IOStream& NoTrace(IOStream &ios);

  static IOStream& Reset(IOStream &ios);
};

}
