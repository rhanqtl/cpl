#pragma once

#include <cstdarg>
#include <cstdio>
#include <cstdlib>

#define cpl_unreachable(fmt, ...) \
  _cpl_unreachable_handler(__FILE__, __LINE__, fmt, __VA_ARGS__)

[[noreturn]] inline void _cpl_unreachable_handler(const char *file, int line,
                                                  const char *fmt, ...) {
  std::abort();
}

#ifndef NDEBUG
#define cpl_assert(expr)                            \
  if (!(expr)) {                                    \
    _cpl_assert_handler(__FILE__, __LINE__, #expr); \
  }
#else
#define cpl_assert(expr, ...)
#endif

[[noreturn]] inline void _cpl_assert_handler(const char *file, int line,
                                             const char *expr_str) {
  _cpl_unreachable_handler(file, line,
                           "at %s:%d: expression '%s' is not satisfied", file,
                           line, expr_str);
}
