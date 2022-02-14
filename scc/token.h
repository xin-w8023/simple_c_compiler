//
// Created by Wangxin.Colin on 2022/2/14.
//

#ifndef SCC_SCC_TOKEN_H_
#define SCC_SCC_TOKEN_H_

#include <cstdint>

namespace scc {

enum class TOKEN_TYPE : std::uint8_t {
  Plus = 0,
  Minus,
  Star,
  Slash,
  Num,
  String,
  Eof

};


struct loc_t {
  std::string_view file{};
  std::uint32_t line_no{};
  std::uint32_t col_no{};
};

struct token_t {
  TOKEN_TYPE type{};
  std::string content{};
  loc_t location{};

  [[nodiscard]] std::string repr() const {
    return get_type_repr() + " \t" + content;
  }

  [[nodiscard]] std::string get_type_repr() const {
    switch (type) {
      case TOKEN_TYPE::Plus: return "Plus";
      case TOKEN_TYPE::Minus: return "Minus";
      case TOKEN_TYPE::Star: return "Star";
      case TOKEN_TYPE::Slash: return "Slash";
      case TOKEN_TYPE::Num: return "Num";
      case TOKEN_TYPE::String: return "String";
      case TOKEN_TYPE::Eof: return "Eof";
    }
  }

};

}
#endif //SCC_SCC_TOKEN_H_
