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

template <size_t N>
struct buffer_wrapper {
  unsigned char data[N];
  buffer_wrapper() : data{0} {}
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

 public:
  [[nodiscard]] size_t spaces_available() const {
    return xStreamBufferSpacesAvailable(handle_);
  }

  [[nodiscard]] bool is_empty() const {
    return xStreamBufferIsEmpty(handle_) == pdTRUE;
  }

  [[nodiscard]] bool is_full() const {
    return xStreamBufferIsFull(handle_) == pdTRUE;
  }

  bool reset() {
    return xStreamBufferReset(handle_) == pdTRUE;
  }
};
}

template <typename ItemType>
class basic_stream_buffer final : public detail::basic_stream_buffer_base {
  static_assert(std::is_trivially_copyable_v<ItemType>, "ItemType must be trivially copyable");

 private:
  const size_t item_size;

 public:
  using type = ItemType;
  explicit basic_stream_buffer(size_t sz, size_t trigger_items = 1) : detail::basic_stream_buffer_base(sz, trigger_items * sizeof(ItemType)), item_size(sizeof(ItemType)) {
  };

  size_t send_one(ItemType const& item, time_ticks timeout = os_wrapper::max_ticks()) {
    return xStreamBufferSend(handle_, &item, item_size, timeout.ticks);
  }

  size_t receive_one(ItemType& item, time_ticks timeout = os_wrapper::max_ticks()) {
    return xStreamBufferReceive(handle_, &item, item_size, timeout.ticks);
  }

  size_t send_one_from_isr(ItemType const& item, bool* is_higher_priority_task_woken) {
    s_base_t is_woken{pdFALSE};
    auto ret = xStreamBufferSendFromISR(handle_, &item, item_size, &is_woken);
    *is_higher_priority_task_woken = (is_woken == pdTRUE);
    return ret;
  }

  size_t receive_one_from_isr(ItemType& item, bool* is_higher_priority_task_woken) {
    s_base_t is_woken{pdFALSE};
    auto ret = xStreamBufferReceiveFromISR(handle_, &item, item_size, &is_woken);
    *is_higher_priority_task_woken = (is_woken == pdTRUE);
    return ret;
  }
};

template <>
class basic_stream_buffer<void> final : public detail::basic_stream_buffer_base {
 public:
  basic_stream_buffer(size_t sz, size_t trigger_items) : detail::basic_stream_buffer_base(sz, trigger_items) {}

  size_t send(const buffer_view& buffer, time_ticks timeout = os_wrapper::max_ticks()) {
    return xStreamBufferSend(handle_, buffer.get_data(), buffer.get_size(), timeout.ticks);
  }

  template <size_t N>
  size_t receive(buffer_wrapper<N>& buffer_wrapper, time_ticks timeout = os_wrapper::max_ticks()) {
   return xStreamBufferReceive(handle_, buffer_wrapper.data, N, timeout.ticks);
 }
};

using stream_buffer = basic_stream_buffer<void>;
}


