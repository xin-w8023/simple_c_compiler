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

  explicit Parser(const std::string& source_code);

  explicit Parser(std::unique_ptr<Lexer> lexer);

  std::unique_ptr<AstBaseNode> parse();

 private:

  std::unique_ptr<AstBaseNode> parse_expression(int priority = 0);

  // including constance and variable
  std::unique_ptr<AstBaseNode> parse_basic_exp();

  std::unique_ptr<AstBaseNode> parse_constant_exp();

  std::unique_ptr<AstBaseNode> parse_variable_exp();

  token_t eat_token(TOKEN_TYPE type);

 private:

  std::unique_ptr<Lexer> lexer_;
  int get_binary_priority(TOKEN_TYPE type);
  BinaryOperator get_binary_operator(TOKEN_TYPE type);
  int get_unary_priority(TOKEN_TYPE type);
  UnaryOperator get_unary_operator(TOKEN_TYPE type);
};

}

#endif //SCC_SCC_PARSER_H_
