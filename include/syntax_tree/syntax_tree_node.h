#ifndef SYNTAXTREENODE_H_
#define SYNTAXTREENODE_H_

#include <string>
#include <vector>

#include "value.h"
#include "scope.h"

class SyntaxTreeNode
{
private:
public:
  //Scope *scope = NULL;


  virtual Value Run(Scope *env);
  virtual std::string typeName();

  virtual void addChild(SyntaxTreeNode *st);
  SyntaxTreeNode *getChild(int index);
  int countChildren();
  void clearChildren();
  virtual ~SyntaxTreeNode();
  void x();

protected:
  std::vector<SyntaxTreeNode*> children;

};

extern SyntaxTreeNode *treeRoot;

#endif //SYNTAXTREENODE_H_
