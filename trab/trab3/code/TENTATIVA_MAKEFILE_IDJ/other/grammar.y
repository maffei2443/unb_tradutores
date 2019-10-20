%code requires {
typedef struct {} Dummy;
#define str struct
typedef char Error;
typedef str {
  union {
    struct {} op0;  //i: int
    struct {} op1;  //i: f: float
    struct {} op2;  //i: c: char
  }u;
  int tag;
}MatType;

typedef str {
  union {
    str {str GlobalStmtList* globalStmtList;} op0;
  }u;
  int tag;
} Program;
typedef str {
  union {
    str {str GlobalStmtList* globalStmtList; str GlobalStmt* globalStmt;} op0;
    str {str GlobalStmt* globalStmt;} op1;
  }u;
  int tag;
} GlobalStmtList;
typedef str {
  union {
    str {str DeclFun* declFun;} op0;
    str {str DefFun* defFun; str Error* error;} op1;
    str {str DefFun* defFun;} op2;
    str {str DeclVar* declVar; } op3;
    str {str DeclVar* declVar; str Error* error;} op4;
    str {str AttrVar* attrVar;} op5;
    str {str Block* block;} op6;
  }u;
  int tag;
} GlobalStmt;
typedef str {
  union {
    str {str BaseType* baseType; str Id* id;  str ParamListVoid* paramListVoid; str Block* block;} op0;
  }u;
  int tag;
} DefFun;
typedef str {
  union {
    str {str BaseType* baseType; str Id* id;  str ParamListVoid* paramListVoid; ;} op0;
  }u;
  int tag;
} DeclFun;
typedef str {
  union {
    str {str MatType* mat_type; str BaseType* baseType; str Id* id;  str Num* num0;   str Num* num1; } op0;
    str {str BaseType* baseType; str IdArr* idArr;} op1;
  }u;
  int tag;
} DeclVar;
typedef str {
  union {
    str {str Id* id;  str NumId* numId; } op0;
    str {str Id* id;} op1;
  }u;
  int tag;
} IdArr;
typedef str {
  union {
    str {str MatAttr* matAttr;} op0;
    str {str IndexAttr* indexAttr;} op1;
    str {str SimpleAttr* simpleAttr;} op2;
  }u;
  int tag;
} AttrVar;
typedef str {
  union {
    str {str Id* id;  str Expr* expr; ;} op0;
  }u;
  int tag;
} SimpleAttr;
typedef str {
  union {
    str {str Id* id;  str NumId* numId;   str Expr* expr; ;} op0;
  }u;
  int tag;
} IndexAttr;
typedef str {
  union {
    str {str Id* id;   str NumListList* numListList; } op0;
    str {str Id* id;  str NumId* numId;   ; str NumList* numList; } op1;
    str {str Id* id;  str NumId* numId0;   str NumId* numId1;   str Expr* expr;} op2;
  }u;
  int tag;
} MatAttr;
typedef str {
  union {
    str {str NumListList* numListList; ; str NumList* numList; } op0;
    str {str NumList* numList;} op1;
  }u;
  int tag;
} NumListList;
typedef str {
  union {
    str {str NumList* numList; str Num* num;} op0;
    str {str Num* num;} op1;
    str {str Id* id;} op2;
  }u;
  int tag;
} NumList;
typedef str {
  union {
    str {str Expr* expr; ;} op0;
    str { str Id* id0; str Id* id1; ;} op1;
    str {  str Id* id;  str NumId* numId0;   str NumId* numId1;  ;} op2;
    str {  str Id* id;  str NumId* numId;  ;} op3;
    str {  str Id* id; ;} op4;
    str {str Expr* expr; ;} op5;
    str {str Call* call; ;} op6;
    str {str DeclVar* declVar; ;} op7;
    str {str AttrVar* attrVar; ;} op8;
    str {str FlowControl* flowControl;} op9;
    str {str Loop* loop;} op10;
  }u;
  int tag;
} Stmt;
typedef str {
  union {
    str {} op0;
    str {str ParamList* paramList;} op1;
  }u;
  int tag;
} ParamListVoid;
typedef str {
  union {
    str {str ParamList* paramList; str Param* param;} op0;
    str {str Param* param;} op1;
  }u;
  int tag;
} ParamList;
typedef str {
  union {
    str {str BaseType* baseType; str Id* id;} op0;
    str {str MatType* mat_type; str BaseType* baseType; str Id* id;} op1;
  }u;
  int tag;
} Param;
typedef str {
  union {
    str {str Expr* expr; str Block* block;} op0;
  }u;
  int tag;
} Loop;
typedef str {
  union {
    str {str Expr* expr; str Block* block;  str FlowControl* flowControl;} op0;
    str {str Expr* expr; str Block* block0;  str Block* block1;} op1;
    str {str Error* error; str Block* block0;  str Block* block1;} op2;
    str {str Expr* expr; str Error* error; str Block* block0;  str Block* block1;} op3;
  }u;
  int tag;
} FlowControl;
typedef str {
  union {
    str { str StmtList* stmtList; } op0;
    str {} op1;
  }u;
  int tag;
} Block;
typedef str {
  union {
    str {str StmtList* stmtList; str Stmt* stmt;} op0;
    str {str Stmt* stmt;} op1;
  }u;
  int tag;
} StmtList;
typedef str {
  union {
    str {str AddExpr* addExpr0; str Relop* relop; str AddExpr* addExpr1;} op0;
    str {str AddExpr* addExpr;} op1;
  }u;
  int tag;
} Expr;
typedef str {
  union {
    str {} op0;
    str {} op1;
    str {} op2;
    str {} op3;
    str {} op4;
    str {} op5;
  }u;
  int tag;
} Relop;
typedef str {
  union {
    str {str AddExpr* addExpr; str Addop* addop; str Term* term;} op0;
    str {str Term* term;} op1;
  }u;
  int tag;
} AddExpr;
typedef str {
  union {
    str {} op0;
    str {} op1;
  }u;
  int tag;
} Addop;
typedef str {
  union {
    str {str Term* term; str Mulop* mulop; str Bin* bin;} op0;
    str {str Bin* bin;} op1;
  }u;
  int tag;
} Term;
typedef str {
  union {
    str {} op0;
    str {} op1;
    str {} op2;
  }u;
  int tag;
} Mulop;
typedef str {
  union {
    str {str Bin* bin; str BinLogi* binLogi; str Unary* unary;} op0;
    str {str Unary* unary;} op1;
  }u;
  int tag;
} Bin;
typedef str {
  union {
    str {} op0;
    str {} op1;
  }u;
  int tag;
} BinLogi;
typedef str {
  union {
    str {str UnaryOp* unaryOp; str Factor* factor;} op0;
    str {str Factor* factor;} op1;
  }u;
  int tag;
} Unary;
typedef str {
  union {
    str {} op0;
    str {} op1;
  }u;
  int tag;
} UnaryOp;
typedef str {
  union {
    str {str Expr* expr;} op0;
    str {str Aux* aux;} op1;
    str {str Call* call;} op2;
    str {str Ascii* ascii;} op3;
  }u;
  int tag;
} Factor;
typedef str {
  union {
    str {str Id* id; str Expr* expr0; str Expr* expr1;} op0;
    str {str Id* id; str Expr* expr;} op1;
    str {str NumId* numId;} op2;
  }u;
  int tag;
} Aux;
typedef str {
  union {
    str {int ival;} op0;
    str {float fval;} op1;
    str {str Id* id;} op2;
  }u;
  int tag;
} NumId;
typedef str {
  union {
    str {str Id* id;str ArgList* argList;} op0;
    str {str Id* id;} op1;
  }u;
  int tag;
} Call;
typedef str {
  union {
    str {str ArgList* argList; str Arg* arg;} op0;
    str {str Arg* arg;} op1;
  }u;
  int tag;
} ArgList;
typedef str {
  union {
    str {str MatArg* matArg;} op0;
    str {str Aux* aux;} op1;
  }u;
  int tag;
} Arg;
typedef str {
  union {
    str {str Id* id; str NumId* numId0; str NumId* numId1;} op0;
  }u;
  int tag;
} MatArg;
typedef str {
  union {
    str {char cval;} op0;
  }u;
  int tag;
} Ascii;
typedef str {
  union {
    str {char ival;} op0;  // um caractere para diferenciar int/float/char
  }u;
  int tag;
} BaseType;
typedef str {
  union {
    str {float fval;} op0;
    str {int ival;} op1;
  }u;
  int tag;
} Num;

typedef str {
  int size;
  char* sval;
} Id;
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
%token V_ID AHEAD
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
}
%type<sval> V_ID
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

program : global-stmt-list

global-stmt-list : global-stmt-list global-stmt {
  printf("global-stmt-list global-stmt\n");
}
| global-stmt {
  printf("global-stmt\n");
}


global-stmt : decl-fun 
| def-fun error
| def-fun 
| decl-var SEMI_COLON {
    printf("Decl-var\n");
}
| decl-var error {
    printf("Erro\: declaracao sem ';'\n");
}
| attr-var SEMI_COLON
| block


def-fun : base-type V_ID LP param-list-void RP block {
  $3 = malloc(sizeof(Dummy));
  $5 = malloc(sizeof(Dummy));
  printf("Definicao de funcao!\n");
}

decl-fun : AHEAD base-type V_ID LP param-list-void RP  SEMI_COLON {
  printf("DECLARACAO DE FUNCAOO\n");
}

decl-var : MAT_TYPE base-type V_ID LS num RS LS num RS 
| base-type id-arr

id-arr : V_ID LS num-id RS 
| V_ID

attr-var : mat-attr 
| index-attr 
| simple-attr


simple-attr : V_ID ATTR expr SEMI_COLON

index-attr : V_ID LS num-id RS ATTR expr SEMI_COLON

mat-attr : V_ID ATTR LS num-list-list RS 

| V_ID LS num-id RS ATTR LC num-list RC 

| V_ID LS num-id RS LS num-id RS ATTR expr

num-list-list :  num-list-list LC num-list RC
| num-list

num-list : num-list num 
| num 
| V_ID

stmt : RETURN expr SEMI_COLON {
  	printf("RETURN expr SEMI_COLON\n");
}

| COPY LP V_ID V_ID  RP SEMI_COLON {
  printf("%s\n", $3);
  printf("%s\n", $4);
	printf("COPY LP V_ID V_ID  RP\n");
}

| READ LP V_ID LS num-id RS LS num-id RS RP SEMI_COLON {
  $$ = $3;
	printf("READ LP V_ID LS num-id RS LS num-id RS RP SEMI_COLON\n");
}

| READ LP V_ID LS num-id RS RP SEMI_COLON {
	printf("READ LP V_ID LS num-id RS RP SEMI_COLON\n");
}

| READ LP V_ID RP SEMI_COLON {
	printf("READ LP V_ID RP SEMI_COLON\n");
}

| PRINT expr SEMI_COLON {
	printf("PRINT expr SEMI_COLON\n");
}
	
| call SEMI_COLON  {
	printf("call SEMI_COLON \n");
}

| decl-var SEMI_COLON {
	printf("decl-var SEMI_COLON\n");
}

| attr-var SEMI_COLON {
	printf("attr-var SEMI_COLON\n");
}

| flow-control {
	printf("flow-control\n");
}

| loop {
	printf("loop\n");
}

param-list-void : VOID 
| param-list

param-list : param-list param 
| param

param : base-type V_ID 
| MAT_TYPE base-type V_ID 

loop : WHILE LP expr RP block

flow-control : IF LP expr RP block ELSE flow-control {
      printf("IF LP expr RP block ELSE flow-control\n");
}
| IF LP expr RP block ELSE block {
  printf("IF LP expr RP block ELSE block\n");
}
| IF LP error RP block ELSE block {
      printf("IF LP error RP block ELSE block\n");
}
| IF LP expr error block ELSE block {
  printf("FALTOU FECHAR IF\n");
}

block : LC stmt-list RC {
      printf("BLOCO!!!\n");
}
| LC RC {
      printf("Bloco vazio!\n");
}

stmt-list : stmt-list stmt 
| stmt

expr : add-expr relop add-expr 
| add-expr

relop : LE 
| GE 
| NEQ
| EQ 
| GT
| LT 

add-expr : add-expr addop term 
| term

addop : ADD
| SUB

term : term mulop bin 
| bin

mulop : MAT_MUL
| MUL
| DIV
| MAT_POW

bin : bin bin-logi unary 
| unary

bin-logi : AND
| OR

unary : unary-op factor 
| factor 

unary-op : NOT
| ADDR

factor : LP expr RP 
| aux
| call
| '\''ascii'\''


aux : V_ID LS expr RS LS expr RS 
| V_ID LS expr RS 
| num-id

num-id : num 
| V_ID 

call : V_ID LP arg-list RP
| V_ID LP VOID RP

arg-list : arg-list COMMA arg 
| arg

arg : mat-arg 
| aux

mat-arg : V_ID num-id num-id {

}

ascii : '\'' V_ASCII '\'' {
  // ascii = make_Ascii_op0(ASCII);
}

base-type : CHAR_TYPE 
| INT_TYPE
| FLOAT_TYPE

num : V_FLOAT
| V_INT



%%

// extern void yyerror (char const *s);
void yyerror (char const *s) {
  fprintf (stderr, "%s\n", s);
}
int main() {
  yyparse();
}