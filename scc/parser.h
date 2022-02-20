//
// Created by Colin.Wang on 2022/2/19.
//

#ifndef SCC_SCC_PARSER_H_
#define SCC_SCC_PARSER_H_

#include <memory>

#include "ast.h"


namespace scc {

class Lexer;

class Parser {
 public:

  Parser() = default;

  explicit Parser(std::unique_ptr<Lexer> lexer);

  std::unique_ptr<AstBase> parse();

  std::unique_ptr<AstBase> parse_exp();

  std::unique_ptr<AstBase> parse_assign_exp();

  std::unique_ptr<AstBase> parse_add_exp();

  std::unique_ptr<AstBase> parse_mul_exp();

  // including constance and variable
  std::unique_ptr<AstBase> parse_basic_exp();

  std::unique_ptr<AstBase> parse_constant_exp();

  std::unique_ptr<AstBase> parse_variable_exp();

  token_t eat_token(TOKEN_TYPE type);

 private:

  std::unique_ptr<Lexer> lexer_;
};

}

#endif //SCC_SCC_PARSER_H_
