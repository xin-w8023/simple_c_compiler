//
// Created by Colin.Wang on 2022/2/19.
//

#ifndef SCC_SCC_AST_H_
#define SCC_SCC_AST_H_

#include <variant>
#include <unordered_map>
#include <memory>
#include <string>

namespace scc {

enum class AST_TYPE {
  UnExpression,
  BiExpression,
  Variable,
  Constant,
};


enum class BinaryOperator {
  BadOp,
  Assignment,
  Plus,
  Minus,
  Star,
  Slash
};

enum class UnaryOperator {
  BadOp,
  Plus,
  Minus,
};

struct AstBaseNode {
  AST_TYPE type{};
  std::string content{};
};

struct BinaryExprNode : AstBaseNode {
  BinaryOperator op;
  std::unique_ptr<AstBaseNode> left;
  std::unique_ptr<AstBaseNode> right;
  BinaryExprNode() = default;
  BinaryExprNode(std::unique_ptr<AstBaseNode>&& l,
                 BinaryOperator bo,
                 std::unique_ptr<AstBaseNode>&& r) {
    left = std::move(l);
    right = std::move(r);
    op = bo;
  }
};

struct UnaryExprNode : AstBaseNode {
  UnaryOperator op;
  std::unique_ptr<AstBaseNode> right;
  UnaryExprNode() = default;
  UnaryExprNode(UnaryOperator uo,
                std::unique_ptr<AstBaseNode>&& rhs) {
    right = std::move(rhs);
    op = uo;
  }
};

struct ConstantExprNode : AstBaseNode {

  std::variant<int, float, std::string> value{};

  // 0: int
  // 1: float
  // 2: string
  int value_type{0};
};

}

#endif //SCC_SCC_AST_H_
