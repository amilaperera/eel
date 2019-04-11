#pragma once
#include "util/streams/io_device_interface.hh"

namespace eel::util {

template <typename T>
class IODeviceWrapper : public IODeviceInterface {
 public:
  explicit IODeviceWrapper(T *d) : device_{d} {}
  void write(const U8 *buffer, U32 size) override {
    device_->write(buffer, size);
  }
  void read(U8 *buffer, U32 size) override {
    device_->read(buffer, size);
  }

 private:
  T *device_;
};

template <typename T>
auto make_io_device(T *device) {
  return eel::util::IODeviceWrapper<T>(device);
}


}
