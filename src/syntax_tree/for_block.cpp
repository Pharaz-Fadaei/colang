#include "syntax_tree/for_block.h"
#include "syntax_tree/variable_definition_block.h"


ForBlock::ForBlock(SyntaxTreeNode *e1, SyntaxTreeNode *e2, SyntaxTreeNode *e3, SyntaxTreeNode *code, SyntaxTreeNode *elseBlock)
{
    this->type = FOR_TYPE_NORMAL;

    this->e1 = (ExpressionBlock*) e1;
    this->e2 = (ExpressionBlock*) e2;
    this->e3 = (ExpressionBlock*) e3;

    this->code = (CodeBlock*)code;
    this->elseBlock = (CodeBlock*)elseBlock;
    //this->code->scopeType = LoopScope;
}
ForBlock::ForBlock(std::string *varName, SyntaxTreeNode *rangeStart, SyntaxTreeNode *rangeEnd, SyntaxTreeNode *code, SyntaxTreeNode *elseBlock)
{
    this->type = FOR_TYPE_RANGED;

    //VariableDefinitionBlock handles deletion of varName
    this->variableBuilder = new VariableDefinitionBlock(varName);

    this->e1 = (ExpressionBlock*) rangeStart;
    this->e2 = (ExpressionBlock*) rangeEnd;

    this->code = (CodeBlock*)code;
    this->elseBlock = (CodeBlock*)elseBlock;
}
ForBlock::~ForBlock()
{
    delete this->variableBuilder;
    delete this->e1;
    delete this->e2;
    delete this->e3;
    delete this->code;
}

Value ForBlock::Run(Scope *scope)
{
    Scope *newScope = new Scope();
    newScope->parent = scope;
    newScope->type = LoopScope;

    if(this->type == FOR_TYPE_NORMAL)
    {
        if(this->e1 != NULL)
            this->e1->Run(newScope);
        bool e2IsNull = this->e2 == NULL, e3IsNull = this->e3 == NULL;
        for(; (e2IsNull || this->e2->Run(newScope).getIntegralValue()) && !newScope->isBroken(); (!e3IsNull) ? this->e3->Run(newScope) : Value())
        {
            if(this->code != NULL)
                this->code->Run(newScope);
        }
    }
    else if(this->type == FOR_TYPE_RANGED)
    {
        Variable *var = this->variableBuilder->build(newScope);
        var->value.setIntegralValue(this->e1->Run(newScope).getIntegralValue());
        int last = this->e2->Run(newScope).getIntegralValue();
        for(int i = var->value.getIntegralValue(); i < last && !newScope->isBroken(); i++, var->value.setIntegralValue(i))
        {
            if(this->code != NULL)
                this->code->Run(newScope);
        }
    }

    if(this->elseBlock != NULL && !newScope->isBroken())
        this->elseBlock->Run(scope);

    delete newScope;

    return Value();
}
std::string ForBlock::typeName()
{
    return "ForBlock";
}
