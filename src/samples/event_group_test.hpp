//
// Created by amila.perera on 25/06/2020.
//

#pragma once

#include "utils/os_wrapper/task.hpp"
#include "utils/streams/io_device_wrapper.hpp"
#include "utils/streams/io_stream.hpp"
#include "utils/os_wrapper/mailbox.hpp"
#include "utils/os_wrapper/event_group.hpp"

using namespace eel::utils;
using namespace eel::utils::os_wrapper::literals;

struct mailbox_owner_task : os_wrapper::task {
 private:
  os_wrapper::mailbox<int> mb_;

 public:
  explicit mailbox_owner_task() : task{os_wrapper::priority(10)} {
  }
  void run() override {
    int count{};
    for (;;) {
      // updating value @ 2Hz
      mb_.update(count++);
      os_wrapper::task_delay(500_ms);
    }
  }

  [[nodiscard]] int get_value() const {
    int value{};
    mb_.read(&value);
    return value;
  }
};

struct mailbox_reader_task : os_wrapper::task {
 private:
  mailbox_owner_task* mb_owner_;
  io_stream *stream_;
 public:
  explicit mailbox_reader_task(mailbox_owner_task* mb_owner, io_stream *s) : task{os_wrapper::priority(12)}, mb_owner_{mb_owner}, stream_{s} {
  }
  void run() override {
    for (;;) {
      // reading value @ 1Hz
      // Since mailbox always overwrites to a queue of length 1
      // reader should see all the even values i.e. odd values should be skipped
      stream_->println("reading value from mailbox @ 1Hz: %d", mb_owner_->get_value());
      os_wrapper::task_delay(1_s);
    }
  }
};


