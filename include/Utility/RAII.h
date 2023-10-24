#ifndef CPL_UTILITY_RAII_H
#define CPL_UTILITY_RAII_H

#include "Misc.h"

#define ANON_GUARD ANON_VAR(__guard_)

template <typename T>
class SaveRestore {
 public:
  SaveRestore(T &r, T new_val) : ref_{r}, old_val_{r} {
    r = new_val;
  }
  ~SaveRestore() {
    ref_ = old_val_;
  }

 private:
  T &ref_;
  T old_val_;
};

template <typename Func>
class DeferExecGuard {
 public:
  DeferExecGuard(Func &&f) : fn_{f} {}
  ~DeferExecGuard() {
    fn_();
  }

 private:
  Func fn_;
};

/// \brief Convenient macro to create instances of DeferExecGuard.
/// \note Created lambda expressions use capture-by-ref.
#define cpl_defer(...) DeferExecGuard ANON_GUARD{[&] { __VA_ARGS__ }};

#endif  // CPL_UTILITY_RAII_H
