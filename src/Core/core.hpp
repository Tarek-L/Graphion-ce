#include <expected>
#include <fmt/core.h>

#define CONCAT(x, y) x##y

template <typename F> struct Defer {
  F f;
  ~Defer() { f(); }
};

template <typename F> Defer<F> make_defer(F f) { return {f}; }

#define defer(code) auto CONCAT(_defer_, __LINE__) = make_defer([&]() { code; })

template <class T> struct Error {
  T value;
  fmt::string_view message;
  void logError() { fmt::print("[ERROR] : {}\n", message); }
};

template <class T, class E> using $ = std::expected<T, E>;

