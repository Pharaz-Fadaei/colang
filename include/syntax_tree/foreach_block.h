#ifndef FOREACH_BLOCK_H_
#define FOREACH_BLOCK_H_

#include "syntax_tree_node.h"
#include "variable_definition_block.h"
#include "expression_block.h"
#include "code_block.h"

enum ForeachType
{
    FOREACH_TYPE_ITEM,
    FOREACH_TYPE_KEYVALUE
};


class ForeachBlock : public SyntaxTreeNode
{
private:
    VariableDefinitionBlock *keyBuilder;
    VariableDefinitionBlock *itemBuilder;
public:
    ForeachType type;
    ExpressionBlock *arr;
    CodeBlock *code;
    CodeBlock *elseBlock;


    ForeachBlock(std::string *item, SyntaxTreeNode *arr, SyntaxTreeNode *code, SyntaxTreeNode *elseBlock);
    ForeachBlock(std::string *key, std::string *value, SyntaxTreeNode *arr, SyntaxTreeNode *code, SyntaxTreeNode *elseBlock);
    ~ForeachBlock();

    virtual Value Run(Scope *scope);
    virtual std::string typeName();
};

#endif // FOREACH_BLOCK_H_
