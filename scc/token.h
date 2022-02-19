//
// Created by Colin.Wang on 2022/2/14.
//

#ifndef SCC_SCC_TOKEN_H_
#define SCC_SCC_TOKEN_H_

#include <cstdint>
#include <string_view>
#include <string>
#include <sstream>

namespace scc {

enum class TOKEN_TYPE : std::uint8_t {
  Plus = 0,
  Minus,
  Star,
  Slash,
  Equals,
  Num,
  Identifier,
  Lparen,
  Rparen,
  Lbrace,
  Rbrace,
  Semi,
  Comma,
  Null,
  Eof
};


struct loc_t {
  std::string_view file{};
  std::uint32_t line_no{};
  std::uint32_t col_no{};
  [[nodiscard]] std::string str() const {
    return "[" + std::to_string(line_no) + ", " + std::to_string(col_no) + "]";
  }
};

struct token_t {
  TOKEN_TYPE type{};
  std::string content{'\0'};
  loc_t location{};

  [[nodiscard]] std::string repr() const {
    return "<" + get_type_repr() + " `" + content + "`> " + location.str();
  }

  [[nodiscard]] std::string get_type_repr() const {
    switch (type) {
      case TOKEN_TYPE::Plus: return "Plus";
      case TOKEN_TYPE::Minus: return "Minus";
      case TOKEN_TYPE::Star: return "Star";
      case TOKEN_TYPE::Slash: return "Slash";
      case TOKEN_TYPE::Num: return "Num";
      case TOKEN_TYPE::Identifier: return "Identifier";
      case TOKEN_TYPE::Eof: return "Eof";
      case TOKEN_TYPE::Equals: return "Equals";
      case TOKEN_TYPE::Lparen: return "Lparen";
      case TOKEN_TYPE::Rparen: return "Rparen";
      case TOKEN_TYPE::Lbrace: return "Lbrace";
      case TOKEN_TYPE::Rbrace: return "Rbrace";
      case TOKEN_TYPE::Semi: return "Semi";
      case TOKEN_TYPE::Comma: return "Comma";
      default:
        printf("Unknown token type");
        exit(42);
    }
  }

};

}
#endif //SCC_SCC_TOKEN_H_
