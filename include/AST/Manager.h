#pragma once

#include <type_traits>
#include <vector>

namespace solver::ast {

class Manager;

/// \brief A smart pointer to manage reference counter of AST nodes.
template <typename T, typename ManagerT = Manager>
class ObjectRef final {
 public:
  explicit ObjectRef(ManagerT &mgr) : mgr_{mgr} {}
  explicit ObjectRef(T *n, ManagerT &mgr) : n_{n}, mgr_{mgr} {
    m().inc_ref(n_);
  }
  ObjectRef(const ObjectRef &other) : n_{other.get()}, mgr_{other.m()} {
    m().inc_ref(n_);
  }
  ObjectRef(ObjectRef &&other) : mgr_{other.m()} {
    std::swap(n_, other.n_);
  }
  ~ObjectRef() {
    m().dec_ref(n_);
  }

 public:
  ObjectRef &operator=(const ObjectRef &other);
  ObjectRef &operator=(ObjectRef &&other);

  T &operator*() {
    return *n_;
  }
  const T &operator*() const {
    return *n_;
  }
  T *operator->() {
    return n_;
  }
  const T *operator->() const {
    return n_;
  }
  T *get() const {
    return n_;
  }

 private:
  ManagerT &m() const {
    return mgr_;
  }

 private:
  T *n_{nullptr};
  ManagerT &mgr_;
};

namespace solver::ast {

class Node;
class Expr;

using ExprRef = ObjectRef<Expr>;

class Manager {
 public:
  ExprRef mk_expr_bvadd(ExprRef lhs, ExprRef rhs);
  ExprRef mk_expr_bvsub(ExprRef lhs, ExprRef rhs);
  ExprRef mk_expr_unique(std::vector<ExprRef> args);

  void inc_ref(Node *n);
  void dec_ref(Node *n);

 private:
  // ast table
};

}  // namespace solver::ast

}  // namespace solver::ast
