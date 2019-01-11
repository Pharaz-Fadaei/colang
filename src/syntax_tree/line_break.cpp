#include "syntax_tree/line_block.h"

LineBlock::LineBlock(SyntaxTreeNode *st)
{
    this->addChild(st);
}
Value LineBlock::Run(Scope *scope)
{
    for(int i = 0; i < this->children.size() && !scope->isEnded(); i++)
    {
        if(this->children[i] != NULL)
        {
            SyntaxTreeNode *node = this->children[i];
            node->Run(scope);
        }
    }
    if(scope->hasReturnValue())
        return scope->getReturnValue();
    return Value();
}

std::string LineBlock::typeName()
{
    return "LineBlock";
}
