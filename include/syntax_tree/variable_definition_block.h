#ifndef VARIABLEDEFINITIONBLOCK_H_
#define VARIABLEDEFINITIONBLOCK_H_

#include "syntax_tree_node.h"
#include "variable.h"


class VariableDefinitionBlock: public SyntaxTreeNode
{
public:
  std::string name;
  VariableDefinitionBlock(std::string *name);
  VariableDefinitionBlock(std::string *name, SyntaxTreeNode *expr);
  Value Run(Scope *scope);
  Variable *build(Scope *scope);
};
#endif // VARIABLEDEFINITIONBLOCK_H_
