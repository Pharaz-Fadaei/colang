#ifndef LINE_BLOCK_H_
#define LINE_BLOCK_H_

#include "syntax_tree_node.h"

class LineBlock : public SyntaxTreeNode
{
public:
  LineBlock(SyntaxTreeNode *st);
  virtual Value Run(Scope *scope);
  virtual std::string typeName();
};
#endif //LINE_BLOCK_H_