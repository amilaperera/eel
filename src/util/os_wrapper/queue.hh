#pragma once

#include "ots/FreeRTOS/Source/include/FreeRTOS.h"
#include "ots/FreeRTOS/Source/include/queue.h"
#include <type_traits>

namespace eel::util::os_wrapper {
namespace detail {

class QueueCommon {
  public:
  UBaseType_t messages_waiting() const {
    return uxQueueMessagesWaiting(handle_);
  }
  UBaseType_t messages_waiting_from_isr() const {
    return uxQueueMessagesWaitingFromISR(handle_);
  }
  UBaseType_t spaces_available() const {
    return uxQueueSpacesAvailable(handle_);
  }
  void reset() {
    xQueueReset(handle_);
  }
 protected:
  QueueCommon() : handle_{} {}
  QueueHandle_t handle_;
};

template <typename ItemType>
struct QueueBase : public QueueCommon {
  protected:
  QueueBase() : QueueCommon{} {}
  public:
  bool send_to_back(const ItemType& item, TickType_t ticks_to_wait = max_ticks()) {
    return xQueueSendToBack(handle_, &item, ticks_to_wait) == pdTRUE;
  }
  bool send_to_front(const ItemType& item, TickType_t ticks_to_wait = max_ticks()) {
    return xQueueSendToFront(handle_, &item, ticks_to_wait) == pdTRUE;
  }
  bool receive(ItemType* item, TickType_t ticks_to_wait = max_ticks()) {
    return xQueueReceive(handle_, item, ticks_to_wait) == pdTRUE;
  }
  bool send_to_back_from_isr(const ItemType& item, bool* is_higher_priority_task_woken) {
    UBaseType_t is_woken{pdFALSE};
    auto ret = xQueueSendToBackFromISR(handle_, &item, is_higher_priority_task_woken);
    *is_higher_priority_task_woken = (is_woken == pdTRUE);
    return ret == pdPASS;
  }
  bool send_to_front_from_isr(const ItemType& item, bool* is_higher_priority_task_woken) {
    UBaseType_t is_woken{pdFALSE};
    auto ret = xQueueSendToFrontFromISR(handle_, &item, &is_woken);
    *is_higher_priority_task_woken = (is_woken == pdTRUE);
    return ret == pdPASS;
  }
  bool over_write(const ItemType& item) {
    return xQueueOverwrite(handle_, &item) == pdPASS;
  }
  bool over_write_from_isr(const ItemType& item, bool *is_higher_priority_task_woken) {
    UBaseType_t is_woken{pdFALSE};
    auto ret = xQueueOverwriteFromISR(handle_, &item, &is_woken) == pdPASS;
    *is_higher_priority_task_woken = (is_woken == pdTRUE);
    return ret == pdPASS;
  }
};
}

template <typename ItemType, size_t Size>
class Queue : public detail::QueueBase<ItemType> {
  public:
  static_assert(std::is_trivially_copyable_v<ItemType>, "ItemType must be trivially copyable");
  Queue() : QueueBase{} {
    // TODO: configSUPPORT_DYNAMIC_ALLOCATION must be set to 1
    // return should be hooked to assert
    handle_ = xQueueCreate(Size, sizeof(ItemType));
  }
  ~Queue() {
    vQueueDelete(handle_);
  }
};

}
