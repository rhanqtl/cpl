#ifndef CPL_RT_RANDOM_STAGE_H
#define CPL_RT_RANDOM_STAGE_H

#include "AST/Node.h"

namespace cpl::rt::random {

class Stage {
 public:
  const std::vector<ast::Expr *> &constraints() const;
  std::vector<ast::Expr *> &constraints();
  [[nodiscard]] std::vector<ast::Expr *> take_constraints();

 private:
  std::vector<ast::Expr *> csts;
};

}  // namespace cpl::rt::random

#endif  // CPL_RT_RANDOM_STAGE_H