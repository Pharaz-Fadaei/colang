#ifndef FUNCTION_ARGUMENTS_H_
#define FUNCTION_ARGUMENTS_H_

#include "syntax_tree_node.h"

class FunctionArguments : public SyntaxTreeNode
{
public:
    FunctionArguments();
    virtual std::string typeName();
};
#endif // FUNCTION_ARGUMENTS_H_
