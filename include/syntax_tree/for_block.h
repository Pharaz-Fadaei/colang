#ifndef FOR_BLOCK_H_
#define FOR_BLOCK_H_

#include "syntax_tree_node.h"
#include "expression_block.h"
#include "variable_definition_block.h"
#include "code_block.h"
#include "scope.h"

enum ForType
{
    FOR_TYPE_NORMAL,
    FOR_TYPE_RANGED
};

class ForBlock : public SyntaxTreeNode
{
    //0 : default for block
    //1 : range for block
    ForType type;
public:
    VariableDefinitionBlock *variableBuilder = NULL;
    ExpressionBlock *e1 = NULL;
    ExpressionBlock *e2 = NULL;
    ExpressionBlock *e3 = NULL;
    CodeBlock *code = NULL;
    CodeBlock *elseBlock = NULL;
    ForBlock(SyntaxTreeNode *e1, SyntaxTreeNode *e2, SyntaxTreeNode *e3, SyntaxTreeNode *code, SyntaxTreeNode *elseBlock);
    ForBlock(std::string *varName, SyntaxTreeNode *rangeStart, SyntaxTreeNode *rangeEnd, SyntaxTreeNode *code, SyntaxTreeNode *elseBlock);
    ~ForBlock();

    virtual Value Run(Scope *scope);
    virtual std::string typeName();
};
#endif //FOR_BLOCK_H_