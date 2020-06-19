#pragma once
#include "utils/os_wrapper/queue.hpp"

namespace eel::utils::os_wrapper {

template <typename ItemType>
class mailbox {
private:
  queue<ItemType, 1> q_;

public:
  mailbox() = default;
  update(ItemType const& item) {
    q_.over_write(item);
  }
  update_from_isr(ItemType const& item) {
    q_.over_write_from_isr(item);
  }
  bool has_value() {
    ItemType item;
    return read(&item, 0);
  }
  bool has_value_from_isr() {
    ItemType item;
    return read_from_isr(&item, 0);
  }
  bool read(ItemType* item, time_ticks ticks_to_wait = max_ticks()) {
    return q_.peek(item, ticks_to_wait);
  }
  bool read_from_isr(ItemType* item) {
    return q_.peek_from_isr(item);
  }
};

}