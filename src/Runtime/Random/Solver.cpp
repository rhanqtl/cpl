#include <cstdint>

#include "Runtime/RTTI/TypeInfo.h"
#include "Runtime/Random/ConstraintPartitioner.h"
#include "Runtime/Random/Solver.h"
#include "Runtime/Random/SolvingOrderAnalysis.h"
#include "Runtime/Random/Stage.h"
#include "Utility/Assert.h"

namespace cpl::rt::random {

Result Solver::find_solution(uintptr_t obj_addr) {
  rt::TypeInfo *type_info = RTTI::get_type_info(obj_addr);
  cpl_assert(type_info->is_class_type());

  // 0. Reuse
  if (can_reuse(obj_addr, type_info)) {
  }

  // 1. Check rand_mode and constraint_mode

  std::vector<ast::Class::ConstraintBlock *> csts =
      collect_active_constraints();

  // 2. Create "Var"s for properties whose rand_mode is 1.
  create_vars(csts);

  // 3. Partition constraints
  ConstraintPartitioner cp;
  std::vector<ConstraintPartition> partitions = cp.partition(csts);

  // 4. Analyze solving order of constraint partitions
  SolvingOrderAnalysis an;
  std::vector<Stage> stages = an.analyze(partitions);

  // 5. For each solving stage, translate to the IR the underlying constraint
  // solver and solve it.
  //  5.1 if an item is foreach, expand it
  //  5.1 translate
  //  5.2 map constraint solver's result to CPL.
  for (Stage &s : stages) {
    Result res = solve_stage(s);
    if (res != Result::SAT) return res;
    fill_solution();
  }

  return Result::SAT;
}

Result Solver::solve_stage(Stage &s) {
  std::vector<ast::Expr *> &csts = s.constraints();

  std::vector<ast::Expr *> results = expand_foreach(csts);

  // Translate
}

}  // namespace cpl::rt::random