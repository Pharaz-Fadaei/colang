#ifndef CODE_BLOCK_H_
#define CODE_BLOCK_H_

#include "syntax_tree_node.h"


class CodeBlock: public SyntaxTreeNode
{
public:
    ScopeType scopeType = SimpleScope;
    SyntaxTreeNode *content = NULL;

    CodeBlock(SyntaxTreeNode *content);
    ~CodeBlock();

    virtual Value Run(Scope *scope);
    virtual std::string typeName();
};
#endif // CODE_BLOCK_H_
