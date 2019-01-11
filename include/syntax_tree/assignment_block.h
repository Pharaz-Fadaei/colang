#ifndef ASSIGNMENT_BLOCK_H_
#define ASSIGNMENT_BLOCK_H_

#include "syntax_tree_node.h"
#include "expression_block.h"

class AssignmentBlock : public SyntaxTreeNode
{
private:
    std::string name;
    ExpressionBlock *expr = NULL;
    ExpressionBlock *index = NULL;
    //0: var
    //1: arr
    //2: arr add
    int type;
public:
    AssignmentBlock(std::string *name, SyntaxTreeNode *expr, int type);
    AssignmentBlock(std::string *name, SyntaxTreeNode *index, SyntaxTreeNode *expr);
    ~AssignmentBlock();
    virtual Value Run(Scope *scope);
    virtual std::string typeName();
};

#endif // ASSIGNMENT_BLOCK_H_