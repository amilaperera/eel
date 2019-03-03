#pragma once
#include <utility>
#include <type_traits>

namespace eel {
namespace util {

template <typename T1, typename T2>
struct Pair {
  T1 first;
  T2 second;

  constexpr Pair() : first{}, second{} {}
  explicit constexpr Pair(T1 const& t1, T2 const &t2) : first{t1}, second{t2} {
  }

  template <typename U1, typename U2>
  explicit constexpr Pair(Pair<U1, U2> const& p) : first{p.first}, second{p.second} {
  }

  constexpr Pair& operator=(Pair const& p) {
    first = p.first;
    second = p.second;
    return *this;
  }
};

template <typename T1, typename T2>
constexpr bool operator==(Pair<T1, T2> const& x, Pair<T1, T2> const& y) {
  return x.first == y.first && x.second == y.second;
}

template <typename T1, typename T2>
constexpr bool operator!=(Pair<T1, T2> const& x, Pair<T1, T2> const& y) {
  return !(x == y);
}

template <typename T1, typename T2>
constexpr auto MakePair(T1&& t1, T2&& t2) {
  return Pair<std::decay_t<T1>, std::decay_t<T2>>(std::forward<T1>(t1), std::forward<T2>(t2));
}

}
}

