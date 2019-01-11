%token STRING_LITERAL IF_KEYWORD ELSE_KEYWORD FUNCTION_KEYWORD VOID_KEYWORD RETURN_KEYWORD AND_KEYWORD OR_KEYWORD WHILE_KEYWORD FOR_KEYWORD FOREACH_KEYWORD IN_KEYWORD BREAK_KEYWORD CONTINUE_KEYWORD VAR_KEYWORD ARRAY_KEYWORD RIGHT_ARROW ASSIGNMENT PLUS MINUS ASTERISK DOUBLEASTERISK SLASH COMMA COLON SEMICOLON DOLLAR LEQ MEQ LESS MORE EQUAL NOTEQUAL PARA PARB BRAA BRAB CURA CURB FLOAT INTEGER ID EOL EOF_ EXCLAMATION PERCENT COMMENT
%{
  #include "scanner.c"
%}
%code requires
{
  #include <string>

  #include "syntax_tree/syntax_tree_node.h"
  #include "syntax_tree/variable.h"
  #include "syntax_tree/function_block.h"
  #include "syntax_tree/if_block.h"
  #include "syntax_tree/line_block.h"
  #include "syntax_tree/assignment_block.h"
  #include "syntax_tree/literal_block.h"
  #include "syntax_tree/function_call_block.h"
  #include "syntax_tree/program_blocks.h"
  #include "syntax_tree/variable_call_block.h"
  #include "syntax_tree/endline_block.h"
  #include "syntax_tree/for_block.h"
  #include "syntax_tree/variable_definition_block.h"
  #include "syntax_tree/variable_definition_list_block.h"
  #include "syntax_tree/foreach_block.h"

  void yyerror(char *msg);
}

%union{
  std::string *str;
  SyntaxTreeNode *tree;
}

%type <str> ID STRING_LITERAL INTEGER FLOAT
%type <tree> blocks block if_block code_block expression function_definition function_parameters parameters assignment function_call arguments single_expression line loop_block for_block while_block foreach_block nullable_expression end_line variable_definition variable_definition_list single_variable_definition

%precedence PARB
%precedence BRAA


%precedence VAR_KEYWORD
%precedence COMMA

%right ASSIGNMENT
%right ELSE_KEYWORD
%right EOL

%left OR_KEYWORD
%left AND_KEYWORD
%left EQUAL
%left NOTEQUAL
%left MORE
%left LESS
%left MEQ
%left LEQ

%left MINUS
%left PLUS
%left PERCENT
%left SLASH
%left ASTERISK
%left EXCLAMATION
%right DOUBLEASTERISK
%left NEGATION


%start program

%%

program: blocks { treeRoot = $1; YYACCEPT; }
blocks: blocks block { $$ = $1; $$->addChild($2); }
  | block { $$ = new ProgramBlocks(); $$->addChild($1); }

block: line { $$ = $1; }
  | EOL { $$ = NULL; }
  | COMMENT { $$ = NULL; }
;

line:
  end_line end			{ $$ = $1; }
  | if_block            { $$ = $1; }
  | single_expression	{ $$ = $1; }
  | loop_block			{ $$ = $1; }
  | function_definition { $$ = $1; }
  | CURA blocks CURB  { $$ = new CodeBlock($2); }

function_definition: FUNCTION_KEYWORD ID PARA function_parameters PARB code_block { $$ = new FunctionBlock($2, $4, $6, 0); }
  | FUNCTION_KEYWORD ID PARA function_parameters PARB ASSIGNMENT single_expression { $$ = new FunctionBlock($2, $4, $7, 1); };

function_parameters: parameters { $$ = $1;   }
  | %empty                      { $$ = NULL; };

parameters: parameters COMMA ID  { $$ = $1; $$->addChild(new VariableDefinitionBlock($3)); }
  | ID                           { $$ = new ParametersBlock(); $$->addChild(new VariableDefinitionBlock($1)); };

code_block: line             { $$ = new CodeBlock($1); }
  | EOL code_block   { $$ = $2; }
  | code_block EOL   { $$ = $1; }



end_line:
  RETURN_KEYWORD expression { $$ = new EndLineBlock($2); }
  | RETURN_KEYWORD { $$ = new EndLineBlock(ReturnEnd); }
  | BREAK_KEYWORD { $$ = new EndLineBlock(BreakEnd); }
  | CONTINUE_KEYWORD { $$ = new EndLineBlock(ContinueEnd); };


if_block: IF_KEYWORD PARA expression PARB code_block  { $$ = new IfBlock($3, $5); }
  | IF_KEYWORD PARA expression PARB code_block ELSE_KEYWORD  code_block { $$ = new IfBlock($3, $5, $7); }

loop_block:
  for_block { $$ = $1; }
  | foreach_block { $$ = $1; }
  | while_block { $$ = $1; }

for_block: FOR_KEYWORD PARA nullable_expression SEMICOLON nullable_expression SEMICOLON nullable_expression PARB code_block  { $$ = new ForBlock($3, $5, $7, $9, NULL);  }
  | FOR_KEYWORD PARA nullable_expression SEMICOLON nullable_expression SEMICOLON nullable_expression PARB code_block ELSE_KEYWORD code_block { $$ = new ForBlock($3, $5, $7, $9, $11);  }
  | FOR_KEYWORD PARA VAR_KEYWORD ID IN_KEYWORD expression COLON expression PARB code_block { $$ = new ForBlock($4, $6, $8, $10, NULL); }
  | FOR_KEYWORD PARA VAR_KEYWORD ID IN_KEYWORD expression COLON expression PARB code_block ELSE_KEYWORD code_block { $$ = new ForBlock($4, $6, $8, $10, $12); }

foreach_block: FOREACH_KEYWORD PARA VAR_KEYWORD ID IN_KEYWORD expression PARB code_block { $$ = new ForeachBlock($4, $6, $8, NULL); }
  | FOREACH_KEYWORD PARA VAR_KEYWORD ID IN_KEYWORD expression PARB code_block ELSE_KEYWORD code_block { $$ = new ForeachBlock($4, $6, $8, $10); }
  | FOREACH_KEYWORD PARA VAR_KEYWORD ID COMMA ID IN_KEYWORD expression PARB code_block { $$ = new ForeachBlock($4, $6, $8, $10, NULL); }
  | FOREACH_KEYWORD PARA VAR_KEYWORD ID COMMA ID IN_KEYWORD expression PARB code_block ELSE_KEYWORD code_block { $$ = new ForeachBlock($4, $6, $8, $10, $12); }

while_block: WHILE_KEYWORD PARA nullable_expression PARB code_block { $$ = new ForBlock((SyntaxTreeNode*)NULL, $3, NULL, $5, NULL); }
  | WHILE_KEYWORD PARA nullable_expression PARB code_block ELSE_KEYWORD code_block { $$ = new ForBlock((SyntaxTreeNode*)NULL, $3, NULL, $5, $7); }

assignment:	ID ASSIGNMENT expression		        { $$ = new AssignmentBlock($1, $3, 0); }
	| ID BRAA expression BRAB ASSIGNMENT expression { $$ = new AssignmentBlock($1, $3,  $6); }
	| ID BRAA BRAB ASSIGNMENT expression 			{ $$ = new AssignmentBlock($1, $5, 2); };

single_expression:
    expression end { $$ = $1; }

nullable_expression:
  expression { $$ = $1; }
  | %empty     { $$ = NULL; }

expression:
  MINUS expression %prec NEGATION { $$ = new ExpressionBlock(Negation); $$->addChild($2); }
  | expression PLUS expression      { $$ = new ExpressionBlock(Addition); $$->addChild($1); $$->addChild($3); }
  | expression MINUS expression     { $$ = new ExpressionBlock(Subtraction); $$->addChild($1); $$->addChild($3); }
  | expression ASTERISK expression   { $$ = new ExpressionBlock(Multiplication); $$->addChild($1); $$->addChild($3); }
  | expression SLASH expression     { $$ = new ExpressionBlock(Division); $$->addChild($1); $$->addChild($3); }
  | expression PERCENT expression	{ $$ = new ExpressionBlock(Modulo); $$->addChild($1); $$->addChild($3); }
  | expression DOUBLEASTERISK expression { $$ = new ExpressionBlock(Exponentiation); $$->addChild($1); $$->addChild($3); }
  | expression EQUAL expression     { $$ = new ExpressionBlock(Equality); $$->addChild($1); $$->addChild($3); }
  | expression NOTEQUAL expression  { $$ = new ExpressionBlock(Inequality); $$->addChild($1); $$->addChild($3); }
  | expression MORE expression      { $$ = new ExpressionBlock(MoreThan); $$->addChild($1); $$->addChild($3); }
  | expression LESS expression      { $$ = new ExpressionBlock(LessThan); $$->addChild($1); $$->addChild($3); }
  | expression MEQ expression       { $$ = new ExpressionBlock(Meq); $$->addChild($1); $$->addChild($3); }
  | expression LEQ expression       { $$ = new ExpressionBlock(Leq); $$->addChild($1); $$->addChild($3); }
  | expression AND_KEYWORD expression { $$ = new ExpressionBlock(And); $$->addChild($1); $$->addChild($3); }
  | expression OR_KEYWORD expression { $$ = new ExpressionBlock(Or); $$->addChild($1); $$->addChild($3); }
  | EXCLAMATION expression			{ $$ = new ExpressionBlock(Not); $$->addChild($2); }
  | INTEGER                         { $$ = new ExpressionBlock(NONE); $$->addChild(new LiteralBlock(Value($1, INTEGRAL_VALUE))); }
  | FLOAT                           { $$ = new ExpressionBlock(NONE); $$->addChild(new LiteralBlock(Value($1, DOUBLE_VALUE))); }
  | STRING_LITERAL                  { $$ = new ExpressionBlock(NONE); $$->addChild(new LiteralBlock($1, STRING_VALUE)); }
  | ID BRAA expression BRAB            { $$ = new VariableCallBlock($1, $3); }
  |	function_call					{ $$ = new ExpressionBlock(NONE); $$->addChild($1); }
  | PARA expression PARB			{ $$ = $2; }
  | ID								{ $$ = new VariableCallBlock($1); }
  | variable_definition 			{ $$ = $1; }
  | assignment			  			{ $$ = $1; }

variable_definition:
  VAR_KEYWORD variable_definition_list { $$ = $2; }

variable_definition_list:
  single_variable_definition { $$ = new VariableDefinitionListBlock(); $$->addChild($1); }
  | variable_definition_list COMMA single_variable_definition { $1->addChild($3); $$ = $1; }

single_variable_definition: ID ASSIGNMENT expression { $$ = new VariableDefinitionBlock($1, $3); }
  | ID                                        { $$ = new VariableDefinitionBlock($1); }

function_call: ID PARA arguments PARB	{ $$ = new FunctionCallBlock($1, $3); }

arguments: arguments COMMA expression { $$ = $1; $1->addChild($3); }
  | expression						  { $$ = new FunctionArguments(); $$->addChild($1); }
  | %empty 							  { $$ = NULL; }


end: EOL
  | COMMENT
  | SEMICOLON
  | EOF_;



%%


void yyerror(char *msg)
{
  printf("%s around line %d \n", msg, yylineno);
  system("pause");
  exit(1);
}
