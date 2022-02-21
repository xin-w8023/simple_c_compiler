//
// Created by Colin.Wang on 2022/2/18.
//

#ifndef SCC_SCC_COMPILER_H_
#define SCC_SCC_COMPILER_H_

#include <string_view>

#include "lexer.h"
#include "parser.h"

namespace scc {

class Compiler {

 public:

  explicit Compiler() = default;

  explicit Compiler(std::string_view filename);

  void compile();

  static void compile(const std::string& filename);

 private:
  std::unique_ptr<Parser> parser_;
};

}

#endif //SCC_SCC_COMPILER_H_
