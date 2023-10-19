

#ifndef CPL_RT_RANDOM_RANDMODEMANAGER_H
#define CPL_RT_RANDOM_RANDMODEMANAGER_H

#include "Utility/Singleton.h"

namespace cpl::rt::random {

class ConstraintModeManager : public util::Singleton<ConstraintModeManager> {
 public:
  bool constraint_mode() const;
  bool set_constraint_mode();
};

}  // namespace cpl::rt::random

#endif  // CPL_RT_RANDOM_RANDMODEMANAGER_H