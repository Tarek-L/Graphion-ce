#pragma once

#include <expected>
#include <fmt/core.h>
#include <glad/glad.h>

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

// DEBUG, turned off in realease

#define GL_STACK_OVERFLOW 0x0503
#define GL_STACK_UNDERFLOW 0x0504

inline void GLClearError() {
  while (glGetError() != GL_NO_ERROR)
    ;
}

inline const char *GLGetErrorString(GLenum error) {
  switch (error) {
  case GL_INVALID_ENUM:
    return "INVALID_ENUM";
  case GL_INVALID_VALUE:
    return "INVALID_VALUE";
  case GL_INVALID_OPERATION:
    return "INVALID_OPERATION";
  case GL_STACK_OVERFLOW:
    return "STACK_OVERFLOW";
  case GL_STACK_UNDERFLOW:
    return "STACK_UNDERFLOW";
  case GL_OUT_OF_MEMORY:
    return "OUT_OF_MEMORY";
  case GL_INVALID_FRAMEBUFFER_OPERATION:
    return "INVALID_FRAMEBUFFER_OPERATION";
  default:
    return "UNKNOWN_ERROR";
  }
}

inline bool GLLogCall(const char *function, const char *file, int line) {
  bool hasError = false;
  while (GLenum error = glGetError()) {
      fmt::print("[OpenGL Error] ({}) | Call: {} | {}:{}",
                  GLGetErrorString(error), function, file, line);
    hasError = true;
  }
  return hasError;
}

#if defined(_MSC_VER)
#define DEBUG_BREAK() __debugbreak()
#else
#define DEBUG_BREAK() __builtin_trap()
#endif

#ifdef NDEBUG
#define GL_CALL(gl_func) gl_func
#else
#define GL_CALL(gl_func)                                                       \
  do {                                                                         \
    GLClearError();                                                            \
    gl_func;                                                                   \
    if (GLLogCall(#gl_func, __FILE__, __LINE__)) {                             \
      DEBUG_BREAK();                                                           \
    }                                                                          \
  } while (0)
#endif

#ifdef NDEBUG
#define ASSERT(expr, ...) ((void)0)
#else
#define ASSERT(expr, ...)                                                      \
  do {                                                                         \
    if (!(expr)) {                                                             \
      fmt::error("[Assertion Failed] {} | {}:{} | {}", #expr, __FILE__,     \
                    __LINE__, fmt::format(__VA_ARGS__));                       \
      DEBUG_BREAK();                                                           \
    }                                                                          \
  } while (0)
#endif

