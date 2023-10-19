#include "Runtime/Random/SupportVarsCollector.h"

namespace cpl::rt::random {

[[nodiscard]] std::vector<ast::Expr *> SupportVarsCollector::collect(
    ast::Expr *cst) {
  return {};
}

}  // namespace cpl::rt::random