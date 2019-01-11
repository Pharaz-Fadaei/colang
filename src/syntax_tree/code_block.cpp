#include "syntax_tree/code_block.h"

CodeBlock::CodeBlock(SyntaxTreeNode *content)
{
    this->content = content;
}
CodeBlock::~CodeBlock()
{
    delete this->content;
}
Value CodeBlock::Run(Scope *scope)
{
//    this->scope = new Scope();
//    this->scope->parent = scope;
//    this->scope->type = this->scopeType;
    Scope *newScope = new Scope();
    newScope->parent = scope;
    newScope->type = this->scopeType;
    Value result = this->content->Run(newScope);
    delete newScope;
    return result;
}
std::string CodeBlock::typeName()
{
    return "CodeBlock";
}
