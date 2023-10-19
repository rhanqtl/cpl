#pragma once

#include <filesystem>
#include <memory>

#include "AST/Node.h"
#include "Parser/Lexer.h"

namespace cpl::frontend {

/// \brief The abstract interface of parser.
class Parser {
  virtual std::unique_ptr<ast::Node> parse(std::istream &is) = 0;
};

}  // namespace cpl::frontend

namespace cpl::frontend {

class HandWrittenParser : public Parser {
 public:
  std::unique_ptr<ast::Node> parse(std::istream &is) override;

 private:
  Lexer lex_;
};

}  // namespace cpl::frontend