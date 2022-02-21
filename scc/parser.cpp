//
// Created by Colin.Wang on 2022/2/19.
//

#include "lexer.h"
#include "ast.h"
#include "parser.h"

using namespace scc;

Parser::Parser(const std::string& source_code) {
  lexer_ = std::make_unique<Lexer>(source_code);
}

Parser::Parser(std::unique_ptr<Lexer> lexer) : lexer_(std::move(lexer)) {

}

std::unique_ptr<AstBaseNode> Parser::parse() {

  auto root = parse_expression();
  this->eat_token(TOKEN_TYPE::Eof);
  return root;
}

std::unique_ptr<AstBaseNode> Parser::parse_expression(int parent_priority) {
  std::unique_ptr<AstBaseNode> root;
  auto token = lexer_->peek_next_n_token(1);
  int unary_op_priority = get_unary_priority(token.type);

  if (unary_op_priority != 0 && unary_op_priority >= parent_priority){

    token = this->eat_token(token.type);
    UnaryOperator op = get_unary_operator(token.type);
    auto right = parse_expression(unary_op_priority);
    root = std::make_unique<UnaryExprNode>(op, std::move(right));
    root->content = token.content;
    root->type = AST_TYPE::UnExpression;


  } else {

    root = parse_basic_exp();
  }

  while(true) {
    token = lexer_->peek_next_n_token(1);
    int priority = get_binary_priority(token.type);
    if (priority == 0 || priority <= parent_priority)
      break;
    BinaryOperator op = get_binary_operator(token.type);
    this->eat_token(token.type);
    auto right = parse_expression(priority);
    root = std::make_unique<BinaryExprNode>(std::move(root), op, std::move(right));
    root->content = token.content;
    root->type = AST_TYPE::BiExpression;
  }
  return root;
}

std::unique_ptr<AstBaseNode> Parser::parse_basic_exp() {
  auto token = lexer_->peek_next_n_token(1);

  if (token.type == TOKEN_TYPE::Identifier) {
    return parse_variable_exp();
  } else if (token.type == TOKEN_TYPE::Lparen) {
    this->eat_token(TOKEN_TYPE::Lparen);
    auto node = parse_expression();
    this->eat_token(TOKEN_TYPE::Rparen);
    return node;
  }

  return parse_constant_exp();
}

std::unique_ptr<AstBaseNode> Parser::parse_variable_exp() {
  auto node = std::make_unique<AstBaseNode>();
  auto token = this->eat_token(TOKEN_TYPE::Identifier);
  node->content = token.content;
  node->type = AST_TYPE::Variable;

  return node;
}

std::unique_ptr<AstBaseNode> Parser::parse_constant_exp() {
  auto node = std::make_unique<ConstantExprNode>();
  auto token = lexer_->peek_next_n_token(1);
  switch (token.type) {
    case TOKEN_TYPE::Num:
      node->value = std::stoi(token.content);
      this->eat_token(TOKEN_TYPE::Num);
      break;
    case TOKEN_TYPE::String:
      this->eat_token(TOKEN_TYPE::String);
      node->value = token.content;
      break;
    default:
      printf("ERROR: unsupport constant token type: %s\n",
             get_type_repr(token.type).c_str());
  }
  node->type = AST_TYPE::Constant;
  node->content = token.content;
  return node;
}

token_t Parser::eat_token(TOKEN_TYPE type) {
  auto token = lexer_->next_token();
  if (token.type != type) {
    printf("ERROR: unexpected token: %s, expect: %s\n",
           token.repr().c_str(), get_type_repr(type).c_str());
    exit(42);
  }
  return token;
}

int Parser::get_binary_priority(TOKEN_TYPE type) {
  switch (type) {
    case TOKEN_TYPE::Star:
    case TOKEN_TYPE::Slash:
      return 4;
    case TOKEN_TYPE::Plus:
    case TOKEN_TYPE::Minus:
      return 2;
    case TOKEN_TYPE::Equals:
      return 1;
    default:
      return 0;
  }
}

BinaryOperator Parser::get_binary_operator(TOKEN_TYPE type) {
  switch (type) {
    case TOKEN_TYPE::Star:
      return BinaryOperator::Star;
    case TOKEN_TYPE::Slash:
      return BinaryOperator::Slash;
    case TOKEN_TYPE::Plus:
      return BinaryOperator::Plus;
    case TOKEN_TYPE::Minus:
      return BinaryOperator::Minus;
    case TOKEN_TYPE::Equals:
      return BinaryOperator::Assignment;
    default:
      return BinaryOperator::BadOp;
  }
}


int Parser::get_unary_priority(TOKEN_TYPE type) {
  switch (type) {
    case TOKEN_TYPE::Plus:
    case TOKEN_TYPE::Minus:
      return 8;
    default:
      return 0;
  }
}

UnaryOperator Parser::get_unary_operator(TOKEN_TYPE type) {
  switch (type) {
    case TOKEN_TYPE::Plus:
      return UnaryOperator::Plus;
    case TOKEN_TYPE::Minus:
      return UnaryOperator::Minus;
    default:
      return UnaryOperator::BadOp;
  }
}