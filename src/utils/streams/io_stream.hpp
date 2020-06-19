#pragma once
#include <cstddef>
#include <cstdarg>
#include "utils/types.hpp"
#include <algorithm>

namespace eel::utils {
namespace detail {
struct append_crlf_tag {};
static const append_crlf_tag append_crlf;

template <size_t N> 
struct stream_buffer {
private:
  char buffer_[N + 1]; // always nul-terminated
  size_t write_idx_;
public:
  stream_buffer() : buffer_{0}, write_idx_(0) {}
  void copy(detail::append_crlf_tag, const char* fmt, va_list args) {
    auto n = std::vsnprintf(buffer_ + write_idx_, N - write_idx_, fmt, args);
    if (n > 0) {
      write_idx_ += n;
    }
    buffer_[write_idx_++] = '\r';
    buffer_[write_idx_++] = '\n';
  }
  void copy(const char* fmt, va_list args) {
    auto n = std::vsnprintf(buffer_ + write_idx_, N - write_idx_, fmt, args);
    if (n > 0) {
      write_idx_ += n;
    }
  }
  void copy(const char* s) {
    auto copy_len = std::min(std::strlen(s), N - write_idx_);
    std::copy(s, s + copy_len, buffer_ + write_idx_);
    write_idx_ += copy_len;
  }
  void copy(char ch) {
    if (N - write_idx_ > 0) {
      buffer_[write_idx_++] = ch;
    }
  }
  void reset() {
    std::fill_n(buffer_, write_idx_, 0);
    write_idx_ = 0;
  }
  size_t free_space() const {
    return N - write_idx_;
  }
  bool buffer_full() const {
    return write_idx_ == N;
  }
  bool ended_with_crlf() const {
    return write_idx_ > 1 && buffer_[write_idx_ - 1] == '\n' && buffer_[write_idx_ - 2] == '\r';
  }
  const char* buffer() const {
    return buffer_;
  }
  size_t size() const {
    return write_idx_;
  }
};
}

class io_device_interface;

class io_stream {
 private:
  static constexpr std::size_t kMaxPrintBufferSize{128 + 1};
  // private type aliasing
  using Manipulator = io_stream& (*)(io_stream&);

  io_device_interface *io_device_;
  detail::stream_buffer<128> stream_buffer_;

  static constexpr const char* kCrLf = "\r\n";
  static constexpr const char* kColorRed = "\033[31m";
  static constexpr const char* kColorGreen = "\033[32m";
  static constexpr const char* kColorYellow = "\033[33m";
  static constexpr const char* kColorBlue = "\033[34m";
  static constexpr const char* kColorMagenta = "\033[35m";
  static constexpr const char* kColorCyan = "\033[36m";
  static constexpr const char* kColorWhite = "\033[37m";
  static constexpr const char* kColorReset = "\033[0m";
  void flush_if_needed();

 public:
  explicit io_stream(io_device_interface *io_device);
  void print(const char* fmt, ...);
  void print_ln(const char* fmt, ...);
  // stream insertion
  io_stream& operator<<(const char *str);
  io_stream& operator<<(char ch);
  io_stream& operator<<(bool b);
  io_stream& operator<<(int v);
  io_stream& operator<<(Manipulator manip);

  // stream extraction
  io_stream& operator>>(char &ch);

  // Manipulators
  static io_stream& endl(io_stream &ios);

  static io_stream& red(io_stream& ios);
  static io_stream& green(io_stream& ios);
  static io_stream& yellow(io_stream& ios);
  static io_stream& blue(io_stream& ios);
  static io_stream& magenta(io_stream& ios);
  static io_stream& cyan(io_stream& ios);
  static io_stream& white(io_stream& ios);

  static io_stream& error(io_stream &ios);
  static io_stream& no_error(io_stream &ios);
  static io_stream& warn(io_stream &ios);
  static io_stream& no_warn(io_stream &ios);
  static io_stream& info(io_stream &ios);
  static io_stream& no_info(io_stream &ios);
  static io_stream& debug(io_stream &ios);
  static io_stream& no_debug(io_stream &ios);
  static io_stream& trace(io_stream &ios);
  static io_stream& no_trace(io_stream &ios);

  static io_stream& reset(io_stream &ios);
};

}
