#include "syntax_tree/if_block.h"

IfBlock::IfBlock(SyntaxTreeNode *condition, SyntaxTreeNode *content)
{
    this->condition = (ExpressionBlock*)condition;
    this->ifContent = (CodeBlock*) content;
    this->elseContent = NULL;
}
IfBlock::IfBlock(SyntaxTreeNode *condition, SyntaxTreeNode *ifCode, SyntaxTreeNode *elseCode)
{
    this->condition = (ExpressionBlock*)condition;
    this->ifContent = (CodeBlock*) ifCode;
    this->elseContent = (CodeBlock*) elseCode;
}
IfBlock::~IfBlock()
{
    delete this->condition;
    delete this->ifContent;
    delete this->elseContent;
}


Value IfBlock::Run(Scope *scope)
{
    Value val = this->condition->Run(scope);
    if(val.getIntegralValue())
        this->ifContent->Run(scope);
    else if(this->elseContent != NULL)
        this->elseContent->Run(scope);
    return Value();
}
std::string IfBlock::typeName()
{
    return "IfBlock";
}
