//
// Created by amila.perera on 29/05/2020.
//

#pragma once

#include "utils/os_wrapper/task.hpp"
#include "utils/streams/io_device_wrapper.hpp"
#include "utils/streams/io_stream.hpp"

using namespace eel::utils;
using namespace eel::utils::os_wrapper::literals;

struct simple_task : os_wrapper::task {
  explicit simple_task(io_stream *s) : task{os_wrapper::priority(10),
                                            os_wrapper::stack_size(os_wrapper::word_size(1024)),
                                            "init task"}, stream_{s} {
  }
  void run() override {
    *stream_ << io_stream::yellow << "\r\nSingle task program\r\n" << io_stream::reset;
    for (;;) {
      *stream_ << io_stream::cyan << "Task running\r\n" << io_stream::reset;
      os_wrapper::task_delay(1_s);
      stream_->print("tick count: %d\r\n", os_wrapper::tick_count().ticks);
      *stream_ << io_stream::green << "Task running\r\n" << io_stream::reset;
      os_wrapper::task_delay(1_s);
      stream_->print("tick count: %d\r\n", os_wrapper::tick_count().ticks);
    }
  }
 private:
  io_stream *stream_;
};

