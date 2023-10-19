#pragma once

#include <memory>
#include <optional>
#include <tuple>
#include <vector>

namespace cpl::rt::random {

class Var {
 public:
  bool solved() const { return solved_; }
  void set_solved(bool new_val = true) { solved_ = new_val; }

 private:
  bool solved_{false};
};

class ScalarVar : public Var {
 public:
  uint64_t value() const { return v_; }

 private:
  uint64_t v_;
};

class DynArrayVar : public Var {
 public:
  std::optional<size_t> size() const {
    if (!solved()) return std::nullopt;
    return sz_->value();
  }

  Var *operator[](size_t i) const { return elems_[i].get(); }

 private:
  std::unique_ptr<ScalarVar> sz_;
  std::vector<std::unique_ptr<Var>> elems_;
};

/// \brief Represents function call return value.
class FuncCallVar : public Var {};

}  // namespace cpl::rt::random
