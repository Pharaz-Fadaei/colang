#ifndef IF_BLOCK_H_
#define IF_BLOCK_H_

#include "syntax_tree_node.h"
#include "expression_block.h"
#include "code_block.h"

class IfBlock : public SyntaxTreeNode
{
public:
    ExpressionBlock *condition;
    CodeBlock *ifContent;
    CodeBlock *elseContent;
    IfBlock(SyntaxTreeNode *condition, SyntaxTreeNode *content);
    IfBlock(SyntaxTreeNode *condition, SyntaxTreeNode *ifCode, SyntaxTreeNode *elseCode);
    ~IfBlock();

    virtual Value Run(Scope *scope);
    virtual std::string typeName();
};
#endif //IF_BLOCK_H_