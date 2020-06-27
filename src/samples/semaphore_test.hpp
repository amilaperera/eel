//
// Created by amila.perera on 25/06/2020.
//

#pragma once

#include "utils/os_wrapper/task.hpp"
#include "utils/streams/io_device_wrapper.hpp"
#include "utils/streams/io_stream.hpp"
#include "utils/os_wrapper/semaphore.hpp"

using namespace eel::utils;
using namespace eel::utils::os_wrapper::literals;

struct task_1 : os_wrapper::task {
 private:
  struct blob_t {
    int a;
    int b;
  } blob_{0, 0};
  os_wrapper::mutex m_;
  io_stream& stream_;

 public:
  explicit task_1(io_stream& stream) : task{os_wrapper::priority(10)}, stream_(stream) {
  }
  void run() override {
    for (;;) {
      update_blob();
      os_wrapper::task_delay(50_ms);
    }
  }

  void update_blob() {
    os_wrapper::lock_guard lk(m_);
    blob_.a++;
    blob_.b++;
    stream_.println("updated values: (a: %d, b: %d)", blob_.a, blob_.b);
  }
};

struct task_2 : os_wrapper::task {
 private:
  task_1& owner_;
 public:
  explicit task_2(task_1& owner) : task{os_wrapper::priority(11)}, owner_(owner) {
  }
  void run() override {
    for (;;) {
      owner_.update_blob();
      os_wrapper::task_delay(100_ms);
    }
  }
};

