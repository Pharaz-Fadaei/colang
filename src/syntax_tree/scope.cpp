#include <iostream>

#include "syntax_tree/scope.h"
#include "syntax_tree/variable.h"
#include "utility.cpp"

Scope::Scope()
{
    this->parent = NULL;
    this->type = SimpleScope;
}
Scope::~Scope()
{
    for(std::map<std::string, Variable*>::iterator it = this->vars.begin(); it != vars.end(); it++)
        delete it->second;
}

Scope *Scope::getRoot()
{
    Scope *root = this;
    while(root->parent != NULL)
        root = root->parent;
    return root;
}

void Scope::setVar(std::string name, Variable *var)
{
    this->vars[name] = var;
}

Variable *Scope::getVar(std::string name)
{
    if(this->vars.find(name) == this->vars.end())
    {
        if(this->parent != NULL)
            return this->parent->getVar(name);
        Utility::error("Variable \"" + name + "\" is not defined in this scope.");
    }
    return this->vars[name];
}
void Scope::deleteVar(std::string name)
{
    std::map<std::string, Variable*>::iterator it = this->vars.find(name);
    if(it == this->vars.end())
    {
        if(this->parent != NULL)
            this->parent->deleteVar(name);
    }
    else
        this->vars.erase(it);

}
void Scope::deleteVar(std::string name, const Value& index)
{
    std::map<std::string, Variable*>::iterator it = this->vars.find(name);
    if(it == this->vars.end())
    {
        if(this->parent != NULL)
            this->parent->deleteVar(name);
    }
    else
    {
        it->second->value.deleteArrayValue(index);
    }
}
bool Scope::hasVar(std::string name, bool recursive = true)
{
    bool found = this->vars.find(name) != this->vars.end();
    if(recursive && !found && this->parent != NULL)
        found = this->parent->hasVar(name);
    return found;
}

void Scope::setFunc(std::string name, FunctionBlock *block)
{
    this->funcs[name] = block;
}

FunctionBlock *Scope::getFunc(std::string name)
{
    if(this->funcs.find(name) == this->funcs.end())
    {
        if(this->parent != NULL)
            return this->parent->getFunc(name);
        Utility::error("Function \"" + name + "\" is not defined in this scope.");
    }
    return this->funcs[name];
}
bool Scope::hasFunc(std::string name, bool recursive = true)
{
    bool found = this->funcs.find(name) != this->funcs.end();
    if(recursive && !found && this->parent != NULL)
        found = this->parent->hasFunc(name);
    return found;
}



Scope *Scope::getVarScope(std::string name)
{
    if(this->vars.find(name) == this->vars.end())
    {
        if(this->parent != NULL)
            return this->parent->getVarScope(name);
        Utility::error("Variable \"" + name + "\" is not defined in this scope.");
    }
    return this;
}
Scope *Scope::getFuncScope(std::string name)
{
    if(this->funcs.find(name) == this->funcs.end())
    {
        if(this->parent != NULL)
            return this->parent->getFuncScope(name);
        Utility::error("Function \"" + name + "\" is not defined in this scope.");
    }
    return this;
}




void Scope::setReturnValue(Value val)
{
    this->returnValue = val;
    this->containsReturnValue = true;
    if(this->type < FunctionScope && this->parent != NULL)
        this->parent->setReturnValue(val);
}
bool Scope::hasReturnValue()
{
    return this->containsReturnValue;
}
Value Scope::getReturnValue()
{
    return this->returnValue;
}

void Scope::setBroken()
{
    this->breakStatus = true;
    if(this->type < LoopScope && this->parent != NULL)
        this->parent->setBroken();
}
bool Scope::isBroken()
{
    return this->breakStatus;
}

void Scope::setContinued()
{
    this->continueStatus = true;
    if(this->type < LoopScope && this->parent != NULL)
        this->parent->setContinued();
}
bool Scope::isContinued()
{
    return this->continueStatus;
}

bool Scope::isEnded()
{
    return this->hasReturnValue() || this->isBroken() || this->isContinued();
}
