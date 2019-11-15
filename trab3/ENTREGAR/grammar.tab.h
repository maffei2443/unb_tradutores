/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_GRAMMAR_TAB_H_INCLUDED
# define YY_YY_GRAMMAR_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "grammar.y" /* yacc.c:1909  */

  #include "Function.h"
  // #include "ShowTree.h"

#line 49 "grammar.tab.h" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ERRU = 258,
    CHAR_TYPE = 259,
    INT_TYPE = 260,
    FLOAT_TYPE = 261,
    MAT_TYPE = 262,
    VOID = 263,
    V_INT = 264,
    V_FLOAT = 265,
    ID = 266,
    AHEAD = 267,
    LP = 268,
    RP = 269,
    LS = 270,
    RS = 271,
    LC = 272,
    RC = 273,
    EQ = 274,
    LT = 275,
    GT = 276,
    LE = 277,
    GE = 278,
    NEQ = 279,
    ADD = 280,
    SUB = 281,
    MUL = 282,
    DIV = 283,
    MAT_MUL = 284,
    MAT_POW = 285,
    AND = 286,
    OR = 287,
    NOT = 288,
    ADDR = 289,
    IF = 290,
    ELSE = 291,
    WHILE = 292,
    RETURN = 293,
    COPY = 294,
    PRINT = 295,
    READ = 296,
    V_ASCII = 297,
    SEMI_COLON = 298,
    DOT = 299,
    COMMA = 300,
    ATTR = 301
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 70 "grammar.y" /* yacc.c:1909  */

  int ival;
  float fval;
  char cval;
  char* sval;
  Dummy* dummy;
  void* vvv;
  Program* _program;
  GlobalStmtList* _globalStmtList;
  GlobalStmt* _globalStmt;
  DefFun* _defFun;
  DeclFun* _declFun;
  DeclVar* _declVar;
  IdArr* _idArr;
  AttrVar* _attrVar;
  SimpleAttr* _simpleAttr;
  IndexAttr* _indexAttr;
  MatAttr* _matAttr;
  NumListList* _numListList;
  NumList* _numList;
  Stmt* _stmt;
  ParamListVoid* _paramListVoid;
  ParamList* _paramList;
  Param* _param;
  Loop* _loop;
  FlowControl* _flowControl;
  Block* _block;
  StmtList* _stmtList;
  Expr* _expr;
  Relop* _relop;
  AddExpr* _addExpr;
  Addop* _addop;
  Term* _term;
  Mulop* _mulop;
  Bin* _bin;
  BinLogi* _binLogi;
  Unary* _unary;
  UnaryOp* _unaryOp;
  Factor* _factor;
  Aux* _aux;
  NumId* _numId;
  Call* _call;
  ArgList* _argList;
  Arg* _arg;
  MatArg* _matArg;
  Ascii* _ascii;
  BaseType* _baseType;
  Num* _num;
  Id* _id;

#line 159 "grammar.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_GRAMMAR_TAB_H_INCLUDED  */
