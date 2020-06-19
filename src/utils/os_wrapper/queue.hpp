#pragma once

#include "ots/FreeRTOS/Source/include/FreeRTOS.h"
#include "ots/FreeRTOS/Source/include/queue.h"
#include <type_traits>
#include "utils/os_wrapper/free_rtos_types.hpp"
#include <utility>
#include "utils/preprocessor.hpp"

namespace eel::utils::os_wrapper {
namespace detail {

class queue_common {
 public:
  using native_handle_type = QueueHandle_t;
  [[nodiscard]]
  base_t messages_waiting() const {
    return uxQueueMessagesWaiting(handle_);
  }
  [[nodiscard]]
  base_t messages_waiting_from_isr() const {
    return uxQueueMessagesWaitingFromISR(handle_);
  }
  [[nodiscard]]
  base_t spaces_available() const {
    return uxQueueSpacesAvailable(handle_);
  }
  void reset() {
    xQueueReset(handle_);
  }

  [[nodiscard]] native_handle_type& native_handle() {
    return handle_;
  }

  queue_common(const queue_common&) = delete;
  queue_common& operator=(const queue_common&) = delete;
 protected:
  queue_common() : handle_{} {}
  queue_common(queue_common&& other) noexcept : handle_{std::exchange(other.handle_, nullptr)} {}
  queue_common& operator=(queue_common&& other) noexcept {
    if (this != &other) {
      handle_ = std::exchange(other.handle_, nullptr);
    }
    return *this;
  }

  native_handle_type handle_;
};

template <typename ItemType>
struct queue_base : public queue_common {
 public:
  using item_type = ItemType;

  bool send_to_back(const ItemType& item, time_ticks ticks_to_wait = max_ticks()) {
    return xQueueSendToBack(handle_, &item, ticks_to_wait.ticks) == pdTRUE;
  }

  bool send_to_front(const ItemType& item, time_ticks ticks_to_wait = max_ticks()) {
    return xQueueSendToFront(handle_, &item, ticks_to_wait.ticks) == pdTRUE;
  }

  bool receive(ItemType* item, time_ticks ticks_to_wait = max_ticks()) {
    return xQueueReceive(handle_, item, ticks_to_wait.ticks) == pdTRUE;
  }

  bool receive_from_isr(ItemType* item, bool* is_task_woken) {
    os_wrapper::base_t task_woken = pdFALSE;
    auto ret = xQueueReceiveFromISR(handle_, item, &task_woken);
    *is_task_woken = task_woken == pdTRUE;
    return ret == pdTRUE;
  }

  bool send_to_back_from_isr(const ItemType& item, bool* is_higher_priority_task_woken) {
    base_t is_woken{pdFALSE};
    auto ret = xQueueSendToBackFromISR(handle_, &item, is_higher_priority_task_woken);
    *is_higher_priority_task_woken = (is_woken == pdTRUE);
    return ret == pdPASS;
  }

  bool send_to_front_from_isr(const ItemType& item, bool* is_higher_priority_task_woken) {
    base_t is_woken{pdFALSE};
    auto ret = xQueueSendToFrontFromISR(handle_, &item, &is_woken);
    *is_higher_priority_task_woken = (is_woken == pdTRUE);
    return ret == pdPASS;
  }

  bool over_write(const ItemType& item) {
    return xQueueOverwrite(handle_, &item) == pdPASS;
  }

  bool over_write_from_isr(const ItemType& item, bool *is_higher_priority_task_woken) {
    base_t is_woken{pdFALSE};
    auto ret = xQueueOverwriteFromISR(handle_, &item, &is_woken) == pdPASS;
    *is_higher_priority_task_woken = (is_woken == pdTRUE);
    return ret == pdPASS;
  }

  bool peek(ItemType* item, time_ticks ticks_to_wait = max_ticks()) {
    return xQueuePeek(handle_, item, ticks_to_wait.ticks) == pdTRUE;
  }

  bool peek_from_isr(ItemType* item) {
    return xQueuePeekFromISR(handle_, item) == pdTRUE;
  }

 protected:
  queue_base() : queue_common{} {}
};
}

template <typename ItemType, size_t Size>
class queue final : public detail::queue_base<ItemType> {
  public:
  static_assert(std::is_trivially_copyable_v<ItemType>, "ItemType must be trivially copyable");
  queue() : detail::queue_base<ItemType>{} {
    // TODO: configSUPPORT_DYNAMIC_ALLOCATION must be set to 1
    // return should be hooked to assert
    this->handle_ = xQueueCreate(Size, sizeof(ItemType));
  }
  ~queue() {
    if (this->handle_) {
      vQueueDelete(this->handle_);
    }
  }
  DELETE_COPY_CTOR(queue);
  DELETE_COPY_ASSIGNMENT(queue);

  queue(queue&& other) noexcept = default;
  queue& operator=(queue&& other) noexcept = default;
};

}
