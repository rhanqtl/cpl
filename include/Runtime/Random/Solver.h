#pragma once

#include <cstdint>
#include <unordered_map>
#include <vector>

#include "AST/Node.h"
#include "Runtime/Random/Stage.h"
#include "Runtime/Random/Var.h"

namespace cpl::rt::random {

enum class Result { SAT, UNSAT };
class NodeRef;

class Solver {
 public:
  void add(NodeRef cst);
  Result find_solution(uintptr_t obj_addr);

 private:
  /// \brief Collect all active constraints
  std::vector<ast::Expr *> collect_active_constraints();

  /// \brief Traverse the AST and create "Var"s for primary expressions
  void create_vars(const std::vector<ast::Expr *> &cst_blocks);

  [[nodiscard]] std::vector<ast::Expr *> expand_foreach(
      const std::vector<ast::Expr *> &csts);

  /// \brief Solve the stage using the SMT solver.
  Result solve_stage(Stage &s);

  /// \brief Fill the result from solver to CPL objects.
  void fill_solution();

 private:
  std::unordered_map<ast::Expr *, Var *> vars_by_ast_primary_;
};

}  // namespace cpl::rt::random