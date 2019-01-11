#ifndef PROGRAM_BLOCK_H_
#define PROGRAM_BLOCK_H_

#include "syntax_tree_node.h"

class ProgramBlocks: public SyntaxTreeNode
{
public:
    ProgramBlocks();
    virtual std::string typeName();
};
#endif //PROGRAM_BLOCK_H_