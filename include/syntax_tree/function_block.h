#ifndef FUNCTION_BLOCK_H_
#define FUNCTION_BLOCK_H_

#include "syntax_tree_node.h"
#include "parameters_block.h"
#include "code_block.h"
#include "expression_block.h"

class FunctionBlock : public SyntaxTreeNode
{
private:

public:
    std::string name;
    ParametersBlock *params;
    CodeBlock *code;
    ExpressionBlock *returnExpression;
    FunctionBlock(std::string *name, SyntaxTreeNode *params, SyntaxTreeNode *code, int type);

    // 0: CodeBlock
    // 1: ReturnExpression
    int type;

    ~FunctionBlock();

    virtual Value Run(Scope *scope);
    virtual std::string typeName();

};
#endif //FUNCTION_BLOCK_H_