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
  yyval.no->tname =  x  ;
#define MAKE_NODE(x) INITNODE(STR(x))


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

%union {
  char* _id;
  int ival;
  float fval;
  char cval;
  No* no;
}

%token BASE_TYPE WHILE V_INT V_FLOAT V_ASCII
%token MAT_TYPE IF ID ICAST FCAST ELSE


%token RETURN PRINT IREAD FREAD COPY
%token AND OR
%token ERRU

%type<no> program
%type<no> globalStmtList globalStmt declFun param declOrdeclInitVar paramListVoid 
%type<no> paramList localStmtList localStmt flowControl 
%type<no> loop defFun numListList
%type<no> numList block declList expr call arglist 
%type<no> arg rvalue lvalue num

%type<_id> ID BASE_TYPE
%type<ival> V_INT
%type<cval> V_ASCII
%type<fval> V_FLOAT
%%

program: globalStmtList {
  MAKE_NODE(program);
  add_Node_Child($program, $globalStmtList);
  root = $program;
  printf("Derivacao foi concluida.\n");
}
| V_ASCII {
  printf("ACHAR %c\n", yylval.cval);
}

globalStmtList : {
  MAKE_NODE(globalStmtList);
}
| globalStmtList globalStmt {
  MAKE_NODE(globalStmtList);
  add_Node_Child($$, $1);
  add_Node_Child($$, $globalStmt);
}

globalStmt : defFun {
  MAKE_NODE(globalStmt);
  add_Node_Child($$, $defFun);
}
| declFun ';' {
  MAKE_NODE(globalStmt);
  add_Node_Child($$, $declFun);
}
| declOrdeclInitVar {
  MAKE_NODE(globalStmt);
  add_Node_Child($$, $declOrdeclInitVar);
}

declFun : BASE_TYPE ID '(' paramListVoid ')' {
  MAKE_NODE(declFun);
  No* _BASE_TYPE = Token_New("BASE_TYPE", $BASE_TYPE);
  No* _ID = Token_New(STR(ID), $ID);
  add_Node_Child($$, _BASE_TYPE);
  add_Node_Child($$, _ID);
  add_Node_Child($$, $paramListVoid);
}

param : BASE_TYPE ID {
  printf("BASE_TYPE ID \n");
  MAKE_NODE(param);
  $$->ival = 0;
  No* base_no = Token_New(STR(BASE_TYPE), $BASE_TYPE);
  No* id_no = Token_New(STR(ID),$ID);
  add_Node_Child($$, base_no);
  add_Node_Child($$, id_no);

}
| BASE_TYPE ID '[' V_INT ']' {
  MAKE_NODE(param);
  $$->ival = 1;
  No* id_no = Token_New(STR(ID),$ID);
  No* base_no = Token_New(STR(BASE_TYPE), $BASE_TYPE);
}
| MAT_TYPE BASE_TYPE ID '[' V_INT ']' '[' V_INT ']'{
  MAKE_NODE(param);
  $$->ival = 2;
}

declOrdeclInitVar : param ';' {
  MAKE_NODE(declOrdeclInitVar);
  add_Node_Child($$, $param);
}
| param '=' rvalue ';' {
  MAKE_NODE(declOrdeclInitVar);
  add_Node_Child($$, $param);
  add_Node_Child($$, $rvalue);
}

paramListVoid : paramList {
  MAKE_NODE(paramListVoid);
  add_Node_Child($$, $paramList);
}
| {
  MAKE_NODE(paramListVoid);
}

paramList : paramList ',' param {
  MAKE_NODE(paramList);
  add_Node_Child($$, $1);
  add_Node_Child($$, $param);
}
| param {
  MAKE_NODE(paramList);
  add_Node_Child($$, $param);
}

localStmtList : localStmtList localStmt {
  MAKE_NODE(localStmtList);
  add_Node_Child($$, $1);
  add_Node_Child($$, $localStmt);
}
|  {
  MAKE_NODE(localStmtList);
}

localStmt : call ';' {
  MAKE_NODE(localStmt);
  add_Node_Child($$, $call);
}
| lvalue '=' rvalue ';'  {
  MAKE_NODE(localStmt);
  add_Node_Child($$, $lvalue);
  add_Node_Child($$, $rvalue);
}
| flowControl {
  MAKE_NODE(localStmt);
  add_Node_Child($$, $flowControl);
}
| loop {
  MAKE_NODE(localStmt);
  add_Node_Child($$, $loop);
}
| RETURN expr ';' {
  MAKE_NODE(localStmt);
  add_Node_Child($$, $expr);
}
| IREAD '(' lvalue ')' ';' {
  MAKE_NODE(localStmt);
  No* iread_no = Token_New("IREAD","IREAD");
  add_Node_Child($$, iread_no);
  add_Node_Child($$, $lvalue);
}
| FREAD '(' lvalue ')' ';' {
  MAKE_NODE(localStmt);
  No* fread_no = Token_New("FREAD","FREAD");
  add_Node_Child($$, fread_no);
  add_Node_Child($$, $lvalue);
}
| PRINT '(' lvalue ')' ';' {
  MAKE_NODE(localStmt);
  No* print_no = Token_New("PRINT","PRINT");
  add_Node_Child($$, print_no);
  add_Node_Child($$, $lvalue);
}
| PRINT '(' V_ASCII ')' ';' {
  MAKE_NODE(localStmt);
  $$->ival = $V_ASCII;
  add_Node_Child($$, Token_New("PRINT","PRINT"));
}
| COPY '(' lvalue lvalue ')' ';' {
  MAKE_NODE(localStmt);
  No* copy_no = Token_New("COPY","COPY");
  add_Node_Child( $$, copy_no );
  add_Node_Child( $$, $3 );
  add_Node_Child( $$, $4 );
}
| ';' {
  MAKE_NODE(localStmt);
  $$->ival = ';';
}

flowControl : IF '(' expr ')' block ELSE flowControl {
  MAKE_NODE(flowControl);
  add_Node_Child($$, Token_New("IF","if"));
  add_Node_Child($$, $expr);
  add_Node_Child($$, $block);
  add_Node_Child($$, Token_New("ELSE","else"));
  add_Node_Child($$, $7);
}
| IF '(' expr ')' block ELSE block {
  MAKE_NODE(flowControl);
  add_Node_Child($$, Token_New("IF","if"));
  add_Node_Child($$, $expr);
  add_Node_Child($$, $5);
  add_Node_Child($$, Token_New("ELSE","else"));
  add_Node_Child($$, $7);
}
| IF '(' expr ')' block {
  MAKE_NODE(flowControl);
  add_Node_Child($$, Token_New("IF","if"));
  add_Node_Child($$, $expr);
  add_Node_Child($$, $block);
}

loop : WHILE '(' expr ')' block {
  MAKE_NODE(loop);
  add_Node_Child($$, Token_New("WHILE","while"));
  add_Node_Child($$, $expr);
  add_Node_Child($$, $block);
}


defFun : BASE_TYPE ID '(' paramListVoid ')' '{' declList localStmtList '}' {
  MAKE_NODE(defFun);
  No* _BASE_TYPE = Token_New(STR(BASE_TYPE), $BASE_TYPE);
  No* _ID = Token_New(STR(ID), $ID);
  add_Node_Child($$, _BASE_TYPE);
  add_Node_Child($$, _ID);
  add_Node_Child($$, $paramListVoid);
  add_Node_Child($$, $declList);
  add_Node_Child($$, $localStmtList);
}

numListList :  numListList '{' numList '}' {
  MAKE_NODE(numListList);
  add_Node_Child($$, $1);
  add_Node_Child($$, $numList);
}
| {
  MAKE_NODE(numListList);
}

numList : numList ',' num {
  MAKE_NODE(numList);
  add_Node_Child($$, $1);
  add_Node_Child($$, $num);
}
| num {
  MAKE_NODE(numList);
  add_Node_Child($$, $num);
}


block : '{' localStmtList '}' {
  MAKE_NODE(block);
  add_Node_Child($$, $localStmtList);
}

declList : declList declOrdeclInitVar {
  MAKE_NODE(declList);
  add_Node_Child($$, $1);
  add_Node_Child($$, $declOrdeclInitVar);
}
| {
  MAKE_NODE(declList);
}

expr : expr '+' expr {
  MAKE_NODE(expr); 
  $$->ival = '+'; 
  add_Node_Child($$, $1); 
  add_Node_Child($$, $3);  
}
| expr '-' expr {
  MAKE_NODE(expr); 
  $$->ival = '-'; 
  add_Node_Child($$, $1); 
  add_Node_Child($$, $3);  
}
| expr '*' expr {
  MAKE_NODE(expr); 
  $$->ival = '*'; 
  add_Node_Child($$, $1); 
  add_Node_Child($$, $3);  

}
| expr '/' expr {
  MAKE_NODE(expr); 
  $$->ival = '/'; 
  add_Node_Child($$, $1); 
  add_Node_Child($$, $3);  
}
| expr '%' expr {
  MAKE_NODE(expr); 
  $$->ival = '%'; 
  add_Node_Child($$, $1); 
  add_Node_Child($$, $3);    
}
| expr '@' expr {
  MAKE_NODE(expr); 
  $$->ival = '@'; 
  add_Node_Child($$, $1); 
  add_Node_Child($$, $3);    
}
| expr MAT_POW expr {
  MAKE_NODE(expr); 
  $$->ival = MAT_POW; 
  add_Node_Child($$, $1); 
  add_Node_Child($$, $3);    
}
| expr EQ expr {
  MAKE_NODE(expr); 
  $$->ival = EQ; 
  add_Node_Child($$, $1); 
  add_Node_Child($$, $3);  
}
| expr NEQ expr {
  MAKE_NODE(expr); 
  $$->ival = NEQ; 
  add_Node_Child($$, $1); 
  add_Node_Child($$, $3);  
}
| expr GE expr {
  MAKE_NODE(expr); 
  $$->ival = GE; 
  add_Node_Child($$, $1); 
  add_Node_Child($$, $3);  
}
| expr LE expr {
  MAKE_NODE(expr); 
  $$->ival = LE; 
  add_Node_Child($$, $1); 
  add_Node_Child($$, $3);  
}
| expr '>' expr {
  MAKE_NODE(expr); 
  $$->ival = '>'; 
  add_Node_Child($$, $1); 
  add_Node_Child($$, $3);    
}
| expr '<' expr {
  MAKE_NODE(expr); 
  $$->ival = '<'; 
  add_Node_Child($$, $1); 
  add_Node_Child($$, $3);    
}
| expr AND expr {
  MAKE_NODE(expr); 
  $$->ival = AND; 
  add_Node_Child($$, $1); 
  add_Node_Child($$, $3);  
}
| expr OR expr {
  MAKE_NODE(expr); 
  $$->ival = OR; 
  add_Node_Child($$, $1); 
  add_Node_Child($$, $3);  
}
| '!' expr {
  MAKE_NODE(expr);
  $$->ival = '!';
  add_Node_Child($$, $2);
}
| '&' expr {
  MAKE_NODE(expr);
  $$->ival = '&';
  add_Node_Child($$, $2);
}
| '(' expr ')' {
  MAKE_NODE(expr);
  add_Node_Child($$, $2);
}
| ICAST '(' expr ')' {
  MAKE_NODE(expr);
  add_Node_Child($$, Token_New("ICAST", "ICAST"));
  add_Node_Child($$, $3);
}
| FCAST '(' expr ')' {
  MAKE_NODE(expr);
  add_Node_Child($$, Token_New("FCAST", "FCAST"));
  add_Node_Child($$, $3);
}
| lvalue {
  MAKE_NODE(expr);
  add_Node_Child($$, $lvalue);
}
| call {
  MAKE_NODE(expr);
  add_Node_Child($$, $call);
}
| num {
  MAKE_NODE(expr);
  add_Node_Child($$, $num);
}

call : ID '(' arglist ')' {
  MAKE_NODE(call);
  add_Node_Child($$, Token_New("ID", $ID));
  add_Node_Child($$, $arglist);
}
| ID '('  ')' {
  MAKE_NODE(call);
  add_Node_Child($$, Token_New("ID", $ID));
}

arglist : arglist ',' arg {
  MAKE_NODE(arglist);
  add_Node_Child($$, $1);
  add_Node_Child($$, $3);
}
| arg {
  MAKE_NODE(arglist);
  add_Node_Child($$, $1);
}

arg : lvalue {
  MAKE_NODE(arg);
  add_Node_Child($$, $lvalue);
}
| ID '(' expr ')' '(' expr ')' {
  MAKE_NODE(arg);
  add_Node_Child($$, Token_New("ID", $ID));
  add_Node_Child($$, $3);
  add_Node_Child($$, $6);
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
  root = NULL;
  nodeCounter = 0;
  yyparse();
  print_reshi();
  if(root) {
    show_Sub_Tree(root, 1, SVAL);
    show_Lis(root,SVAL);
  }

}