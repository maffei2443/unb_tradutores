%code requires {
typedef struct {} Dummy;
#include "unions.c"
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
}
%type<vvv> stmt num-id
%type<sval> V_ID
%type<ival> V_INT
%type<fval> V_FLOAT
%type<cval> V_ASCII
%type<dummy> LP RP LS RS LC RC CHAR_TYPE INT_TYPE FLOAT_TYPE MAT_TYPE VOID
%type<dummy> AHEAD EQ LT GT LE GE NEQ ADD SUB MUL DIV MAT_MUL MAT_POW AND
%type<dummy> OR NOT ADDR IF ELSE WHILE RETURN COPY PRINT READ SEMI_COLON
%type<dummy> DOT COMMA ATTR
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