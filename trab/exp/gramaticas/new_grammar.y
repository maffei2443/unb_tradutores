%{
#include <stdio.h>
#include <stdlib.h>
extern int yylineno;
extern int currCol;
extern int numlines;
extern int yyleng;
extern int yylex();
void yyerror (char const *s);
%}
%define parse.error verbose
%define parse.lac none
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

%union {
  char* _id;
  int ival;
  float fval;
  char cval;
}
%%

program: globalStmtList

globalStmtList : globalStmtList globalStmt
| globalStmt

globalStmt : defFun
| declFun ';'
| param ';'

declFun : BASE_TYPE ID '(' paramListVoid ')'

param : BASE_TYPE ID 
| BASE_TYPE ID '[' V_INT ']' 
| MAT_TYPE BASE_TYPE ID '['V_INT ']' '[' V_INT ']'

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
flowControl : IF '(' expr ')' block ELSE block 

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

flowControl : IF '(' error ')' block ELSE block 
flowControl : IF '(' expr error block ELSE block 

%%
void yyerror (char const *s) {
  fprintf (stderr, "%s | l. %d, c. %d\n", s, numlines, currCol - yyleng);
  fprintf (stderr, "%s | l. %d, c. %d\n", s, yylloc.first_line, yylloc.first_column);
}

int _main(){

}