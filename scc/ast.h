//
// Created by Colin.Wang on 2022/2/19.
//

#ifndef SCC_SCC_AST_H_
#define SCC_SCC_AST_H_

#include <unordered_map>
#include <memory>
#include <string>

namespace scc {

enum class AST_TYPE {
  Expression,
  Variable,
  Constant,
};

inline std::unordered_map<AST_TYPE, std::string> ast_type_str = {
    {AST_TYPE::Expression, "Expression"},
    {AST_TYPE::Variable, "Variable"},
    {AST_TYPE::Constant, "Constant"}
};
enum class BinaryOperator {
  Assignment,
  Plus,
  Minus,
  Star,
  Slash
};
inline std::unordered_map<BinaryOperator, std::string> op_to_str = {
    {BinaryOperator::Assignment, "Assignment"},
    {BinaryOperator::Plus, "Plus"},
    {BinaryOperator::Minus, "Minus"},
    {BinaryOperator::Star, "Star"},
    {BinaryOperator::Slash, "Slash"}
};

struct AstBase {
  AST_TYPE type{};
  std::string content{};
};

struct BinaryExprNode : AstBase {
  BinaryOperator op;
  std::unique_ptr<AstBase> left;
  std::unique_ptr<AstBase> right;
  BinaryExprNode() = default;
  BinaryExprNode(std::unique_ptr<AstBase>&& l,
                 BinaryOperator o,
                 std::unique_ptr<AstBase>&& r) {
    left = std::move(l);
    right = std::move(r);
    op = o;
  }
};

struct ConstantExprNode : AstBase {
  int value{};
};

class AstVisitor {
 public:

  AstVisitor() = default;

  AstVisitor(std::unique_ptr<AstBase>&& root);

  virtual void visit();

  virtual ~AstVisitor() = default;

 private:
  void print_expr_ast(AstBase *root, std::string indent);

  void print_var_ast(AstBase* root, std::string indent);

  void print_const_ast(AstBase* root, std::string indent);

  void print_ast(AstBase* root, std::string indent);

 protected:
  std::unique_ptr<AstBase> root_;
};




}

#endif //SCC_SCC_AST_H_
