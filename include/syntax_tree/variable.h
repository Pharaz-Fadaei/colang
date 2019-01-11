#ifndef VARIABLE_H_
#define VARIABLE_H_

#include "syntax_tree_node.h"


class Variable
{
private:
  bool initialized = false;
  Variable();
public:
  Value value;
  std::string name;
  Variable(std::string name);
  Variable(std::string name, Value value);
  Variable(const Variable& block);
};
#endif // VARIABLE_H
