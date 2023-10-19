#ifndef CPL_RT_RANDOM_RANDMODEMANAGER_H
#define CPL_RT_RANDOM_RANDMODEMANAGER_H

#include "Utility/Singleton.h"

namespace cpl::rt::random {

class RandModeManager : public util::Singleton<RandModeManager> {
 public:
  bool rand_mode() const;
  bool set_rand_mode();
};

}  // namespace cpl::rt::random

#endif  // CPL_RT_RANDOM_RANDMODEMANAGER_H