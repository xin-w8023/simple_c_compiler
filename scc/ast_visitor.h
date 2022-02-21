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

  AstVisitor(std::unique_ptr<AstBaseNode>&& root);

  virtual void visit();

  virtual ~AstVisitor() = default;

 private:
  void print_biexpr_ast(AstBaseNode *root, std::string indent);

  void print_unexpr_ast(AstBaseNode *root, std::string indent);

  void print_var_ast(AstBaseNode* root, std::string indent);

  void print_const_ast(AstBaseNode* root, std::string indent);

  void print_ast(AstBaseNode* root, std::string indent);

 protected:
  std::unique_ptr<AstBaseNode> root_;
};

}

#endif //SCC_SCC_AST_VISITOR_H_
