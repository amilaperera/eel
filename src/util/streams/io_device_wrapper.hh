#pragma once
#include "util/streams/io_device_interface.hh"

namespace eel {
namespace util {

template <typename T>
class IODeviceWrapper : public IODeviceInterface {
 public:
  explicit IODeviceWrapper(T *d) : device_{d} {}
  void Write(const U8 *buffer, U32 size) override {
    device_->Write(buffer, size);
  }

 private:
  T *device_;
};

}
}

