#ifndef CPL_RT_RANDOM_SOLVINGORDERANALYSIS_H
#define CPL_RT_RANDOM_SOLVINGORDERANALYSIS_H

#include "Runtime/Random/Stage.h"
namespace cpl::rt::random {

class SolvingOrderAnalysis {
 public:
  std::vector<Stage> analyze();

 private:
  void sanitize();
};

}  // namespace cpl::rt::random

#endif  // CPL_RT_RANDOM_SOLVINGORDERANALYSIS_H