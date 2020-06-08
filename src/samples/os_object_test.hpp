//
// Created by amila.perera on 29/05/2020.
//

#pragma once

#include "utils/os_wrapper/task.hpp"
#include "utils/os_wrapper/queue.hpp"
#include "utils/streams/io_device_wrapper.hpp"
#include "utils/streams/io_stream.hpp"
#include <type_traits>

using namespace eel::utils;
using namespace eel::utils::os_wrapper::literals;

inline void test_task_object(io_stream* s);
inline void test_queue_object(io_stream* s);
inline void test_queue_contained_type(io_stream* s);

struct test_task : public os_wrapper::task {
  explicit test_task(io_stream *s) : os_wrapper::task(os_wrapper::priority(10), 156_ws, "test task"), stream(s) {}
  void run() override {
    *stream << io_stream::yellow << "OS object test\r\n" << io_stream::reset;
    test_task_object(stream);
    test_queue_object(stream);
    test_queue_contained_type(stream);
    for (;;) {
      os_wrapper::task_delay(30_s);
    }
  }
private:
  io_stream* stream;
};

struct derived_task : public os_wrapper::task {
  derived_task() : os_wrapper::task(os_wrapper::priority(3)) {}
  void run() override {
  }
};

inline void test_task_object(io_stream* s) {
  s->print("\r\n---- task test ----\r\n");
  static_assert(std::is_default_constructible_v<derived_task>, "Task is not default constructible");
  static_assert(!std::is_copy_constructible_v<derived_task>, "Task is not copy constructible");
  static_assert(!std::is_copy_assignable_v<derived_task>, "Task is not copy assignable");
  static_assert(std::is_move_constructible_v<derived_task>, "Task is move constructible");
  static_assert(std::is_move_assignable_v<derived_task>, "Task is not move assignable");

  derived_task t;
  s->print("t before moving: handle = %p\r\n", t.native_handle());
  auto another_t = std::move(t);
  s->print("t after moving: handle = %p\r\n", t.native_handle());
  s->print("another_t: handle = %p\r\n", another_t.native_handle());
}

inline void test_queue_object(io_stream* s) {
  s->print("\r\n---- queue test ----\r\n");
  using q_type = os_wrapper::queue<int, 5>;
  static_assert(std::is_default_constructible_v<q_type>, "Queue should be default constructible");
  static_assert(!std::is_copy_constructible_v<q_type>, "Queue is not copy constructible");
  static_assert(!std::is_copy_assignable_v<q_type>, "Queue is not copy assignable");
  static_assert(std::is_move_constructible_v<q_type>, "Queue is not move constructible");
  static_assert(std::is_move_assignable_v<q_type>, "Queue is not move assignable");

  q_type q;
  s->print("q before moving: handle = %p\r\n", q.native_handle());
  s->print("q spaces available: %d\r\n", q.spaces_available());
  q.send_to_back(1);
  q.send_to_back(2);
  s->print("q spaces available: %d\r\n", q.spaces_available());

  auto new_q(std::move(q));
  s->print("q after moving: source handle = %p\r\n", q.native_handle());
  s->print("new_ after moving: dest handle = %p\r\n", new_q.native_handle());
  s->print("new_q spaces available: %d\r\n", new_q.spaces_available());

  q_type another_q;
  another_q.send_to_back(34);
  another_q.send_to_back(34);
  another_q.send_to_back(34);
  another_q.send_to_back(34);

  s->print("another_q spaces available: %d\r\n", another_q.spaces_available());
  another_q = std::move(new_q);
  s->print("another_q spaces available after move assignment from new_q: %d\r\n", another_q.spaces_available());
}

#include <string>
#include <array>
#include <variant>

struct my_trivial_type_1 {
  int a;
  char b[64];
  float f;
};

struct my_trivial_type_2 {
  int a;
  std::array<char, 50> b;
  float f;
};


inline void test_queue_contained_type(io_stream* s) {
  s->print("\r\n---- queue contained type test ----\r\n");
  using q_type_trivial_1 = os_wrapper::queue<int, 5>;
  q_type_trivial_1 q1;
  using q_type_trivial_2 = os_wrapper::queue<char, 5>;
  q_type_trivial_2 q2;
  using q_type_trivial_3 = os_wrapper::queue<double, 5>;
  q_type_trivial_3 q3;
  using q_type_trivial_4 = os_wrapper::queue<float, 5>;
  q_type_trivial_4 q4;

  static_assert(std::is_trivially_copyable_v<my_trivial_type_1>, "my_trivial_type_1 is not trivially copyable");
  os_wrapper::queue<my_trivial_type_1, 5> q5;

  static_assert(std::is_trivially_copyable_v<my_trivial_type_2>, "my_trivial_type_2 is not trivially copyable");
  os_wrapper::queue<my_trivial_type_2, 5> q6;

  using type_q7 = std::variant<my_trivial_type_1, my_trivial_type_2>;
  static_assert(std::is_trivially_copyable_v<type_q7>, "my_trivial_type_2 is not trivially copyable");
  os_wrapper::queue<type_q7, 5> q7;
}

