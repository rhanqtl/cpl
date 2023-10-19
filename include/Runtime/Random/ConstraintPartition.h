#ifndef CPL_CONSTRAINT_PARTITION_H
#define CPL_CONSTRAINT_PARTITION_H

#include "AST/Node.h"
#include "Runtime/Random/Constraint.h"

namespace cpl::rt::random {

/// \brief A constraint partition consists of constraints containing related
/// vars.
class ConstraintPartition {
 private:
  std::vector<Constraint> csts_;
};

}  // namespace cpl::rt::random

#endif  // CPL_CONSTRAINT_PARTITION_H
