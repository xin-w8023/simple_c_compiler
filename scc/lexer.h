//
// Created by Colin.Wang on 2022/2/14.
//

#ifndef SCC_SCC_LEXER_H_
#define SCC_SCC_LEXER_H_

#include <string_view>

#include "token.h"

namespace scc {

class Lexer {

 public:

  Lexer() = default;

  explicit Lexer(std::string source_code);

  token_t next_token();

 private:

  void advance();

  void eat_whitespace();

  void rollback(int position);

  token_t parse_number();

  token_t parse_identifier();

  char peek();

 private:

  std::string source_code_{};
  int src_size{};
  int cursor_{0};
  char current_char_{};
  std::uint32_t cur_line_{};
  std::uint32_t cur_col_{};
};

}

#endif //SCC_SCC_LEXER_H_
