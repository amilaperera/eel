#pragma once

namespace eel {
namespace util {

class IODeviceInterface;

class IOStream {
 public:
  explicit IOStream(IODeviceInterface *io_device) : io_device_{io_device} {};

 private:
  IODeviceInterface *io_device_;
};

}
}

