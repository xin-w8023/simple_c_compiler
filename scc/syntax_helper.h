//
// Created by Colin.Wang on 2022/2/22.
//

#ifndef SCC_SCC_SYNTAX_HELPER_H_
#define SCC_SCC_SYNTAX_HELPER_H_

#include "ast.h"

namespace scc {

class SyntaxHelper {
 public:
  static std::string_view ast_type2str(AST_TYPE type) {
    switch (type) {
      case AST_TYPE::UnExpression: return "UnExpression";
      case AST_TYPE::BiExpression: return "BiExpression";
      case AST_TYPE::Variable: return "Variable";
      case AST_TYPE::Constant: return "Constant";
    }
  }


  static std::string_view binary_op2str(BinaryOperator op) {
    switch (op) {
      case BinaryOperator::Assignment: return "Assignment";
      case BinaryOperator::Plus: return "Plus";
      case BinaryOperator::Minus: return "Minus";
      case BinaryOperator::Star: return "Star";
      case BinaryOperator::Slash: return "Slash";
      case BinaryOperator::BadOp: return "BadOp";
    }
  }

  static std::string_view unary_op2str(UnaryOperator op) {
    switch (op) {
      case UnaryOperator::Plus: return "Positive";
      case UnaryOperator::Minus: return "Negative";
      case UnaryOperator::BadOp: return "BadOp";
    }
  };

};

}

#endif //SCC_SCC_SYNTAX_HELPER_H_
