#ifndef ENDLINE_BLOCK_H_
#define ENDLINE_BLOCK_H_

#include "syntax_tree_node.h"
#include "expression_block.h"

enum EndLineType
{
    ContinueEnd,
    BreakEnd,
    ReturnEnd
};

class EndLineBlock: public SyntaxTreeNode
{
public:
    EndLineType type;
    ExpressionBlock *expr = NULL;
    EndLineBlock(EndLineType type);
    EndLineBlock(SyntaxTreeNode *expr);
    ~EndLineBlock();
    virtual Value Run(Scope *scope);
    virtual std::string typeName();
};
#endif //ENDLINE_BLOCK_H_