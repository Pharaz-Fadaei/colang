# Colang Interpreter

As the name suggests, this is an interpreter for Colang language.

## The Project

This project was actually an optional university project I did for the Compiler Design course.

## Colang Language
Colang is a simple language designed by me. Colang means pickaxe in Persian and since it ends with "lang" and sounds like name of some famous languages like GoLang I decided to use it as the name for the language.
## The Interpreter
The interpreter is composed of three major components: 
* Scanner or lexer
* Parser 
* Abstract Syntax Tree (AST)
### Scanner
When the input text is read, the first step to interpret it, is lexial analysis. Scanners, lexers or lexical analysers use a DFA to tokenize the input. Then these tokens are passed to the parser. You can read more about lexical analysis on [Wikipedia](https://en.wikipedia.org/wiki/Lexical_analysis). This project uses a tool named [Flex](https://en.wikipedia.org/wiki/Flex_(lexical_analyser_generator)) to generate a scanner. Flex takes a flex scanner as the input and generates respective C code. Flex scanner of this project is located at [raw/lex.l](raw/lex.l).
### Parser
To parse a text written in a specific language, a grammar is needed. A parser uses a grammar and tokens from the scanner and parses the input text. A tool named [Bison](https://en.wikipedia.org/wiki/GNU_Bison) is used in this project to generate a parser. Bison takes a specification of a context-free language and generates a parser. Specification of Colang is located at [raw/grammar.y](raw/grammar.y). The parser is also responsible for creating the syntax tree after parsing each rule.
### Abstract Syntax Tree (AST)
After successfully parsing a text, AST will decide what to do with each rule that was parsed by the parser. Each node of this tree corresponds to a rule in the grammar. Since we have different rules, nodes of the tree won't be the same. Thanks to the polymorphism feature in C++, we can have an abstract SyntaxTreeNode and for each rule of the grammar, create a class that extends SyntaxTreeNode and decides what to when that rule is specified. SyntaxTreeNode and different inherited classes of it is located at [include/syntax_tree/](include/syntax_tree/).

## Language Features

Colang has some common features of some popular programming languages. It supports variables, loops, conditionals, functions, simple mathematical arithmetic, the concept of scopes and so on. You can learn more about these features by exploring test files located at [Test/](Test/).

# Build
In order to build this project and use flex and bison, you are going to need some tools from gnu. However, if you don't want to generate the scanner and the parser, you can use your preferred IDE. If you are on Windows, I suggest using [Chocolatey package manager](https://chocolatey.org/). After downloading and installing it, you can use following command in terminal to install all requirements (make sure the terminal is running as administrator):
```
choco install mingw make winflexbison3
```
Then assuming the terminal is at the interpreter folder, you can use following commands to build the project and generate the parser and the scanner.
## Generating the Scanner
In order to generate the scanner you can run the following command:
```
make flex
```
Flex will be used to generate the scanner from _**raw/lex.l**_ and the scanner will be created at *__src/scanner.c__*.
## Generating the parser
Following command can be used to generate the parser:
```
make bison
```
Bison will use the grammar specified at _**raw/grammar.y**_ to generate the parser. It will generate a header file and a source file. The header file will be moved to __*include*__ folder as __*parser.h*__ and the source will be created at __*src/parser.c*__.
## Building the project
To build the project you can simply use **make** command inside the terminal. If you're on windows and there are no errors, the executable file will be at __*bin/colang.exe*__.

## Running tests
After you built the project, you can open the executable file from terminal with an **absolute path** to a .col test file as a parameter, or you can run the executable without a path parameter and then the program will ask you for a path.