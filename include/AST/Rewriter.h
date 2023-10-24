#pragma once

#include "Node.h"
namespace cpl::ast {

template <typename Config>
class Rewriter {
 public:
  void operator()(Expr *term, ExprRef &result);

 private:
};

}  // namespace cpl::ast
