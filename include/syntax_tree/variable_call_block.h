#ifndef VARIABLE_CALL_BLOCK_
#define VARIABLE_CALL_BLOCK_H_

#include "syntax_tree_node.h"

class VariableCallBlock : public SyntaxTreeNode
{
public:
    std::string name;
    SyntaxTreeNode *index = NULL;
    VariableCallBlock(std::string *name);
    VariableCallBlock(std::string *name, SyntaxTreeNode *index);
    ~VariableCallBlock();

    std::string getName();

    virtual Value Run(Scope *scope);
    virtual std::string typeName();
};
#endif //VARIABLE_CALL_BLOCK_H_