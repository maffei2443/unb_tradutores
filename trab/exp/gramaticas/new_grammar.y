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
#define STR(x) #x 

#define INITNODE(x) \
  yyval.no = No_New(nodeCounter++); \
  if(!yyval.no) abort(); \
  yyval.no->sval =  x  ;
#define MAKE_NODE(x) INITNODE(STR(x))

#include <stdio.h>
#include <stdlib.h>
extern int yylineno;
extern int currCol;
extern int numlines;
extern int yyleng;
extern int yylex();
void yyerror (char const *s);
extern void print_reshi();
unsigned nodeCounter;
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
%left '%'
%left '*' '/' 
%left '@'
%right MAT_POW
%left '!' '&'

%token AHEAD BASE_TYPE WHILE V_INT V_FLOAT V_ASCII
%token MAT_TYPE IF ID ICAST FCAST ELSE

%token RETURN PRINT IREAD FREAD COPY
%token AND OR
%token ERRU

%type<no> program
%type<no> globalStmtList globalStmt declFun param declOrdeclInitVar paramListVoid 
%type<no> paramList localStmtList localStmt flowControl 
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
  MAKE_NODE(program);
  root = $program;
  printf("Derivacao foi concluida.\n");
}

globalStmtList : {
  MAKE_NODE(globalStmtList);
}
| localStmtList globalStmt {
  MAKE_NODE(globalStmtList);
}

globalStmt : defFun {
  MAKE_NODE(globalStmt);
  $$ = No_New(nodeCounter++);
  // add_Node_Child($$, defFun);
}
| declFun ';' {
  MAKE_NODE(globalStmt);
}
| declOrdeclInitVar {
  MAKE_NODE(globalStmt);
}

declFun : BASE_TYPE ID '(' paramListVoid ')' {
  MAKE_NODE(declFun);
}

param : BASE_TYPE ID {
  MAKE_NODE(param);
}
| BASE_TYPE ID '[' ']' {
  MAKE_NODE(param);
}
| MAT_TYPE BASE_TYPE ID {
  MAKE_NODE(param);
}

declOrdeclInitVar : param ';' {
  MAKE_NODE(declOrdeclInitVar);
}
| param '=' rvalue ';' {
  MAKE_NODE(param);
}

paramListVoid : paramList {
  MAKE_NODE(paramListVoid);
}
| {
  MAKE_NODE(paramListVoid);
}

paramList : paramList ',' param {
  MAKE_NODE(paramList);
}
| param {
  MAKE_NODE(paramList);
}

localStmtList : localStmtList localStmt {
  MAKE_NODE(localStmtList);
}
|  {
  MAKE_NODE(localStmtList);
}

localStmt : call ';' {
  MAKE_NODE(localStmt);

}
| lvalue '=' rvalue ';'  {
  MAKE_NODE(localStmt);
}
| flowControl {
  MAKE_NODE(localStmt);
}
| loop {
  MAKE_NODE(localStmt);
}
| RETURN expr ';' {
  MAKE_NODE(localStmt);
}
| IREAD '(' lvalue ')' ';' {
  MAKE_NODE(localStmt);
}
| FREAD '(' lvalue ')' ';' {
  MAKE_NODE(localStmt);
}
| PRINT '(' lvalue ')' ';' {
  MAKE_NODE(localStmt);
}
| COPY '(' lvalue lvalue ')' ';' {
  MAKE_NODE(localStmt);
}
| ';' {
  MAKE_NODE(localStmt);
}
flowControl : IF '(' expr ')' block ELSE flowControl {
  MAKE_NODE(flowControl);
}
| IF '(' expr ')' block ELSE block {
  MAKE_NODE(flowControl);
}
| IF '(' expr ')' block {
  MAKE_NODE(flowControl);
}

loop : WHILE '(' expr ')' block {
  MAKE_NODE(loop);
}


defFun : BASE_TYPE ID '(' paramListVoid ')' '{' declList localStmtList '}' {
  MAKE_NODE(defFun);
}

numListList :  numListList '{' numList '}' {
  MAKE_NODE(numListList);
}
| {
  MAKE_NODE(numListList);
}

numList : numList ',' num {
  MAKE_NODE(numList);
}
| num {
  MAKE_NODE(numList);
}


block : '{' localStmtList '}' {
  MAKE_NODE(block);
}

declList : declList declOrdeclInitVar {
  MAKE_NODE(declList);
}
| {
  MAKE_NODE(declList);
}

expr : expr '+' expr {
  MAKE_NODE(expr);
}
| expr '-' expr {
  MAKE_NODE(expr);
}
| expr '*' expr {
  MAKE_NODE(expr);
}
| expr '/' expr {
  MAKE_NODE(expr);
}
| expr '%' expr {
  MAKE_NODE(expr);
}
| expr '@' expr {
  MAKE_NODE(expr);
}
| expr MAT_POW expr {
  MAKE_NODE(expr);
}
| expr EQ expr {
  MAKE_NODE(expr);
}
| expr NEQ expr {
  MAKE_NODE(expr);
}
| expr GE expr {
  MAKE_NODE(expr);
}
| expr LE expr {
  MAKE_NODE(expr);
}
| expr '>' expr {
  MAKE_NODE(expr);
}
| expr '<' expr {
  MAKE_NODE(expr);
}
| expr AND expr {
  MAKE_NODE(expr);
}
| expr OR expr {
  MAKE_NODE(expr);
}
| '!' expr {
  MAKE_NODE(expr);
}
| '&' expr {
  MAKE_NODE(expr);
}
| '(' expr ')' {
  MAKE_NODE(expr);
}
| ICAST '(' expr ')' {
  MAKE_NODE(expr);
}
| FCAST '(' expr ')' {
  MAKE_NODE(expr);
}
| lvalue {
  MAKE_NODE(expr);
}
| call {
  MAKE_NODE(expr);
}
| num {
  MAKE_NODE(expr);
}

call : ID '(' arglist ')' {
  MAKE_NODE(call);
}
| ID '('  ')' {
  MAKE_NODE(call);
}

arglist : arglist ',' arg {
  MAKE_NODE(arglist);
}
| arg {
  MAKE_NODE(arglist);
}

arg : lvalue {
  MAKE_NODE(arg);
}
| ID '(' expr ')' '(' expr ')' {
  MAKE_NODE(arg);
}

num: V_INT {
  MAKE_NODE(num);
}
| V_FLOAT {
  MAKE_NODE(num);
}


lvalue: ID {
  MAKE_NODE(lvalue);
}
| ID '[' expr ']' {
  MAKE_NODE(lvalue);
}
| ID '[' expr ']' '[' expr ']' {
  MAKE_NODE(lvalue);
}

rvalue : expr {
  MAKE_NODE(rvalue);
}
| '{' numList '}' {
  MAKE_NODE(rvalue);
}
| '[' numListList ']' {
  MAKE_NODE(rvalue);
}

%%
void yyerror (char const *s) {
  fprintf (stderr, "%s | l. %d, c. %d\n", s, numlines, currCol - yyleng);
  fprintf (stderr, "%s | l. %d, c. %d\n", s, yylloc.first_line, yylloc.first_column);
}

int main(){
  nodeCounter = 0;
  yyparse();
  print_reshi();
  show_Sub_Tree(root, 0, SVAL);
  show_Lis(root, SVAL);
}