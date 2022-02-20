//
// Created by Colin.Wang on 2022/2/19.
//

#ifndef SCC_SCC_AST_H_
#define SCC_SCC_AST_H_

#include <memory>
#include <string>

namespace scc {

enum class AST_TYPE {
  Assignment,
  Expression,
  Variable,
  Constant,
};

enum class BinaryOperator {
  Assignment,
  Plus,
  Minus,
  Star,
  Slash
};

struct AstBase {
  AST_TYPE type{};
  std::string content{};
};

struct BinaryExprNode : AstBase {
  BinaryOperator op;
  std::unique_ptr<AstBase> left;
  std::unique_ptr<AstBase> right;
};

struct ConstantExprNode : AstBase {
  int value{};
};

class AstVisitor {
 public:

  AstVisitor() = default;

  AstVisitor(std::unique_ptr<AstBase>&& root);

  // 0: pre-order
  // 1: mid-order
  // 2: post-order
  // 3: level-order
  void visit(int order);

 private:
  void print_ass_ast(AstBase *root);

  void print_var_ast(AstBase* root);

  void print_const_ast(AstBase* root);

  void print_ast(AstBase* root);

 private:
  std::unique_ptr<AstBase> root_;
};





}

#endif //SCC_SCC_AST_H_
