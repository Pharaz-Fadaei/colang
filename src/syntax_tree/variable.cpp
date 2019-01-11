#include "syntax_tree/variable.h"
#include "syntax_tree/assignment_block.h"

Variable::Variable(){}
Variable::Variable(std::string name) : name(name), value(Value())
{
}
Variable::Variable(std::string name, Value value) : name(name), value(value)
{
}
//VariableBlock::VariableBlock(const VariableBlock& block)
//{
//    this->name = block.name;
//    this->value = block.value;
//    this->varType = block.varType;
//}
//VariableBlock *VariableBlock::clone()
//{
//    VariableBlock *block = new VariableBlock();
//    block->name = this->name;
//    block->value = this->value;
//    block->varType = this->varType;
//    return block;
//}
