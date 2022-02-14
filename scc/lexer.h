//
// Created by Wangxin.Colin on 2022/2/14.
//

#ifndef SCC_SCC_LEXER_H_
#define SCC_SCC_LEXER_H_

#include <string_view>

#include "token.h"

namespace scc {

class Lexer {

 public:

  explicit Lexer(std::string_view source_code);

  token_t next_token();

 private:

  char next_char();

  std::string parse_number(char& ch);

  std::string_view source_code_{};
  int cursor_{0};
};

}

#endif //SCC_SCC_LEXER_H_
