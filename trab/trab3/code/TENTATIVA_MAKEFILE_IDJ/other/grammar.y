%code requires {
  #include "Function.h"
}


%{
#include <stdio.h>
#include <stdlib.h>
// P : parentese ~~ ()
// S : simply bracket ~~ []
// C : curly bracket ~~ {}
%}

// %define "parse.error"
// %require "3.0.4"
%define parse.error verbose
%define parse.lac none

%token ERRU
%token CHAR_TYPE INT_TYPE FLOAT_TYPE MAT_TYPE VOID
%token V_INT V_FLOAT 
%token ID AHEAD
%token LP RP
%token LS RS
%token LC RC
%token EQ LT GT LE GE NEQ
%token ADD SUB MUL DIV
%token MAT_MUL MAT_POW
%token AND OR
%token NOT ADDR
%token IF ELSE WHILE RETURN 
%token COPY PRINT READ
%token V_ASCII SEMI_COLON DOT COMMA ATTR

%right MAT_POW
%union {
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
}
%type<_id> ID
%type<ival> V_INT
%type<fval> V_FLOAT
%type<cval> V_ASCII
%type<dummy> LP RP LS RS LC RC CHAR_TYPE INT_TYPE FLOAT_TYPE MAT_TYPE VOID
%type<dummy> AHEAD EQ LT GT LE GE NEQ ADD SUB MUL DIV MAT_MUL MAT_POW AND
%type<dummy> OR NOT ADDR IF ELSE WHILE RETURN COPY PRINT READ SEMI_COLON
%type<dummy> DOT COMMA ATTR

%type<_program>program
%type<_globalStmtList>global-stmt-list
%type<_globalStmt>global-stmt
%type<_defFun>def-fun
%type<_declFun>decl-fun
%type<_declVar>decl-var
%type<_idArr>id-arr
%type<_attrVar>attr-var
%type<_simpleAttr>simple-attr
%type<_indexAttr>index-attr
%type<_matAttr>mat-attr
%type<_numListList>num-list-list
%type<_numList>num-list
%type<_stmt>stmt
%type<_paramListVoid>param-list-void
%type<_paramList>param-list
%type<_param>param
%type<_loop>loop
%type<_flowControl>flow-control
%type<_block>block
%type<_stmtList>stmt-list
%type<_expr>expr
%type<_relop>relop
%type<_addExpr>add-expr
%type<_addop>addop
%type<_term>term
%type<_mulop>mulop
%type<_bin>bin
%type<_binLogi>bin-logi
%type<_unary>unary
%type<_unaryOp>unary-op
%type<_factor>factor
%type<_aux>aux
%type<_numId>num-id
%type<_call>call
%type<_argList>arg-list
%type<_arg>arg
%type<_matArg>mat-arg
%type<_ascii>ascii
%type<_baseType>base-type
%type<_num>num
%%

program : global-stmt-list {$$ = make_Program_op0($1);}
global-stmt-list : global-stmt-list global-stmt {$$ = make_GlobalStmtList_op0($1, $2);}
global-stmt-list : global-stmt {$$ = make_GlobalStmtList_op1($1); }
global-stmt : decl-fun {$$ = make_GlobalStmt_op0($1); }
global-stmt : def-fun error {$$ = make_GlobalStmt_op1($1, NULL); }
global-stmt : def-fun {$$ = make_GlobalStmt_op2($1); }
global-stmt : decl-var SEMI_COLON {$$ = make_GlobalStmt_op3($1); }
global-stmt : decl-var error {$$ = make_GlobalStmt_op4($1, NULL); }
global-stmt : attr-var SEMI_COLON {$$ = make_GlobalStmt_op5($1); }
global-stmt : block {$$ = make_GlobalStmt_op6($1); }
def-fun : base-type ID LP param-list-void RP block {$$ = make_DefFun_op0($1, $2, $4, $6); }
decl-fun : AHEAD base-type ID LP param-list-void RP  SEMI_COLON {$$ = make_DeclFun_op0($2, $3, $5); }
decl-var : MAT_TYPE base-type ID LS num RS LS num RS {$$ = make_DeclVar_op0($2, $3, $5, $8 ); }
decl-var : base-type id-arr {$$ = make_DeclVar_op1($1, $2); }
id-arr : ID LS num-id RS {$$ = make_IdArr_op0($1, $3); }
id-arr : ID {$$ = make_IdArr_op1($1); }
attr-var : mat-attr {$$ = make_AttrVar_op0($1); }
attr-var : index-attr {$$ = make_AttrVar_op1($1); }
attr-var : simple-attr {$$ = make_AttrVar_op2($1); }
simple-attr : ID ATTR expr SEMI_COLON {$$ = make_SimpleAttr_op0($1, $3); }
index-attr : ID LS num-id RS ATTR expr SEMI_COLON {$$ = make_IndexAttr_op0($1, $3, $6); }
mat-attr : ID ATTR LS num-list-list RS {$$ = make_MatAttr_op0($1, $4); }
mat-attr : ID LS num-id RS ATTR LC num-list RC {$$ = make_MatAttr_op1($1, $3, $7); }
mat-attr : ID LS num-id RS LS num-id RS ATTR expr {$$ = make_MatAttr_op2($1, $3, $6, $9); }
num-list-list :  num-list-list LC num-list RC {$$ = make_NumListList_op0($1, $3); }
num-list-list : num-list {$$ = make_NumListList_op1($1); }
num-list : num-list num {$$ = make_NumList_op0($1, $2); }
num-list : num {$$ = make_NumList_op1($1); }
num-list : ID {$$ = make_NumList_op2($1); }
stmt : RETURN expr SEMI_COLON {$$ = make_Stmt_op0($2); }
stmt : COPY LP ID ID  RP SEMI_COLON {$$ = make_Stmt_op1($3, $4); }
stmt : READ LP ID LS num-id RS LS num-id RS RP SEMI_COLON {$$ = make_Stmt_op2($3, $5, $8); }
stmt : READ LP ID LS num-id RS RP SEMI_COLON {$$ = make_Stmt_op3($3, $5); }
stmt : READ LP ID RP SEMI_COLON {$$ = make_Stmt_op4($3); }
stmt : PRINT expr SEMI_COLON {$$ = make_Stmt_op5($2); }
stmt : call SEMI_COLON {$$ = make_Stmt_op6($1); }
stmt : decl-var SEMI_COLON {$$ = make_Stmt_op7($1); }
stmt : attr-var SEMI_COLON {$$ = make_Stmt_op8($1); }
stmt : flow-control {$$ = make_Stmt_op9($1); }
stmt : loop {$$ = make_Stmt_op10($1);}
param-list-void : VOID {$$ = make_ParamListVoid_op0(); }
param-list-void : param-list {$$ = make_ParamListVoid_op1($1); }
param-list : param-list param {$$ = make_ParamList_op0($1, $2); }
param-list : param {$$ = make_ParamList_op1($1); }
param : base-type ID {$$ = make_Param_op0($1, $2); }
param : MAT_TYPE base-type ID {$$ = make_Param_op1($2, $3); }
loop : WHILE LP expr RP block {$$ = make_Loop_op0( $3, $5); }
flow-control : IF LP expr RP block ELSE flow-control {$$ = make_FlowControl_op0( $3, $5, $7); }
flow-control : IF LP expr RP block ELSE block {$$ = make_FlowControl_op1($3, $5, $7); }
flow-control : IF LP error RP block ELSE block {$$ = make_FlowControl_op2( NULL, $5, $7); }
flow-control : IF LP expr error block ELSE block {$$ = make_FlowControl_op3($3, NULL, $5, $7); }
block : LC stmt-list RC {$$ = make_Block_op0($2); }
block : LC RC {$$ = make_Block_op1(); }
stmt-list : stmt-list stmt {$$ = make_StmtList_op0($1, $2); }
stmt-list : stmt {$$ = make_StmtList_op1($1); }
expr : add-expr relop add-expr {$$ = make_Expr_op0($1, $2, $3); }
expr : add-expr {$$ = make_Expr_op1($1); }
relop : LE {$$ = make_Relop_op0(); }
relop : GE {$$ = make_Relop_op1(); }
relop : NEQ {$$ = make_Relop_op2(); }
relop : EQ {$$ = make_Relop_op3(); }
relop : GT {$$ = make_Relop_op4(); }
relop : LT {$$ = make_Relop_op5(); }
add-expr : add-expr addop term {$$ = make_AddExpr_op0($1, $2, $3); }
add-expr : term {$$ = make_AddExpr_op1($1); }
addop : ADD {$$ = make_Addop_op0(); }
addop : SUB {$$ = make_Addop_op1(); }
term : term mulop bin {$$ = make_Term_op0($1, $2, $3); }
term : bin {$$ = make_Term_op1($1); }
mulop : MAT_MUL {$$ = make_Mulop_op0(); }
mulop : MUL {$$ = make_Mulop_op1(); }
mulop : DIV {$$ = make_Mulop_op2(); }
mulop : MAT_POW {$$ = make_Mulop_op3(); }
bin : bin bin-logi unary {$$ = make_Bin_op0($1, $2, $3); }
bin : unary {$$ = make_Bin_op1($1); }
bin-logi : AND {$$ = make_BinLogi_op0(); }
bin-logi : OR {$$ = make_BinLogi_op1(); }
unary : unary-op factor {$$ = make_Unary_op0($1, $2); }
unary : factor {$$ = make_Unary_op1($1); }
unary-op : NOT {$$ = make_UnaryOp_op0(); }
unary-op : ADDR {$$ = make_UnaryOp_op1(); }
factor : LP expr RP {$$ = make_Factor_op0($2); }
factor : aux {$$ = make_Factor_op1($1); }
factor : call {$$ = make_Factor_op2($1); }
factor : '\''ascii'\'' {$$ = make_Factor_op3($2); }
aux : ID LS expr RS LS expr RS {$$ = make_Aux_op0($1, $3, $6); }
aux : ID LS expr RS {$$ = make_Aux_op1($1, $3); }
aux : num-id {$$ = make_Aux_op2($1); }
num-id : num {$$ = make_NumId_op0($1); }
num-id : ID {$$ = make_NumId_op1($1); }
call : ID LP arg-list RP {$$ = make_Call_op0($1, $3); }
call : ID LP VOID RP {$$ = make_Call_op1($1); }
arg-list : arg-list COMMA arg {$$ = make_ArgList_op0($1, $3); }
arg-list : arg {$$ = make_ArgList_op1($1); }
arg : mat-arg {$$ = make_Arg_op0($1); }
arg : aux {$$ = make_Arg_op1($1); }
mat-arg : ID V_INT V_INT {$$ = make_MatArg_op0($1, $2, $3); }
ascii :  V_ASCII {$$ = make_Ascii_op0($1); }
base-type : CHAR_TYPE {$$ = make_BaseType_op0(); }
base-type : INT_TYPE {$$ = make_BaseType_op1(); }
base-type : FLOAT_TYPE {$$ = make_BaseType_op2(); }
num : V_FLOAT {$$ = make_Num_op0($1); }
num : V_INT {$$ = make_Num_op1($1); }


%%

// extern void yyerror (char const *s);
void yyerror (char const *s) {
  fprintf (stderr, "%s\n", s);
}
int main() {
  yyparse();
}