#pragma once
#include "utils/streams/io_device_interface.hpp"

namespace eel::utils {

template <typename T>
class IODeviceWrapper : public io_device_interface {
 public:
  explicit IODeviceWrapper(T *d) : device_{d} {}
  void write(const char *buffer, std::size_t sz) override {
    device_->write(buffer, sz);
  }
  void read(char *buffer, std::size_t sz) override {
    device_->read(buffer, sz);
  }

 private:
  T *device_;
};

template <typename T>
auto make_io_device(T *device) {
  return eel::utils::IODeviceWrapper<T>(device);
}


}
