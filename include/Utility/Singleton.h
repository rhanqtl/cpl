#ifndef CPL_UTILITY_SINGLETON_H
#define CPL_UTILITY_SINGLETON_H

#include <type_traits>

namespace cpl::util {

template <typename T>
class Singleton {
 protected:
  Singleton() {
    static_assert(std::is_base_of_v<Singleton, T>,
                  "type parameter T shall be a subclass of Singleton");
  }
  virtual ~Singleton() = default;

 private:
  Singleton(const Singleton &) = delete;
  Singleton(Singleton &&) = delete;
  Singleton &operator=(const Singleton &) = delete;
  Singleton &operator=(Singleton &&) = delete;

 public:
  static T &instance() {
    static T inst;
    return inst;
  }
};

}  // namespace cpl::util

#endif  // CPL_UTILITY_SINGLETON_H
