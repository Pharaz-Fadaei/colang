#include <iostream>

#include "syntax_tree/variable_call_block.h"
#include "syntax_tree/variable.h"
#include "utility.cpp"

VariableCallBlock::VariableCallBlock(std::string *name)
{
    this->name = *name;
    delete name;
}
VariableCallBlock::VariableCallBlock(std::string *name, SyntaxTreeNode *index)
{
    this->name = *name;
    delete name;
    this->index = index;
}
VariableCallBlock::~VariableCallBlock()
{
    delete this->index;
}

std::string VariableCallBlock::getName()
{
    return this->name;
}


Value VariableCallBlock::Run(Scope *scope)
{
    Variable *var = scope->getVar(this->name);
    if(this->index == NULL)
        return var->value;
    Value indexVal = this->index->Run(scope);
    if(var->value.getType() == STRING_VALUE)
    {
        if(indexVal.getType() != INTEGRAL_VALUE)
            Utility::error("Index must be an integral value.");
        int index = indexVal.getIntegralValue();
        if(index >= var->value.getStringValue().size())
        {
            Utility::error("Index out of range. The string " + this->name + " has only " + Utility::IntToString(var->value.getStringValue().size()) + " member(s). You can't access " + Utility::IntToString(index+1) + "th member");
        }
        Value ret;
        ret.setStringValue(std::string(1, var->value.getStringValue()[index]));
        return ret;
    }
    if(!var->value.containsKey(indexVal))
    {
        Utility::error("Array key doesn't exist.");
    }
    return var->value.getArrayValue(indexVal);
    //return block->value;
}
std::string VariableCallBlock::typeName()
{
    return "VariableCallBlock";
}
