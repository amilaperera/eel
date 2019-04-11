#pragma once
#include <cstddef>
#include "util/types.hh"

namespace eel::util {

class IODeviceInterface;

class IOStream {
 private:
  // private type aliasing
  using Manipulator = IOStream& (*)(IOStream&);

 public:
  explicit IOStream(IODeviceInterface *io_device);
  void print(const char *fmt, ...);
  // stream insertion
  IOStream& operator<<(const char *str);
  IOStream& operator<<(char ch);
  IOStream& operator<<(bool b);
  IOStream& operator<<(Manipulator manip);

  // stream extraction
  IOStream& operator>>(char &ch);

  // Manipulators
  static IOStream& endl(IOStream &ios);
  static IOStream& err(IOStream &ios);
  static IOStream& noerr(IOStream &ios);
  static IOStream& warn(IOStream &ios);
  static IOStream& nowarn(IOStream &ios);
  static IOStream& info(IOStream &ios);
  static IOStream& noinfo(IOStream &ios);
  static IOStream& debug(IOStream &ios);
  static IOStream& nodebug(IOStream &ios);
  static IOStream& trace(IOStream &ios);
  static IOStream& notrace(IOStream &ios);
  static IOStream& reset(IOStream &ios);

 private:
  IODeviceInterface *io_device_;
  static constexpr std::size_t kMaxPrintBufferSize{128 + 1};
};

}
