#include <iostream>
#include <fstream>
#include <syntax_tree/scope.h>

#include "parser.c"
#include <syntax_tree/syntax_tree_node.h>

using namespace std;

bool isFileAccessible(string fileName)
{
    ifstream infile(fileName);
    return infile.good();
}

int main(int argc, char **argv)
{
	string fileName = "";
	if(argc == 2)
	{
		cout << argc << " " << argv[1];
		return 0;
		fileName = string(argv[1]);
	}
	else
	{
		cout << "Enter a Colang source file path: " << endl;
		cin >> fileName;
	}
	while(!isFileAccessible(fileName))
	{
		cout << "Selected Colang file is not accessible." << endl;
		cout << "Enter a Colang source file path: " << endl;
		cin >> fileName;
	}
	
	yyin = fopen(fileName.c_str(), "r");
	yyparse();
	Scope *mainScope = new Scope();
	treeRoot->Run(mainScope);
	delete mainScope;
	delete treeRoot;
	cout << endl;
	system("pause");
	return 0;
	////FunctionCallBlock *main = new FunctionCallBlock(new string("Main"), NULL);
	////main->Run(mainScope);
	////FunctionBlock *main = env->getFunc("Main");
    ////main->Run(env);
}
