%code requires {
  #include "Tree.h"
  No* root;
  struct {
    int ival;
    float fval;
    char* sval;
    int allocated;
  } _;
}

%{
#include <stdio.h>
#include <stdlib.h>
extern int yylineno;
extern int currCol;
extern int numlines;
extern int yyleng;
extern int yylex();
void yyerror (char const *s);
extern void print_reshi();
%}
%define parse.error verbose
%define parse.lac none
%define parse.trace

%token-table
%locations

%left EQ NEQ GE LE
%left AND
%left OR
%left '<' '>'
%left '+' '-'
%left '*' '/'
%left '@'
%right MAT_POW
%left '!' '&'

%token AHEAD BASE_TYPE WHILE V_INT V_FLOAT V_ASCII
%token MAT_TYPE IF ID ICAST FCAST ELSE

%token RETURN PRINT IREAD FREAD COPY
%token AND OR
%token ERRU

%type<no> globalStmtList globalStmt declFun param declOrdeclInitVar paramListVoid 
%type<no> paramList locStmtList locStmt flowControl 
%type<no> loop defFun numListList
%type<no> numList block declList expr call arglist 
%type<no> arg rvalue 

%union {
  char* _id;
  int ival;
  float fval;
  char cval;
  No* no;
}
%%

program: globalStmtList {
  printf("Derivacao foi concluida.\n");
}

globalStmtList : globalStmtList globalStmt
|

globalStmt : defFun
| declFun ';'
| declOrdeclInitVar

declFun : BASE_TYPE ID '(' paramListVoid ')'

param : BASE_TYPE ID 
| BASE_TYPE ID '[' ']' 
| MAT_TYPE BASE_TYPE ID 

declOrdeclInitVar : param ';'
| param '=' rvalue ';'

paramListVoid : paramList
| 

paramList : paramList ',' param
| param

locStmtList : locStmtList locStmt 
| 

locStmt : call ';'
| lvalue '=' rvalue ';'
| flowControl
| loop
| RETURN expr ';'
| IREAD '(' lvalue ')' ';'
| FREAD '(' lvalue ')' ';'
| PRINT '(' lvalue ')' ';'
| COPY '(' lvalue lvalue ')' ';'
| ';'
flowControl : IF '(' expr ')' block ELSE flowControl 
| IF '(' expr ')' block ELSE block 
| IF '(' expr ')' block

loop : WHILE '(' expr ')' block


defFun : BASE_TYPE ID '(' paramListVoid ')' '{' declList locStmtList '}'

numListList :  numListList '{' numList '}'
|

numList : numList ',' num
| num


block : '{' locStmtList '}'

declList : declList declOrdeclInitVar
| 

expr : expr '+' expr
| expr '-' expr
| expr '*' expr
| expr '/' expr
| expr '@' expr
| expr MAT_POW expr
| expr EQ expr
| expr NEQ expr
| expr GE expr
| expr LE expr
| expr '>' expr
| expr '<' expr
| expr AND expr
| expr OR expr
| '!' expr
| '&' expr
| '(' expr ')'
| ICAST '(' expr ')'
| FCAST '(' expr ')'
| lvalue
| call
| num

call : ID '(' arglist ')'
| ID '('  ')'

arglist : arglist ',' arg
| arg

arg : lvalue
| ID '(' expr ')' '(' expr ')' 

num: V_INT
| V_FLOAT


lvalue: ID
| ID '[' expr ']'
| ID '[' expr ']' '[' expr ']'

rvalue : expr
| '{' numList '}'
| '[' numListList ']'

%%
void yyerror (char const *s) {
  fprintf (stderr, "%s | l. %d, c. %d\n", s, numlines, currCol - yyleng);
  fprintf (stderr, "%s | l. %d, c. %d\n", s, yylloc.first_line, yylloc.first_column);
}

int main(){
  yyparse();
  print_reshi();
}