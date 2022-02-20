//
// Created by Colin.Wang on 2022/2/19.
//

#include "lexer.h"
#include "ast.h"
#include "parser.h"

using namespace scc;

Parser::Parser(std::unique_ptr<Lexer> lexer) : lexer_(std::move(lexer)) {

}

std::unique_ptr<AstBase> Parser::parse() {

  return parse_exp();
}

std::unique_ptr<AstBase> Parser::parse_exp() {

  auto token = lexer_->peek_next_n_token(1);

  if (token.type == TOKEN_TYPE::Identifier) {
    auto next_token = lexer_->peek_next_n_token(2);
    if (next_token.type == TOKEN_TYPE::Equals) {
      return parse_assign_exp();
    }

  }

  return parse_add_exp();
}

std::unique_ptr<AstBase> Parser::parse_assign_exp() {

  auto root = std::make_unique<BinaryExprNode>();
  root->op = BinaryOperator::Assignment;
  root->type = AST_TYPE::Expression;

  auto token = lexer_->next_token();
  root->content = this->eat_token(TOKEN_TYPE::Equals).content;

  auto node = std::make_unique<AstBase>();
  node->type = AST_TYPE::Variable;
  node->content = token.content;
  root->left = std::move(node);

  root->right = parse_exp();
  return root;
}

std::unique_ptr<AstBase> Parser::parse_add_exp() {
  auto root = parse_mul_exp();

  auto token = lexer_->peek_next_n_token(1);
  if (token.type != TOKEN_TYPE::Plus && token.type != TOKEN_TYPE::Minus) {
    return root;
  }

  while (token.type == TOKEN_TYPE::Plus || token.type == TOKEN_TYPE::Minus) {
    BinaryOperator op;
    if (token.type == TOKEN_TYPE::Plus) {
      op = BinaryOperator::Plus;
      this->eat_token(TOKEN_TYPE::Plus);
    } else {
      op = BinaryOperator::Minus;
      this->eat_token(TOKEN_TYPE::Minus);
    }
    auto right = parse_mul_exp();
    root = std::make_unique<BinaryExprNode>(std::move(root), op, std::move(right));
    root->content = token.content;
    root->type = AST_TYPE::Expression;
    token = lexer_->peek_next_n_token(1);
  }

  return root;
}

std::unique_ptr<AstBase> Parser::parse_mul_exp() {

  auto root = parse_basic_exp();
  auto token = lexer_->peek_next_n_token(1);

  if (token.type != TOKEN_TYPE::Star && token.type != TOKEN_TYPE::Slash) {
    return root;
  }

  while (token.type == TOKEN_TYPE::Star || token.type == TOKEN_TYPE::Slash) {
    BinaryOperator op;
    if (token.type == TOKEN_TYPE::Star) {
      op = BinaryOperator::Star;
      this->eat_token(TOKEN_TYPE::Star);
    } else {
      op = BinaryOperator::Slash;
      this->eat_token(TOKEN_TYPE::Slash);
    }

    auto right = parse_basic_exp();
    root = std::make_unique<BinaryExprNode>(std::move(root), op, std::move(right));
    root->content = token.content;
    root->type = AST_TYPE::Expression;

    token = lexer_->peek_next_n_token(1);
  }

  return root;
}

std::unique_ptr<AstBase> Parser::parse_basic_exp() {
  auto token = lexer_->peek_next_n_token(1);

  if (token.type == TOKEN_TYPE::Identifier) {
    return parse_variable_exp();
  } else if (token.type == TOKEN_TYPE::Lparen) {
    this->eat_token(TOKEN_TYPE::Lparen);
    auto node = parse_exp();
    this->eat_token(TOKEN_TYPE::Rparen);
    return node;
  }

  return parse_constant_exp();
}

std::unique_ptr<AstBase> Parser::parse_variable_exp() {
  auto node = std::make_unique<AstBase>();
  auto token = this->eat_token(TOKEN_TYPE::Identifier);
  node->content = token.content;
  node->type = AST_TYPE::Variable;

  return node;
}

std::unique_ptr<AstBase> Parser::parse_constant_exp() {
  auto node = std::make_unique<ConstantExprNode>();
  auto token = this->eat_token(TOKEN_TYPE::Num);
  node->type = AST_TYPE::Constant;
  node->content = token.content;
  node->value = std::stoi(node->content);
  return node;
}

token_t Parser::eat_token(TOKEN_TYPE type) {
  auto token = lexer_->next_token();
  if (token.type != type) {
    printf("ERROR: unexpected token: %s, expect: %d\n", token.repr().c_str(), (int)type);
    exit(42);
  }
  return token;
}
