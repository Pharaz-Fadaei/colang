#ifndef EXPRESSION_BLOCK_H_
#define EXPRESSION_BLOCK_H_

#include <math.h>

#include "syntax_tree_node.h"

enum OperatorType
{
  Assignment,
  Negation,
  Addition,
  Subtraction,
  Multiplication,
  Division,
  Modulo,
  Exponentiation,
  Equality,
  Inequality,
  MoreThan,
  LessThan,
  Meq,
  Leq,
  And,
  Or,
  Not,
  ARRAY,
  NONE
};

class ExpressionBlock : public SyntaxTreeNode
{
public:
  OperatorType type;
  ExpressionBlock(OperatorType operatorType);
  virtual Value Run(Scope *scope);
  virtual std::string typeName();
};
#endif //EXPRESSION_BLOCK_H_
