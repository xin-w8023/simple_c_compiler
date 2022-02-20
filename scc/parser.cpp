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
  auto node = parse_mul_exp();

  auto token = lexer_->peek_next_n_token(1);
  if (token.type != TOKEN_TYPE::Plus && token.type != TOKEN_TYPE::Minus) {
    return node;
  }

  auto root = std::make_unique<BinaryExprNode>();
  root->left = std::move(node);
  while (token.type == TOKEN_TYPE::Plus || token.type == TOKEN_TYPE::Minus) {
    if (token.type == TOKEN_TYPE::Plus) {
      root->op = BinaryOperator::Plus;
      this->eat_token(TOKEN_TYPE::Plus);
    } else {
      root->op = BinaryOperator::Minus;
      this->eat_token(TOKEN_TYPE::Minus);
    }
    root->content = token.content;
    root->type = AST_TYPE::Expression;
    root->right = parse_mul_exp();
    token = lexer_->peek_next_n_token(1);
    auto new_root = std::make_unique<BinaryExprNode>();
    new_root->left = std::move(root);
    new_root.swap(root);
  }
  if (root->content.empty()) {
    return std::move(root->left);
  }
  return root;
}

std::unique_ptr<AstBase> Parser::parse_mul_exp() {

  auto node = parse_basic_exp();
  auto token = lexer_->peek_next_n_token(1);

  if (token.type != TOKEN_TYPE::Star && token.type != TOKEN_TYPE::Slash) {
    return node;
  }

  auto root = std::make_unique<BinaryExprNode>();
  root->left = std::move(node);

  while (token.type == TOKEN_TYPE::Star || token.type == TOKEN_TYPE::Slash) {
    if (token.type == TOKEN_TYPE::Star) {
      root->op = BinaryOperator::Star;
      this->eat_token(TOKEN_TYPE::Star);
    } else {
      root->op = BinaryOperator::Slash;
      this->eat_token(TOKEN_TYPE::Slash);
    }
    root->content = token.content;
    root->type = AST_TYPE::Expression;
    root->right = parse_basic_exp();
    token = lexer_->peek_next_n_token(1);
    auto new_root = std::make_unique<BinaryExprNode>();
    new_root->left = std::move(root);
    new_root.swap(root);
  }


  if (root->content.empty()) {
    return std::move(root->left);
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
