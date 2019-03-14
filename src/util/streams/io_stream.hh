#pragma once
#include <cstddef>
#include "util/types.hh"

namespace eel {
namespace util {

class IODeviceInterface;

class IOStream {
 private:
  // private type aliasing
  using Manipulator = IOStream& (*)(IOStream&);

 public:
  explicit IOStream(IODeviceInterface *io_device);
  void Print(const char *fmt, ...);
  IOStream& operator<<(const char *str);
  IOStream& operator<<(bool b);
  IOStream& operator<<(Manipulator manip);

  // Manipulators
  static IOStream& Endl(IOStream &ios);

 private:
  IODeviceInterface *io_device_;
  static constexpr std::size_t kMaxPrintBufferSize{128 + 1};
};

}
}

