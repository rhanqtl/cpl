#ifndef CPL_RT_RTTI_TYPEINFO_H
#define CPL_RT_RTTI_TYPEINFO_H

#include <string>
#include <vector>

namespace cpl::rt {

enum Category {
  PRIMITIVE,
  CLASS,
  DYNAMIC_ARRAY,
};

class RTTI {};

enum class Qualifier : uint32_t {
  RAND = 1,
  RANDC = 1 << 1,
  STATIC = 1 << 2,
};

inline Qualifier operator|(Qualifier left, Qualifier right) {
  return Qualifier(left | right);
}

class PropertyInfo {
 public:
 private:
};

class TypeInfo {
 public:
  bool is_primitive_type() const { return cate_ == Category::PRIMITIVE; }
  bool is_class_type() const { return cate_ == Category::CLASS; }
  bool is_array_type() const { return cate_ == Category::DYNAMIC_ARRAY; }

  union {
    struct {
      std::string name;
      std::vector<PropertyInfo> props;
    } cls;
  };

 private:
  Category cate_;
};

}  // namespace cpl::rt

#endif  // CPL_RT_RTTI_TYPEINFO_H