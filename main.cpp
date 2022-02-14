//
// Created by Wangxin.Colin on 2022/2/14.
//

#include <iostream>

#include "scc/lexer.h"
#include "scc/token.h"

using namespace scc;
int main() {
  std::string_view code = "  3   +       2    * 3 / 10 + 1.1 ";
  Lexer lexer(code);
  auto token = lexer.next_token();
  while (token.type != TOKEN_TYPE::Eof) {
    std::cout << token.repr() << std::endl;
    token = lexer.next_token();
  }


  return 42;
}