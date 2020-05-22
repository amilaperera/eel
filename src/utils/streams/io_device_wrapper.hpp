#pragma once
#include "utils/streams/io_device_interface.hpp"

namespace eel::utils {

template <typename T>
class IODeviceWrapper : public io_device_interface {
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
auto make_io_device(T *device) {
  return eel::utils::IODeviceWrapper<T>(device);
}


}
