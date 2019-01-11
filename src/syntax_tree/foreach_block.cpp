#include "syntax_tree/foreach_block.h"
#include "utility.cpp"


ForeachBlock::ForeachBlock(std::string *item, SyntaxTreeNode *arr, SyntaxTreeNode *code, SyntaxTreeNode *elseBlock)
{
    this->type = FOREACH_TYPE_ITEM;
    this->arr = (ExpressionBlock*)arr;
    this->code = (CodeBlock*)code;
    this->elseBlock = (CodeBlock*)elseBlock;

    this->keyBuilder = NULL;
    //VariableDefinitionBlock handles deletion of item
    this->itemBuilder = new VariableDefinitionBlock(item);
}
ForeachBlock::ForeachBlock(std::string *key, std::string *value, SyntaxTreeNode *arr, SyntaxTreeNode *code, SyntaxTreeNode *elseBlock)
{
    this->type = FOREACH_TYPE_KEYVALUE;
    this->arr = (ExpressionBlock*)arr;
    this->code = (CodeBlock*)code;
    this->elseBlock = (CodeBlock*)elseBlock;

    //VariableDefinitionBlock handles deletion of strings
    this->keyBuilder = new VariableDefinitionBlock(key);
    this->itemBuilder = new VariableDefinitionBlock(value);
}


ForeachBlock::~ForeachBlock()
{
    delete this->arr;
    delete this->code;

    if(this->keyBuilder != NULL)
        delete this->keyBuilder;
    delete this->itemBuilder;
}

Value ForeachBlock::Run(Scope *scope)
{
    Scope *newScope = new Scope();
    newScope->parent = scope;
    newScope->type = LoopScope;
    Variable *item = this->itemBuilder->build(newScope);
    Variable *key = this->type == FOREACH_TYPE_KEYVALUE ? this->keyBuilder->build(newScope) : NULL;

    Value arr = this->arr->Run(newScope);
    if(arr.getType() == STRING_VALUE)
    {
        std::string strValue = arr.getStringValue();
        for(int i = 0; i < strValue.size(); i++)
        {
            item->value.setStringValue(std::string(1, strValue[i]));
            if(key != NULL)
                key->value.setIntegralValue(i);
            this->code->Run(newScope);
        }
    }
    else if(arr.getType() == ARRAY_VALUE)
    {
        const std::map<Value, Value>& values = arr.getArray();
        for(std::map<Value, Value>::const_iterator it = values.begin(); it != values.end(); it++)
        {
            item->value = it->second;
            if(key != NULL)
                key->value = it->first;
            this->code->Run(newScope);
        }
    }
    else
    {
        Utility::error("You cannot iterate through a non-array variable.");
    }

    if(this->elseBlock != NULL && !newScope->isBroken())
        this->elseBlock->Run(scope);

    return Value();
}
std::string ForeachBlock::typeName()
{
    return "ForeachBlock";
}
