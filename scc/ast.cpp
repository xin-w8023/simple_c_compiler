//
// Created by Colin.Wang on 2022/2/19.
//

#include "ast.h"

using namespace scc;

AstVisitor::AstVisitor(std::unique_ptr<AstBase>&& root)
  : root_(std::move(root)) {

}

void AstVisitor::visit(int order) {
  print_ass_ast(root_.get());
}

void AstVisitor::print_ass_ast(AstBase* root) {
  auto* node = reinterpret_cast<BinaryExprNode*>(root);
  print_ast(node->left.get());
  print_ast(node->right.get());
  printf("[%s] ", node->content.c_str());
}

void AstVisitor::print_var_ast(AstBase* root) {
  printf("[%s] ", root->content.c_str());
}

void AstVisitor::print_const_ast(AstBase* root) {
  auto* node = reinterpret_cast<ConstantExprNode*>(root);
  printf("[%s] ", node->content.c_str());
}

void AstVisitor::print_ast(AstBase* root) {
  if (!root)
    return;
  if (root->type == AST_TYPE::Expression || root->type == AST_TYPE::Assignment) {
    print_ass_ast(root);
  } else if (root->type == AST_TYPE::Variable){
    print_var_ast(root);
  } else if (root->type == AST_TYPE::Constant) {
    print_const_ast(root);
  }
}
