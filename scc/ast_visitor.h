//
// Created by Colin.Wang on 2022/2/21.
//

#ifndef SCC_SCC_AST_VISITOR_H_
#define SCC_SCC_AST_VISITOR_H_

#include <memory>

#include "ast.h"


namespace scc {

class AstVisitor {
 public:

  AstVisitor() = default;

  explicit AstVisitor(std::unique_ptr<AstBaseNode>&& root);

  virtual void visit();

  virtual ~AstVisitor() = default;

 private:
  void visit_binary_expr(AstBaseNode *root, std::string indent);

  void visit_unary_expr(AstBaseNode *root, std::string indent);

  static void visit_variable_expr(AstBaseNode* root, const std::string& indent);

  static void visit_const_expr(AstBaseNode* root, const std::string& indent);

  void visit_expr(AstBaseNode* root, const std::string& indent = "");

 protected:
  std::unique_ptr<AstBaseNode> root_;
};

}

#endif //SCC_SCC_AST_VISITOR_H_
