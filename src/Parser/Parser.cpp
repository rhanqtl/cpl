#include <fstream>

#include "Parser/Lexer.h"
#include "Parser/Parser.h"
#include "Parser/Token.h"

namespace cpl::frontend {

std::unique_ptr<ast::Node> HandWrittenParser::parse(std::istream &is) {
  Lexer lex{is};

  Token tok = lex.next_token();
  if (tok == TK_INVALID) std::cerr << "no input\n";

  return {};
}

}  // namespace cpl::frontend