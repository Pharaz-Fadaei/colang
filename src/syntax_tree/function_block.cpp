#include "syntax_tree/function_block.h"

FunctionBlock::FunctionBlock(std::string *name, SyntaxTreeNode *params, SyntaxTreeNode *code, int type = 0)
{
    this->name = *name;
    delete name;
    this->params = (ParametersBlock*)params;
    if(type == 0)
    {
        this->code = (CodeBlock*)code;
        this->returnExpression = NULL;
    }
    else if(type == 1)
    {
        this->code = NULL;
        this->returnExpression = (ExpressionBlock*) code;
    }
    this->type = type;
}
FunctionBlock::~FunctionBlock()
{
    delete this->params;
    delete this->code;
}

Value FunctionBlock::Run(Scope *scope)
{
    if(!scope->hasFunc(this->name, false))
    {
        scope->setFunc(this->name, this);
    }
    if(scope->hasReturnValue())
        return scope->getReturnValue();
    return Value();
}
std::string FunctionBlock::typeName()
{
    return "FunctionBlock";
}
