#pragma once

#include "ots/FreeRTOS/Source/include/FreeRTOS.h"
#include "ots/FreeRTOS/Source/include/event_groups.h"
#include <type_traits>
#include "utils/os_wrapper/free_rtos_types.hpp"
#include <utility>
#include "utils/preprocessor.hpp"

namespace eel::utils::os_wrapper {
using event_bits_t = EventBits_t;
namespace detail {
}
class event_group {
 private:
  EventGroupHandle_t handle_;
 public:
  event_group() : handle_{} {
    handle_ = xEventGroupCreate();
  }
  event_bits_t set(const event_bits_t bits) {
    return xEventGroupSetBits(handle_, bits);
  }
  event_bits_t clear(const event_bits_t bits) {
    return xEventGroupClearBits(handle_, bits);
  }
  [[nodiscard]] event_bits_t get() const {
    return xEventGroupGetBits(handle_);
  }
  ~event_group() {
    vEventGroupDelete(handle_);
  }
};
}
