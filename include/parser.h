/* A Bison parser, made by GNU Bison 3.0.5.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 6 "./raw/grammar.y" /* yacc.c:1910  */

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

#line 66 "parser.h" /* yacc.c:1910  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    STRING_LITERAL = 258,
    IF_KEYWORD = 259,
    ELSE_KEYWORD = 260,
    FUNCTION_KEYWORD = 261,
    VOID_KEYWORD = 262,
    RETURN_KEYWORD = 263,
    AND_KEYWORD = 264,
    OR_KEYWORD = 265,
    WHILE_KEYWORD = 266,
    FOR_KEYWORD = 267,
    FOREACH_KEYWORD = 268,
    IN_KEYWORD = 269,
    BREAK_KEYWORD = 270,
    CONTINUE_KEYWORD = 271,
    VAR_KEYWORD = 272,
    ARRAY_KEYWORD = 273,
    RIGHT_ARROW = 274,
    ASSIGNMENT = 275,
    PLUS = 276,
    MINUS = 277,
    ASTERISK = 278,
    DOUBLEASTERISK = 279,
    SLASH = 280,
    COMMA = 281,
    COLON = 282,
    SEMICOLON = 283,
    DOLLAR = 284,
    LEQ = 285,
    MEQ = 286,
    LESS = 287,
    MORE = 288,
    EQUAL = 289,
    NOTEQUAL = 290,
    PARA = 291,
    PARB = 292,
    BRAA = 293,
    BRAB = 294,
    CURA = 295,
    CURB = 296,
    FLOAT = 297,
    INTEGER = 298,
    ID = 299,
    EOL = 300,
    EOF_ = 301,
    EXCLAMATION = 302,
    PERCENT = 303,
    COMMENT = 304,
    NEGATION = 305
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 28 "./raw/grammar.y" /* yacc.c:1910  */

  std::string *str;
  SyntaxTreeNode *tree;

#line 134 "parser.h" /* yacc.c:1910  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
