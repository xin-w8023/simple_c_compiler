//
// Created by Colin.Wang on 2022/2/19.
//

#include "ast.h"

using namespace scc;

AstVisitor::AstVisitor(std::unique_ptr<AstBase>&& root)
  : root_(std::move(root)) {

}

void AstVisitor::visit() {
  print_ast(root_.get(), "");
}

void AstVisitor::print_expr_ast(AstBase* root, std::string indent) {
  auto* node = reinterpret_cast<BinaryExprNode*>(root);
  printf("%s[%s]:%s %s\n", indent.c_str(), node->content.c_str(),
         op_to_str.at(node->op).c_str(), ast_type_str.at(node->type).c_str());
  indent += "|  ";
  print_ast(node->left.get(), indent);
  print_ast(node->right.get(), indent);
}

void AstVisitor::print_var_ast(AstBase* root, std::string indent) {
  printf("%s[%s]:%s\n", indent.c_str(), root->content.c_str(),ast_type_str.at(root->type).c_str() );
}

void AstVisitor::print_const_ast(AstBase* root, std::string indent) {
  auto* node = reinterpret_cast<ConstantExprNode*>(root);
  printf("%s[%s]:%s\n", indent.c_str(), node->content.c_str(), ast_type_str.at(node->type).c_str());
}

void AstVisitor::print_ast(AstBase* root, std::string indent) {
  if (!root)
    return;
  if (root->type == AST_TYPE::Expression) {
    print_expr_ast(root, indent);
  } else if (root->type == AST_TYPE::Variable){
    print_var_ast(root, indent);
  } else if (root->type == AST_TYPE::Constant) {
    print_const_ast(root, indent);
  }
}
