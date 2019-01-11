#include "syntax_tree/endline_block.h"

EndLineBlock::EndLineBlock(EndLineType type)
{
    this->type = type;
}
EndLineBlock::EndLineBlock(SyntaxTreeNode *expr)
{
    this->expr = (ExpressionBlock*) expr;
    this->type = ReturnEnd;
}
EndLineBlock::~EndLineBlock()
{
    delete this->expr;
}


Value EndLineBlock::Run(Scope *scope)
{
    if(this->type == ContinueEnd)
        scope->setContinued();
    else if(this->type == BreakEnd)
        scope->setBroken();
    else
    {
        Value value;
        if(this->expr != NULL)
            value = this->expr->Run(scope);
        scope->setReturnValue(value);
        return value;
    }
    return Value();
}
std::string EndLineBlock::typeName()
{
    return "ReturnBlock";
}
