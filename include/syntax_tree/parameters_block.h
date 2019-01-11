#ifndef PARAMETERS_BLOCK_H_
#define PARAMETERS_BLOCK_H_

#include "syntax_tree_node.h"

class ParametersBlock : public SyntaxTreeNode
{
public:
    ParametersBlock();
    virtual std::string typeName();
};
#endif //PARAMETERS_BLOCK_H_