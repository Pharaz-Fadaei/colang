#include "syntax_tree/assignment_block.h"
#include "syntax_tree/variable.h"
#include "utility.cpp"

AssignmentBlock::AssignmentBlock(std::string *name, SyntaxTreeNode *expr, int type)
{
    this->name = *name;
    delete name;
    this->expr = (ExpressionBlock*)expr;
    this->index = NULL;
    this->type = type;
}
AssignmentBlock::AssignmentBlock(std::string *name, SyntaxTreeNode *index, SyntaxTreeNode *expr)
{
    this->name = *name;
    delete name;
    this->index = (ExpressionBlock*)index;
    this->expr = (ExpressionBlock*)expr;
    this->type = 1;
}
AssignmentBlock::~AssignmentBlock()
{
    delete this->index;
    delete this->expr;
}
Value AssignmentBlock::Run(Scope *scope)
{
    int t = this->type;
    Value val = this->expr->Run(scope);
    Variable *var = scope->getVar(this->name);
    if(t == 0)
    {
        var->value = val;
    }
    else if(t == 1)
    {
        Value index = this->index->Run(scope);
        var->value.setArrayValue(index, val);
    }
    if(t == 2)
    {
        int arrSize = var->value.getArraySize();
        Value index;
        index.setIntegralValue(arrSize);
        if(var->value.containsKey(index))
            Utility::error("You have to assign a key and a value in order to add something to your dictionary.");
        var->value.setArrayValue(index, val);
    }
    return val;
}

std::string AssignmentBlock::typeName()
{
    return "AssignmentBlock";
}
