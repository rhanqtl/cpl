#ifndef CPL_AST_PRETTYPRINTER_H
#define CPL_AST_PRETTYPRINTER_H

#include "AST/Node.h"
#include "AST/Visitor.h"

namespace cpl::ast {

class PrettyPrinter : private Visitor {
 public:
  void print(const Node* const n, std::ostream& os);

 private:
};

}  // namespace cpl::ast

#endif  // CPL_AST_PRETTYPRINTER_H