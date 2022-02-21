//
// Created by Colin.Wang on 2022/2/18.
//

#include "common/logger.h"
#include "io.h"
#include "ast_visitor.h"
#include "compiler.h"

using namespace scc;

Compiler::Compiler(std::string_view filename) {
  auto source_code = read_file_string(filename);
  parser_ = std::make_unique<Parser>(source_code);
}

void Compiler::compile() {
  auto ret = parser_->parse();
  AstVisitor visitor(std::move(ret));
  visitor.visit();
}

void Compiler::compile(const std::string& source_code) {
  auto parser = std::make_unique<Parser>(source_code);
  auto ret = parser->parse();
  AstVisitor visitor(std::move(ret));
  visitor.visit();
}
