#ifndef SCOPE_H_
#define SCOPE_H_

#include <string>
#include <map>
#include "value.h"

enum ScopeType
{
    SimpleScope,
    LoopScope,
    FunctionScope
};

class Variable;
class FunctionBlock;

class Scope
{
private:
    bool containsReturnValue = false;
    Value returnValue;

    bool breakStatus = false;
    bool continueStatus = false;

public:
    ScopeType type;
    std::map<std::string, Variable*> vars;
    std::map<std::string, FunctionBlock*> funcs;
    Scope *parent;

    Scope();
    ~Scope();

    Scope *getRoot();

    void setVar(std::string s, Variable *value);
    Variable *getVar(std::string s);
    bool hasVar(std::string s, bool recursive);
    void deleteVar(std::string name);
    void deleteVar(std::string name, const Value& index);

    void setFunc(std::string s, FunctionBlock *value);
    FunctionBlock *getFunc(std::string s);
    bool hasFunc(std::string s, bool recursive);

    Scope *getVarScope(std::string name);
    Scope *getFuncScope(std::string name);

    void setReturnValue(Value val);
    bool hasReturnValue();
    Value getReturnValue();

    void setBroken();
    bool isBroken();

    void setContinued();
    bool isContinued();

    bool isEnded();
};
#endif // SCOPE_H_
