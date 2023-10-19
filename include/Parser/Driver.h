#pragma once

#include <filesystem>
#include <memory>

#include "AST/Node.h"

namespace cpl::frontend {

class Driver {
  std::unique_ptr<ast::Node> run(std::filesystem::path p);
};

}  // namespace cpl::frontend