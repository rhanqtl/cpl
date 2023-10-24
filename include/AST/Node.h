#pragma once

#include <cstddef>
#include <cstdint>
#include <limits>
#include <string>
#include <variant>
#include <vector>

#include "Utility/Assert.h"

namespace cpl::ast {

class Manager;
class ObjectRef;

class Visitor;

class Class;
class Property;

/// \remarks It's actually a DAG.
class Node {
  friend Manager;

 public:
  enum class Kind {
    CONSTANT,
    PROPERTY_REF,
    LOOP_INDEX,
    BOP,  // Binary operators
    UOP,  // Unary operators
    CONCAT,
    UNIQUE,  // unique and dist are not operators
    DIST,
    FOREACH,
  };

 protected:
  explicit Node(Kind k) : k_{k} {}

 public:
  Kind kind() const {
    return k_;
  }

  virtual void accept(Visitor &vis) = 0;

  std::string to_string() const;

 protected:
  void set_hash(size_t h) {
    hash_ = h;
  }

 private:
  size_t hash() const {
    return hash_;
  }
  void inc_ref() {
    solver_assert(ref_cnt_ < std::numeric_limits<decltype(ref_cnt_)>::max());
    ref_cnt_++;
  }
  size_t dec_ref() {
    solver_assert(ref_cnt_ > 0);
    return --ref_cnt_;
  }
  size_t ref_count() const {
    return ref_cnt_;
  }

 protected:
  /// \brief Check equivalence when hash codes collide.
  virtual bool equals(const Node *n) const = 0;

 private:
  /// \brief Kind of AST node, for fast type checking
  const Kind k_;

  size_t hash_;
  size_t ref_cnt_{0};
};

class Expr : public Node {
 protected:
  explicit Expr(Node::Kind kind) : Node{kind} {}
};

// Primary Expressions

/// \brief This class represents contants (including literals and those
/// generated during transformation).
/// \note Currently only integers of bit-width <= 64 are supported, and 32-bit
/// values are treated as 64-bit.
class Constant : public Expr {
  friend Manager;

 public:
  explicit Constant(int64_t val) : Expr{Node::Kind::CONSTANT}, v_{val} {}
  explicit Constant(uint64_t val) : Expr{Node::Kind::CONSTANT}, v_{val} {}

  bool is_unsigned_int() const {
    return v_.index() == 0;
  }
  bool is_signed_int() const {
    return v_.index() == 1;
  }

  operator uint64_t() const {
    solver_assert(is_unsigned_int());
    return std::get<uint64_t>(v_);
  }
  operator int64_t() const {
    solver_assert(is_signed_int());
    return std::get<int64_t>(v_);
  }

 private:
  std::variant<uint64_t, int64_t> v_;
};

class PropertyRef : public Expr {
  friend Manager;

 private:
  explicit PropertyRef(Property *prop)
      : Expr{Node::Kind::PROPERTY_REF}, prop_{prop} {}

 private:
  Property *prop_;
};

class LoopIndex : public Expr {
  friend Manager;

 private:
  explicit LoopIndex(const std::string name, size_t which_dim)
      : Expr{Node::Kind::LOOP_INDEX}, name_{name}, which_dim_{which_dim} {}

 private:
  std::string name_;
  size_t which_dim_;
};

class BinaryExpr : public Expr {
 public:
  enum class Opcode : uint8_t {
    ADD,
    SUB,
    MUL,
    DIV,  // /
    REM,  // %

    LOG_AND,  // &&
    LOG_OR,   // ||

    BIT_AND,  // &
    BIT_OR,   // |
    BIT_XOR,  // ^

    IMPLY,  // ->
    // LOG_EQUIV,  // "a <-> b" is transformed into "(a && b) || (!a && !b)"

    INSIDE,  // left: a primary, right: a concat
  };

 protected:
  BinaryExpr(Opcode op, std::vector<ObjectRef> args);

 public:
  void accept(Visitor &vis) override;

 private:
  Opcode op_;
  Expr *lhs_;
  Expr *rhs_;
};

class UnaryExpr : public Expr {
 public:
  enum class Opcode : uint8_t {
    NEG,
  };

 private:
  Opcode op_;
  Expr *arg_;
};

/// \brief unique { ... }
class UniqueExpr : public Expr {
 private:
  std::vector<Expr *> args_;
};

class DistExpr : public Expr {
  class DistItem;

 private:
  std::vector<DistItem> items_;
};

/// \remarks [18.5.4] The grammar:
///   expression_or_dist ::= expression [ "dist" dist_list ]
///   dist_list ::= dist_item ( "," dist_item )*
///   dist_item ::= value_range [ dist_weight ]
///   dist_weight ::=
///       := expression
///     | :/ expression
///   If "dist_weight" is omitted, set to ":= 1".
class DistItem {
 public:
  enum class WeightType {
    FOR_EACH,  // :=
    AS_WHOLE,  // :/
  };

 private:
  WeightType wt_;
  Expr *rng_;
  Expr *w_;
};

class ConcatExpr : public Expr {
  friend Manager;

 private:
  explicit ConcatExpr(std::vector<Expr *> xs)
      : Expr{Node::Kind::CONCAT}, elems_{std::move(xs)} {}

 public:
  const std::vector<Expr *> &elements() const {
    return elems_;
  }
  std::vector<Expr *> &elements() {
    return elems_;
  }

 private:
  std::vector<Expr *> elems_;
};

class ForeachExpr : public Expr {
 private:
  Expr *ary_;
  std::vector<LoopIndex *> indexes_;
  Expr *body_;
};

class SoftExpr : public Expr {
 private:
  Expr *expr_;
};

class Class {
 public:
  class Property {
   public:
    const std::string &name() const {
      return name_;
    }
    bool is_rand() const {
      return rand_;
    }
    bool is_static() const {
      return static_;
    }

   private:
    const std::string name_;
    const bool rand_;
    const bool static_;
    // TODO(rhanqtl): type
  };

  class ConstraintBlock {
   public:
    class Item {
     public:
      Expr *expression() const {
        return expr_;
      }

     private:
      Expr *const expr_;
    };

   public:
    const std::string &name() const {
      return name_;
    }
    bool is_static() const {
      return static_;
    }
    const std::vector<Item> &items() const {
      return items_;
    }
    std::vector<Item> &items() {
      return items_;
    }

   private:
    const bool static_;
    const std::string name_;
    std::vector<Item> items_;
  };

 private:
  const std::string name_;
  std::vector<Property> properties_;
  std::vector<ConstraintBlock> cst_blocks_;
};

}  // namespace cpl::ast
