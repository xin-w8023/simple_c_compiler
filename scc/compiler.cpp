//
// Created by Colin.Wang on 2022/2/18.
//

#include "common/logger.h"
#include "io.h"
#include "compiler.h"

using namespace scc;

Compiler::Compiler(std::string_view source_filename) {
  auto source_code = read_file_string(source_filename);
  lexer_ = Lexer(source_code);
}

void Compiler::compile() {
  auto logger = Logger::logger(LOG_LEVEL::INFO);
  auto token = lexer_.next_token();
  while (token.type != TOKEN_TYPE::Eof) {
    printf("%s\n", token.repr().c_str());
    token = lexer_.next_token();
  }

}
