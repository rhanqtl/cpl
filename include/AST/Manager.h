#pragma once

#include <vector>

namespace solver::ast {

class Expr;
class Node;

class NodeRef;

class Manager {
 public:
  NodeRef mk_expr_add(NodeRef lhs, NodeRef rhs);
  NodeRef mk_expr_sub(NodeRef lhs, NodeRef rhs);
  NodeRef mk_expr_unique(std::vector<NodeRef> args);

  void inc_ref(Node *n);
  void dec_ref(Node *n);

 private:
  // ast table
};

}  // namespace solver::ast

namespace solver::ast {

class Node;

/// \brief A smart pointer to manage reference counter of AST nodes.
class NodeRef {
 public:
  explicit NodeRef(Node *n, solver::ast::Manager &mgr) : n_{n}, mgr_{mgr} {
    m().inc_ref(n);
  }
  ~NodeRef() { m().dec_ref(n_); }

 public:
  Node &operator*() { return *n_; }
  const Node &operator*() const { return *n_; }
  Node *operator->() { return n_; }

 private:
  solver::ast::Manager &m() const { return mgr_; }

 private:
  Node *n_;
  solver::ast::Manager &mgr_;
};

}  // namespace solver::ast
