//
// Created by amila.perera on 29/05/2020.
//

#pragma once

#include "utils/os_wrapper/task.hpp"
#include "utils/os_wrapper/queue.hpp"
#include "utils/streams/io_device_wrapper.hpp"
#include "utils/streams/io_stream.hpp"

using namespace eel::utils;
using namespace eel::utils::os_wrapper::literals;

struct receiver_task : os_wrapper::task {
  using QueueType = int;
  explicit receiver_task(io_stream *s) : task{os_wrapper::priority(10), 156_ws, "receiver_task"}, stream_{s}, q_{} {
  }
  void send(const QueueType& item) {
    q_.send_to_back(item);
  }
  void run() override {
    *stream_ << io_stream::yellow << "\r\nReceiver task\r\n" << io_stream::reset;
    for (;;) {
      QueueType item{};
      q_.receive(&item);
      stream_->print("received: %d\r\n", item);
    }
  }
 private:
  io_stream *stream_;
  os_wrapper::queue<QueueType, 5> q_;
};

struct sender_task : os_wrapper::task {
  explicit sender_task(receiver_task* r) : task{os_wrapper::priority(8), 128_ws, "sender_task"}, receiver_{r} {
  }
  void run() override {
    int i = 0;
    for (;;) {
      receiver_->send(i++);
      os_wrapper::task_delay(1_s);
    }
  }
 private:
  receiver_task* receiver_;
};
