//
// Created by amila.perera on 17/07/2020.
//

#pragma once

#include "ots/FreeRTOS/Source/include/FreeRTOS.h"
#include "ots/FreeRTOS/Source/include/stream_buffer.h"
#include "utils/os_wrapper/ticks.hpp"
#include "utils/os_wrapper/free_rtos_types.hpp"
#include "utils/preprocessor.hpp"

namespace eel::utils::os_wrapper {

struct buffer_view {
 private:
  const void* data;
  size_t size;

 public:
  template <typename T>
  explicit buffer_view(const T& item) : data(&item), size(sizeof(item)) {}
  explicit buffer_view(const char* s) : data(s), size(std::strlen(s)) {}
  buffer_view(const void* d, size_t sz) : data(d), size(sz) {}

  [[nodiscard]] const void* get_data() const {
    return data;
  }
  [[nodiscard]] size_t get_size() const {
    return size;
  }
};

namespace detail {
struct basic_stream_buffer_base {
 protected:
  StreamBufferHandle_t handle_;

  basic_stream_buffer_base(size_t sz, size_t trigger_bytes) : handle_{nullptr} {
    handle_ = xStreamBufferCreate(sz, trigger_bytes);
  }
  ~basic_stream_buffer_base() {
    vStreamBufferDelete(handle_);
  }
};
}

template <typename T>
class basic_stream_buffer final : public detail::basic_stream_buffer_base {
 private:
  const size_t item_size = sizeof(T);

 public:
  basic_stream_buffer(size_t sz, size_t trigger_items) : detail::basic_stream_buffer_base(sz, item_size* trigger_items) {
  };

  size_t send_one(T const& item, time_ticks time_out) {
    return xStreamBufferSend(handle_, &item, item_size, time_out.ticks);
  }
};

template <>
class basic_stream_buffer<void> final : public detail::basic_stream_buffer_base {
 private:
 public:
  basic_stream_buffer(size_t sz, size_t trigger_items) : detail::basic_stream_buffer_base(sz, trigger_items) {}

  size_t send(const buffer_view& bview, time_ticks time_out) {
    return xStreamBufferSend(handle_, bview.get_data(), bview.get_size(), time_out.ticks);
  }
};

using stream_buffer = basic_stream_buffer<void>;
}


