#ifndef CPL_PARSER_BUILTIN_H
#define CPL_PARSER_BUILTIN_H

#include <string>
#include <string_view>
#include <unordered_set>

static std::unordered_set<std::string> builtin_functions = {
    "$len",
    "$randomize",
    "$print",
};

inline bool is_builtin_function(const std::string &s) {
  return builtin_functions.count(s);
}

#endif  // CPL_PARSER_BUILTIN_H
