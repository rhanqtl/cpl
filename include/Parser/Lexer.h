#pragma once

#include <iostream>

#include "Parser/Token.h"

namespace cpl::frontend {

class Lexer {
 public:
  explicit Lexer(std::istream &is) : is_{is} {}

  Token next_token();

 private:
  void skip_whitespace();

 private:
  std::istream &is_;
};

}  // namespace cpl::frontend