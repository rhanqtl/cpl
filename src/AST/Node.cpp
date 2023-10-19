#include <sstream>

#include "AST/Node.h"
#include "AST/PrettyPrint.h"

namespace cpl::ast {

std::string Node::to_string() const {
  std::ostringstream oss;
  PrettyPrinter pp;
  pp.print(this, oss);
  return oss.str();
}

}  // namespace cpl::ast