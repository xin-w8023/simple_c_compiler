//
// Created by Colin.Wang on 2022/2/14.
//

#include <string>

#include "lexer.h"

using namespace scc;

Lexer::Lexer(std::string source_code) : source_code_(std::move(source_code)) {
  src_size = static_cast<int>(source_code_.size());
  if (src_size != 0) {
    current_char_ = source_code_[0];
  }
}


token_t Lexer::next_token() {

  this->eat_whitespace();

  if (std::isalpha(current_char_)) {
    return this->parse_identifier();
  }

  if (std::isdigit(current_char_)) {
    return this->parse_number();
  }

  char ch = current_char_;
  advance();
  loc_t location{"", 0, static_cast<std::uint32_t>(cursor_ - 1)};
  switch (ch) {
    case '+':
      return token_t{TOKEN_TYPE::Plus, "+", location};
    case '-':
      return token_t{TOKEN_TYPE::Minus, "-", location};
    case '*':
      return token_t{TOKEN_TYPE::Star, "*", location};
    case '/':
      return token_t{TOKEN_TYPE::Slash, "/", location};
    case '=':
      return token_t{TOKEN_TYPE::Equals, "=", location};
    case '\0':
      return token_t{TOKEN_TYPE::Eof, "eof", location};
    default:
      printf("[scc ERROR]: unrecognized character `%c`\n", ch);
      exit(42);
  }
}

void Lexer::advance() {
  if (cursor_ == source_code_.size()) {
    cursor_ ++;
    current_char_ = '\0';
  }
  current_char_ = source_code_[++cursor_];
}

token_t Lexer::parse_number() {

  std::string content{};
  loc_t location{"", 0, static_cast<std::uint32_t>(cursor_)};

  bool has_point = false;
  while (std::isdigit(current_char_) || (current_char_ == '.' && !has_point)) {

    if (current_char_ == '.') has_point = true;

    content += current_char_;
    this->advance();
  }

  return {TOKEN_TYPE::Num, content, location};
}

char Lexer::peek() {
  if (cursor_ < source_code_.size() - 1) {
    return source_code_[cursor_ + 1];
  }
  return '\0';
}

token_t Lexer::parse_identifier() {

  loc_t location{"", 0, static_cast<std::uint32_t>(cursor_)};
  std::string identifier{};
  while (std::isalpha(current_char_)) {
    identifier += current_char_;
    advance();
  }
  return {TOKEN_TYPE::Identifier, identifier, location};
}

void Lexer::eat_whitespace() {
  while (std::isspace(current_char_))
    this->advance();
}

void Lexer::rollback(int position) {
  cursor_ = position;
  current_char_ = source_code_[position];
}
