//
// Created by amila.perera on 25/06/2020.
//

#pragma once

#include "utils/os_wrapper/task.hpp"
#include "utils/streams/io_device_wrapper.hpp"
#include "utils/streams/io_stream.hpp"
#include "utils/os_wrapper/semaphore.hpp"
#include "utils/os_wrapper/timer.hpp"

using namespace eel::utils;
using namespace eel::utils::os_wrapper::literals;

struct task_1 : os_wrapper::task {
 private:
  struct blob_t {
    int a;
    int b;
  } blob_{0, 0};
  os_wrapper::periodic_timer timer_;
  os_wrapper::mutex m_;
  io_stream& stream_;

 public:
  explicit task_1(io_stream& stream) : task{os_wrapper::priority(10)}, timer_(1_s, [this]{this->on_timer_expired();}), stream_(stream) {
  }
  void run() override {
    for (;;) {
      os_wrapper::task_delay(os_wrapper::max_ticks());
    }
  }

  void on_timer_expired() {
    os_wrapper::lock_guard lk(m_);
    stream_ << io_stream::debug << "1 sec timer expired (a: " << blob_.a << ", b: " << blob_.b << ")\r\n" << io_stream::no_debug;
    blob_.a++;
    blob_.b++;
  }

  void on_other_periodic_timer_expiration() {
    os_wrapper::lock_guard lk(m_);
    stream_ << io_stream::warn << "periodic expired (a: " << blob_.a << ", b: " << blob_.b << ")\r\n" << io_stream::no_warn;
    blob_.a++;
    blob_.b++;
  }

  void on_other_one_shot_timer_expiration() {
    os_wrapper::lock_guard lk(m_);
    stream_ << io_stream::error << "One shot timer expired (a: " << blob_.a << ", b: " << blob_.b << ")\r\n" << io_stream::no_error;
    blob_.a++;
    blob_.b++;
  }
};

struct task_2 : os_wrapper::task {
 private:
  task_1& owner_;
  os_wrapper::one_shot_timer o_timer_;
  os_wrapper::periodic_timer p_timer_;
 public:
  explicit task_2(task_1& owner) : task{os_wrapper::priority(11)}, owner_(owner),
                                   o_timer_(3_s, [this]{ this->on_one_shot_timer_expired();}),
                                   p_timer_(os_wrapper::timer_start_policy::deferred, 6_s, [this]{ this->on_periodic_timer_expired();}) {
  }
  void run() override {
    for (;;) {
      os_wrapper::task_delay(os_wrapper::max_ticks());
    }
  }

  void on_periodic_timer_expired() {
    owner_.on_other_periodic_timer_expiration();
    o_timer_.reset();
  }

  void on_one_shot_timer_expired() {
    // since p_timer start_policy is set to deferred,
    // we start the timer upon first one-shot timer
    // expiration
    if (!p_timer_.is_active()) {
      p_timer_.start();
    }
    owner_.on_other_one_shot_timer_expiration();
  }
};

