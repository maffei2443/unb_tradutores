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
%token CHAR INT FLOAT 
%token LETTER_ DIGIT
%token ID FN AHEAD
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
%token ASCII SEMI_COLON DOT COMMA ATTR
%token XOR_BITWISE AND_BITWISE OR_BITWISE

%union {
  int ival;
  double fval;
  char cval;
  char* sval;

}

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


def-fun : base-type ID LP param-list-void RP block {
  printf("Definicao de funcao!\n");
}

decl-fun : AHEAD base-type ID LP param-list-void RP  SEMI_COLON {
  printf("DECLARACAO DE FUNCAOO\n");
}

decl-var : MAT_TYPE base-type ID LS num RS LS num RS 
| base-type id-arr

id-arr : ID LS num-id RS 
| ID

attr-var : mat-attr 
| index-attr 
| simple-attr


simple-attr : ID ATTR expr SEMI_COLON

index-attr : ID LS num-id RS ATTR expr SEMI_COLON

mat-attr : ID ATTR LS num-list-list RS 

| ID LS num-id RS ATTR LC num-list RC 

| ID LS num-id RS LS num-id RS ATTR expr

num-list-list :  num-list-list LC num-list RC
| num-list

num-list : num-list num 
| num 
| ID

stmt : RETURN expr SEMI_COLON {
  	printf("RETURN expr SEMI_COLON\n");
}

| COPY LP ID ID RP SEMI_COLON {
	printf("COPY LP ID ID RP\n");
}

| READ LP ID LS num-id RS LS num-id RS RP SEMI_COLON {
	printf("READ LP ID LS num-id RS LS num-id RS RP SEMI_COLON\n");
}

| READ LP ID LS num-id RS RP SEMI_COLON {
	printf("READ LP ID LS num-id RS RP SEMI_COLON\n");
}

| READ LP ID RP SEMI_COLON {
	printf("READ LP ID RP SEMI_COLON\n");
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

param : base-type ID 
| MAT_TYPE base-type ID

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


aux : ID LS expr RS LS expr RS 
| ID LS expr RS 
| num-id

num-id : INT 
| FLOAT
| ID

call : ID LP arg-list RP
| ID LP VOID RP

arg-list : arg-list COMMA arg 
| arg

arg : mat-arg 
| aux

mat-arg : ID num-id num-id

ascii : '\'' ASCII '\''

base-type : CHAR_TYPE 
| INT_TYPE
| FLOAT_TYPE

num : FLOAT
| INT

%%

// extern void yyerror (char const *s);
void yyerror (char const *s) {
  fprintf (stderr, "%s\n", s);
}
int main() {
  yyparse();
}