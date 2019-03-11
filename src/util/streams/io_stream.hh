#pragma once

namespace eel {
namespace util {

class IODeviceInterface;

class IOStream {
 public:
  explicit IOStream(IODeviceInterface *io_device) : io_device_{io_device} {};
  IOStream& Print(const char *fmt, ...);

 private:
  IODeviceInterface *io_device_;
};

}
}

