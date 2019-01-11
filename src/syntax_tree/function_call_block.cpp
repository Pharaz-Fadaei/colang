#include <iostream>
#include <sstream>

#include "syntax_tree/function_call_block.h"
#include "syntax_tree/function_block.h"
#include "syntax_tree/variable_definition_block.h"
#include "syntax_tree/endline_block.h"
#include "syntax_tree/variable_call_block.h"
#include "utility.cpp"

FunctionCallBlock::FunctionCallBlock(std::string *name, SyntaxTreeNode *args)
{
    this->name = *name;
    delete name;
    this->args = NULL;
    if(args != NULL)
        this->args = (FunctionArguments*)args;
}
FunctionCallBlock::~FunctionCallBlock()
{
    delete this->args;
}


Value FunctionCallBlock::Run(Scope *scope)
{
    if(this->name == "Print")
    {
        if(this->args == NULL)
        {
            return Value();
        }
        Value v = this->args->getChild(0)->Run(scope);
        this->print(v);
        return v;
    }
    else if(this->name == "PrintLn" || this->name == "PrintLine")
    {
        if(this->args == NULL)
        {
            this->println();
            return Value();
        }
        Value v = this->args->getChild(0)->Run(scope);
        this->println(v);
        return v;
    }
    else if(this->name == "Count")
    {
        Value v = this->args->getChild(0)->Run(scope);
        Value ret;
        ret.setIntegralValue(v.getType() == STRING_VALUE ? v.getStringValue().size() : (v.getType() == ARRAY_VALUE) ? v.getArraySize() : 0);

        return ret;
    }
    else if(this->name == "ReadInt")
    {
        Value ret;
        int n;
        std::cin >> n;
        ret.setIntegralValue(n);
        return ret;
    }
    else if(this->name == "ReadDouble")
    {
        Value ret;
        double x;
        std::cin >> x;
        ret.setDoubleValue(x);
        return ret;
    }
    else if(this->name == "ReadString")
    {
        Value ret;
        std::string str;
        std::cin >> str;
        ret.setStringValue(str);
        return ret;
    }
    else if(this->name == "ReadLine")
    {
        Value ret;
        std::string str;
        std::cin.clear();
        std::cin.sync();
        std::getline(std::cin, str);
        ret.setStringValue(str);
        return ret;
    }
    else if(this->name == "Clear")
    {
        VariableCallBlock *variable = dynamic_cast<VariableCallBlock*> (this->args->getChild(0));
        if(variable == nullptr)
            Utility::error("Colang interpreter currently only supports clearing a direct call to a variable.");        

        Variable *var = scope->getVar(variable->getName());
        Value& value = var->value;

        value.clearValues();
    }
    else if(this->name == "ContainsKey")
    {
        this->checkParameters(false, 2);
        Value arr = this->args->getChild(0)->Run(scope);
        Value key = this->args->getChild(1)->Run(scope);

        return Value((int)arr.containsKey(key));
    }
    else if(this->name == "GetKeys")
    {
        Value arr = this->args->getChild(0)->Run(scope);
        return arr.getKeys();
    }
    else if(this->name == "Delete")
    {
        VariableCallBlock *variable = dynamic_cast<VariableCallBlock*> (this->args->getChild(0));
        if(variable == nullptr)
            Utility::error("You cannot delete a non-variable expression.");
        else
        {
            if(variable->index == NULL)
                scope->deleteVar(variable->getName());
            else
            {
                SyntaxTreeNode *indexNode = variable->index;
                Value index = indexNode->Run(scope);

                scope->deleteVar(variable->getName(), index);
            }
        }
    }
    else if(this->name == "ToInt")
    {
        Value v = this->args->getChild(0)->Run(scope);

        return Value(v.toInt());
    }
    else if(this->name == "ToDouble")
    {
        Value v = this->args->getChild(0)->Run(scope);

        return Value(v.toDouble());
    }
    else if(this->name == "ToString")
    {
        Value v = this->args->getChild(0)->Run(scope);

        return Value(v.toString());
    }
    else if(this->name == "Array")
    {
        if(this->args->countChildren() == 0)
        {
            Value v;
            v.convertToArray();
            return v;
        }
        Value v = this->args->getChild(0)->Run(scope);
        Value _r;
        _r.convertToArray();
        int n = v.getIntegralValue();
        for(int i = 0; i < n; i++)
        {
            _r.setArrayIndexedValue(Value());
        }
        return _r;
    }
    else if(this->name == "Add")
    {
        int nChildren = this->args->countChildren();
        if(nChildren < 2)
            Utility::error("Add function requires an array and some values to add.");

        VariableCallBlock *array = dynamic_cast<VariableCallBlock*> (this->args->getChild(0));
        if(array == nullptr)
            Utility::error("Colang interpreter currently only supports adding to a direct call of an array.");        

        Variable *var = scope->getVar(array->getName());
        Value& arr = var->value;


        if(arr.getType() != EMPTY_VALUE && arr.getType() != ARRAY_VALUE)
            Utility::error("Add function excepts it's first parameter to be an array.");
        if(arr.getType() == EMPTY_VALUE)
            arr.convertToArray();

        for(int i = 1; i < nChildren; i++)
            arr.setArrayIndexedValue(this->args->getChild(i)->Run(scope));
        
        return Value();
    }
    else if(this->name == "FormatString")
    {
        std::string format = this->args->getChild(0)->Run(scope).getStringValue();

        int n = this->args->countChildren() - 1;
        std::vector<std::string> values(n);
        for(int i = 0; i < n; i++)
            values[i] = this->args->getChild(i + 1)->Run(scope).toString();

        std::ostringstream oss;

        bool opened = false;
        std::string temp;
        n = format.size();
        int j;
        for(int i = 0; i < n; i++)
        {
            if(!opened)
            {
                if(format[i] == '{' && i != n - 1 && format[i + 1] != '{')
                    opened = true;
                else
                    oss << format[i];
            }
            else
            {
                if(format[i] == '}')
                {
                    opened = false;
                    j = Utility::StringToInt(temp);
                    temp = "";
                    if(j >= n)
                        Utility::error("Invalid format for string.");
                    oss << values[j];
                }
                else
                    temp += format[i];
            }
        }
        return Value(oss.str());
    }
//TODO:   Argument Type Checking     Delete Variable   Clear, ToInt, ContainsKey, GetKeys
    else
    {
        FunctionBlock *func = scope->getFunc(this->name);
        ParametersBlock *params = func->params;
        Scope *e = new Scope();
        e->type = FunctionScope;
        e->parent = scope->getFuncScope(this->name);
        std::vector<Variable*> arguments;
        if(params != NULL)
        {
            for(int i = 0; i < params->countChildren(); i++)
            {
                Variable *var = ((VariableDefinitionBlock*)params->getChild(i))->build(e);
                var->value = this->args->getChild(i)->Run(scope);
                arguments.push_back(var);
                //e->setVar(var->name, var);
            }
        }
        Value val;
        // Full function
        if(func->type == 0)
            val = func->code->Run(e);
        // One-Line Function
        else if(func->type == 1)
        {
            EndLineBlock *returns = new EndLineBlock(func->returnExpression);
            val = returns->Run(e);
            delete returns;
        }
        delete e;
        return val;
    }
    return Value(EMPTY_VALUE);
}
std::string FunctionCallBlock::typeName()
{
    return "FunctionCallBlock";
}

void FunctionCallBlock::print(const Value& val)
{
    std::cout << val.toString();
}
void FunctionCallBlock::println()
{
    std::cout << std::endl;
}
void FunctionCallBlock::println(const Value& val)
{
    std::cout << val.toString() << std::endl;
}

void FunctionCallBlock::checkParameters(bool checkTypes, int n, ...)
{
    if(n != this->args->countChildren())
        Utility::error("Function " + this->name + " expects exactly " + Utility::IntToString(n) + " paremters. " + Utility::IntToString(this->args->countChildren()) + " passed.");
   /* if(!checkTypes)
        return;
    va_list args;
    va_start(args, n);
    VariableType type, typeInt;
    bool ok = true;
    for(int i = 0; i < n; i++)
    {
        typeInt = va_arg(i, int);
        if(typeInt == -1)
            continue;
        type = (VariableType)typeInt;
        Variable *var = ((VariableDefinitionBlock*)params->getChild(i))->build(e);
        var->value = this->args->getChild(i)->Run(scope);
        if(type != this->args->getChild(i)->)
    }*/
}
