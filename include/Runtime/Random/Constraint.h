#ifndef CPL_CONSTRAINT_H
#define CPL_CONSTRAINT_H

#include <vector>

#include "AST/Node.h"
namespace cpl::rt::random {

class Constraint {
 public:
  explicit Constraint(ast::Expr *expr);

 private:
  ast::Expr *expr_;
  std::vector<ast::Expr> support_vars_;
};

}  // namespace cpl::rt::random

#endif  // CPL_CONSTRAINT_H