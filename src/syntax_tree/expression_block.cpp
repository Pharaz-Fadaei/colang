#include <iostream>
#include <math.h>

#include "syntax_tree/expression_block.h"
#include "utility.cpp"

ExpressionBlock::ExpressionBlock(OperatorType operatorType)
{
  this->type = operatorType;
}
Value ExpressionBlock::Run(Scope *scope)
{
  Value val, v1, v2;
  std::string s1, s2;
  int b;
  switch (this->type)
  {
  case Assignment:
    val = this->children[1]->Run(scope);
    break;
  case Negation:
    val = this->children[0]->Run(scope).negate();
    break;
  case Addition:
    val = this->children[0]->Run(scope) + this->children[1]->Run(scope);
    break;
  case Subtraction:
    val = this->children[0]->Run(scope) - this->children[1]->Run(scope);
    break;
  case Multiplication:
    val = this->children[0]->Run(scope) * this->children[1]->Run(scope);
    break;
  case Division:
    val = this->children[0]->Run(scope) / this->children[1]->Run(scope);
    break;
  case Modulo:
    val = this->children[0]->Run(scope) % this->children[1]->Run(scope);
    break;
  case Exponentiation:
    v1 = this->children[0]->Run(scope);
    v2 = this->children[1]->Run(scope);
    val = v1.exponentiate(v2);
    break;
  case Equality:
    val.setIntegralValue(this->children[0]->Run(scope) == this->children[1]->Run(scope));
    break;
  case Inequality:
    val.setIntegralValue(!(this->children[0]->Run(scope) == this->children[1]->Run(scope)));
    break;
  case MoreThan:
    val.setIntegralValue(this->children[0]->Run(scope) > this->children[1]->Run(scope));
    break;
  case LessThan:
    val.setIntegralValue(this->children[0]->Run(scope) < this->children[1]->Run(scope));
    break;
  case Meq:
    val.setIntegralValue(this->children[0]->Run(scope) >= this->children[1]->Run(scope));
    break;
  case Leq:
    val.setIntegralValue(this->children[0]->Run(scope) <= this->children[1]->Run(scope));
    break;
  case And:
    val.setIntegralValue(this->children[0]->Run(scope).getIntegralValue() && this->children[1]->Run(scope).getIntegralValue());
    break;
  case Or:
    val.setIntegralValue(this->children[0]->Run(scope).getIntegralValue() || this->children[1]->Run(scope).getIntegralValue());
    break;
  case Not:
    val.setIntegralValue(!(this->children[0]->Run(scope).getIntegralValue()));
    break;
  case ARRAY:
    val = this->children[0]->Run(scope).getArrayValue(this->children[1]->Run(scope));
    break;
  case NONE:
    val = this->children[0]->Run(scope);
    break;
  }
  return val;
}
std::string ExpressionBlock::typeName()
{
  return "ExpressionBlock";
}
