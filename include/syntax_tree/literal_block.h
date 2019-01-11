#ifndef LITERAL_BLOCK_H_
#define LITERAL_BLOCK_H_

#include "syntax_tree_node.h"

class LiteralBlock : public SyntaxTreeNode
{
private:
    std::string getEscapedString(const std::string& str) const;


public:
    Value value;
    LiteralBlock(Value value);
    LiteralBlock(std::string *str, ValueType type);

    virtual Value Run(Scope *scope);
    virtual std::string typeName();
};
#endif //LITERAL_BLOCK_H_