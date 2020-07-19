//
//

#pragma once

#include "utils/os_wrapper/task.hpp"
#include "utils/streams/io_device_wrapper.hpp"
#include "utils/streams/io_stream.hpp"
#include "utils/os_wrapper/semaphore.hpp"
#include "utils/os_wrapper/timer.hpp"
#include "utils/os_wrapper/stream_buffer.hpp"

using namespace eel::utils;
using namespace eel::utils::os_wrapper::literals;

struct task_1 : os_wrapper::task {
 private:
  struct blob_t {
    int a;
    int b;
  };
  io_stream& stream_;
  os_wrapper::basic_stream_buffer<blob_t> stream_buffer_;

 public:
  explicit task_1(io_stream& stream) : task{os_wrapper::priority(10)}, stream_(stream), stream_buffer_(10) {
  }
  void run() override {
    for (;;) {
      blob_t item{};
      auto ret = stream_buffer_.receive_one(item);
      if (ret == sizeof(item)) {
        stream_ << io_stream::info << "a: " << item.a << ", b: " << item.b << io_stream::no_info << "\r\n";
      }
    }
  }

  size_t send(int a, int b) {
    return stream_buffer_.send_one(blob_t{a, b});
  }

};

struct task_2 : os_wrapper::task {
 private:
  task_1& owner_;
  os_wrapper::periodic_timer p_timer_;
  int count{};
 public:
  explicit task_2(task_1& owner) : task{os_wrapper::priority(11)}, owner_(owner), p_timer_{1_s, [this]{update();}} {
  }
  void run() override {
    for (;;) {
      os_wrapper::task_delay(os_wrapper::max_ticks());
    }
  }

  void update() {
    owner_.send(count++, static_cast<int>(os_wrapper::tick_count().ticks));
  }

};

