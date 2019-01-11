#ifndef FUNCTION_CALL_BLOCK_H_
#define FUNCTION_CALL_BLOCK_H_

#include <stdarg.h>

#include "syntax_tree_node.h"
#include "function_arguments.h"

class FunctionCallBlock : public SyntaxTreeNode
{
public:
    FunctionArguments *args;
    std::string name;


    FunctionCallBlock(std::string *name, SyntaxTreeNode *arguments);
    ~FunctionCallBlock();

    virtual Value Run(Scope *scope);
    virtual std::string typeName();

private:
    void print(const Value& val);
    void println();
    void println(const Value& val);
    void checkParameters(bool checkTypes, int n, ...);

};
#endif // FUNCTION_CALL_BLOCK_H_
