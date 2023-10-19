
#include <gtest/gtest.h>

#include "Solver/RandVar.h"
#include "Solver/Solver.h"

using namespace solver;

TEST(No_Solve_Order, _) {
  RandVar x, y, z;
  Solver s;
  s.add(x + y == z);
  s.add(x < 100);
  s.add(y < 100);

  Solver::Result res = s.solve();
  ASSERT_EQ(res, Solver::Result::SAT);

  EXPECT_LESS_THAN(x, 100);
  EXPECT_LESS_THAN(y, 100);
  EXPECT_EQ(x.value() + y.value(), z.value());
}
