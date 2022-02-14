//
// Created by Wangxin.Colin on 2022/2/14.
//

#include <string>

#include "lexer.h"

using namespace scc;

Lexer::Lexer(std::string_view source_code) : source_code_(source_code) {

}


token_t Lexer::next_token() {
  token_t t;
  char ch = next_char();

  while (std::isspace(ch)) ch = next_char();

  switch (ch) {
    case '+':
      return token_t{TOKEN_TYPE::Plus, "+"};
    case '-':
      return token_t{TOKEN_TYPE::Minus, "-"};
    case '*':
      return token_t{TOKEN_TYPE::Star, "*"};
    case '/':
      return token_t{TOKEN_TYPE::Slash, "/"};
    case '\0':
      return token_t{TOKEN_TYPE::Eof, "eof"};
    default:
      auto code = parse_number(ch);
      if (!code.empty())
        return token_t{TOKEN_TYPE::Num, code};
      else
        printf("ERROR: unsupported token\n");
  }
  return {};
}

char Lexer::next_char() {
  if (cursor_ == source_code_.size()) {
    cursor_ ++;
    return '\0';
  }
  return source_code_[cursor_++];
}

std::string Lexer::parse_number(char &ch) {
  std::string code{};
  int start_pos = cursor_;
  bool has_point = false;
  while ((ch >= '0' && ch <= '9') || (ch == '.' && !has_point)) {

    if (ch == '.') has_point = true;

    code += ch;
    ch = next_char();
  }

  if ((ch >= '0' && ch <= '9') || (ch == '.' && !has_point) || std::isspace(ch));
  else {
    cursor_ = start_pos; // rollback
  }

  return code;
}
