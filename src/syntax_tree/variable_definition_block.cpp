#include "syntax_tree/variable_definition_block.h"
#include "syntax_tree/expression_block.h"
#include "utility.cpp"


VariableDefinitionBlock::VariableDefinitionBlock(std::string *name)
{
    this->name = *name;
    delete name;
}
VariableDefinitionBlock::VariableDefinitionBlock(std::string *name, SyntaxTreeNode *expr)
{
    this->name = *name;
    this->addChild(expr);
    delete name;
}
Value VariableDefinitionBlock::Run(Scope *scope)
{
    if(scope->hasVar(this->name, false))
        Utility::error("A variable with the name \"" + this->name + "\" already exists in the current scope. You can't redefine it.");
    Variable *var = new Variable(this->name);
    if(!this->children.empty())
    {
        ExpressionBlock *expr = (ExpressionBlock*)this->children.back();
        var->value = expr->Run(scope);
    }
    scope->setVar(this->name, var);
    return var->value;
}
Variable *VariableDefinitionBlock::build(Scope *scope)
{
    this->Run(scope);
    return scope->getVar(this->name);
}
