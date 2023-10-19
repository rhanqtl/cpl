#ifndef CPL_CONSTRAINT_PARTITIONER_H
#define CPL_CONSTRAINT_PARTITIONER_H

#include "AST/Node.h"
#include "AST/Visitor.h"
#include "Runtime/Random/ConstraintPartition.h"

namespace cpl::rt::random {

class ConstraintPartitioner {
 public:
  std::vector<ConstraintPartition> partition(
      const std::vector<ast::Expr *> &csts);
};

}  // namespace cpl::rt::random

#endif  // CPL_CONSTRAINT_PARTITIONER_H