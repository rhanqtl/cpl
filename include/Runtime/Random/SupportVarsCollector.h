#ifndef CPL_RT_RAND_ANALYSIS_SUPPORTVARSCOLLECTOR_H
#define CPL_RT_RAND_ANALYSIS_SUPPORTVARSCOLLECTOR_H

#include "AST/Node.h"
#include "AST/Visitor.h"

namespace cpl::rt::random {

class SupportVarsCollector : private ast::Visitor {
  [[nodiscard]] std::vector<ast::Expr *> collect(ast::Expr *cst);
};

}  // namespace cpl::rt::random

#endif  // CPL_RT_RAND_ANALYSIS_SUPPORTVARSCOLLECTOR_H