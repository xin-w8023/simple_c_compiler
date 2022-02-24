//
// Created by Colin.Wang on 2022/2/21.
//

#include "syntax_helper.h"
#include "ast_visitor.h"

using namespace scc;

AstVisitor::AstVisitor(std::unique_ptr<AstBaseNode>&& root)
    : root_(std::move(root)) {

}

void AstVisitor::visit() {
  this->visit_expr(root_.get());
}

void AstVisitor::visit_unary_expr(AstBaseNode *root, std::string indent) {
  auto* node = reinterpret_cast<UnaryExprNode*>(root);
  printf("%sUnaryExpression\n", indent.c_str());
  indent += "*  ";
  printf("%s[%s]: %s\n", indent.c_str(), node->content.c_str(),
         SyntaxHelper::unary_op2str(node->op).data());
  // ├──
  // └──
  this->visit_expr(node->right.get(), indent);

}

void AstVisitor::visit_binary_expr(AstBaseNode* root, std::string indent) {
  auto* node = reinterpret_cast<BinaryExprNode*>(root);
  printf("%sBinaryExpression\n", indent.c_str());
  indent += "*  ";
  this->visit_expr(node->left.get(), indent);
  printf("%s[%s]: %s\n", indent.c_str(), node->content.c_str(),
         SyntaxHelper::binary_op2str(node->op).data());
  this->visit_expr(node->right.get(), indent);
}

void AstVisitor::visit_variable_expr(AstBaseNode* root, const std::string& indent) {
  printf("%s[%s]: %s\n", indent.c_str(), root->content.c_str(),
         SyntaxHelper::ast_type2str(root->type).data() );
}

void AstVisitor::visit_const_expr(AstBaseNode* root, const std::string& indent) {
  auto* node = reinterpret_cast<ConstantExprNode*>(root);
  printf("%s[%s]: %s\n", indent.c_str(), node->content.c_str(),
         SyntaxHelper::ast_type2str(node->type).data());
}

void AstVisitor::visit_expr(AstBaseNode* root, const std::string& indent) {
  if (!root)
    return;
  if (root->type == AST_TYPE::UnExpression) {
    this->visit_unary_expr(root, indent);
  } else if (root->type == AST_TYPE::BiExpression) {
    this->visit_binary_expr(root, indent);
  } else if (root->type == AST_TYPE::Variable){
    this->visit_variable_expr(root, indent);
  } else if (root->type == AST_TYPE::Constant) {
    this->visit_const_expr(root, indent);
  }
}

