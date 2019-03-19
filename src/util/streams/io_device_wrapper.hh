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
  void Read(U8 *buffer, U32 size) override {
    device_->Read(buffer, size);
  }

 private:
  T *device_;
};

template <typename T>
auto MakeIODeviceWrapper(T *device) {
  return eel::util::IODeviceWrapper<T>(device);
}


}
}

