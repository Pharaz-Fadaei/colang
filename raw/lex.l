%option noinput nounput noyywrap
%{
#include "parser.h"

void setValue();
%}

LETTER            [a-zA-Z_]
DIGIT             [0-9]
INT               -?{DIGIT}+
FLOAT             -?(({DIGIT}+"."{DIGIT}*)|({DIGIT}*"."{DIGIT}+))
NEWLINE           \n
WS   	            [ \t]+
ID    	          {LETTER}({LETTER}|{DIGIT})*
STRING 	  				\"(\\.|[^"])*\"
COMMENT   				\/\/.*

%%

{STRING} { setValue(); return STRING_LITERAL; }

"if"        { return IF_KEYWORD; }
"else"      { return ELSE_KEYWORD; }


"function"  { return FUNCTION_KEYWORD; }
"void"      { return VOID_KEYWORD; }
"return"    { return RETURN_KEYWORD; }
"and"|"&&"  { return AND_KEYWORD; }
"or"|"||"   { return OR_KEYWORD; }

"while"     { return WHILE_KEYWORD; }
"for"       { return FOR_KEYWORD; }
"foreach"   { return FOREACH_KEYWORD; }
"in"				{ return IN_KEYWORD; }


"break"     { return BREAK_KEYWORD; }
"continue"  { return CONTINUE_KEYWORD; }

"var"		{ return VAR_KEYWORD; }
"array"		{ return ARRAY_KEYWORD; }


"->"        { return RIGHT_ARROW; }
"="         { return ASSIGNMENT; }
"+"         { return PLUS; }
"-"         { return MINUS; }
"*"         { return ASTERISK; }
"**"	      { return DOUBLEASTERISK; }
"/"         { return SLASH; }
","		      { return COMMA; }
":"         { return COLON; }
";"		      { return SEMICOLON; }
"$"		      { return DOLLAR; }
"<="	      { return LEQ; }
">="	      { return MEQ; }
"<"         { return LESS; }
">"         { return MORE; }
"!"			{ return EXCLAMATION; }
"%"			{ return PERCENT; }

"=="        { return EQUAL; }
"!="        { return NOTEQUAL; }


"("      {return PARA;}
")"      {return PARB;}
"["      {return BRAA;}
"]"      {return BRAB;}
"{"		 {return CURA;}
"}"		 {return CURB;}


{COMMENT} { return COMMENT; }
{FLOAT}	  { setValue(); return FLOAT;}
{INT}     { setValue(); return INTEGER;}
{ID}      { setValue(); return ID;}
{NEWLINE} { yylineno++; return EOL;  }
{WS}      { }

<<EOF>> { return EOF_;}

%%


void setValue()
{
	yylval.str = new std::string(yytext);
}
