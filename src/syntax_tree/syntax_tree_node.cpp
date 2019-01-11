#include <iostream>

#include "syntax_tree/syntax_tree_node.h"

void SyntaxTreeNode::addChild(SyntaxTreeNode *st)
{
    if (st != NULL)
        this->children.push_back(st);
}
SyntaxTreeNode::~SyntaxTreeNode()
{
    for (int i = 0; i < children.size(); i++)
        delete children[i];
}
SyntaxTreeNode *SyntaxTreeNode::getChild(int index)
{
    return this->children[index];
}
int SyntaxTreeNode::countChildren()
{
    return this->children.size();
}
void SyntaxTreeNode::clearChildren()
{
    this->children.clear();
}
Value SyntaxTreeNode::Run(Scope *scope)
{
    for(int i = 0; i < this->children.size() && !scope->isEnded(); i++)
    {
        if(this->children[i] != NULL)
        {
            SyntaxTreeNode *node = this->children[i];
            node->Run(scope);
        }
    }
    return scope->hasReturnValue() ? scope->getReturnValue() : Value();
}
std::string SyntaxTreeNode::typeName()
{
    return "SyntaxTreeNode";
}

void SyntaxTreeNode::x()
{
    std::cout << this->typeName() << std::endl;
}

SyntaxTreeNode *treeRoot;
