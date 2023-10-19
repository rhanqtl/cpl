#include "Runtime/Random/SolvingOrderAnalysis.h"
#include "Runtime/Random/Stage.h"

namespace cpl::rt::random {

std::vector<Stage> SolvingOrderAnalysis::analyze() {
#ifndef NDEBUG
  sanitize();
#endif
  return {};
}

}  // namespace cpl::rt::random
