//
// Created by Colin.Wang on 2022/2/18.
//

#include "common/logger.h"
#include "io.h"
#include "compiler.h"

using namespace scc;

Compiler::Compiler(std::string_view source_filename) {
  auto source_code = read_file_string(source_filename);
  auto lexer = std::make_unique<Lexer>(source_code);
  parser_ = Parser(std::move(lexer));
}

void Compiler::compile() {
//  auto token = lexer_.next_token();
//  while (token.type != TOKEN_TYPE::Eof) {
//    printf("%s\n", token.repr().c_str());
//    token = lexer_.next_token();
//  }
  auto ret = parser_.parse();
  AstVisitor visitor(std::move(ret));
  visitor.visit(2);
}
