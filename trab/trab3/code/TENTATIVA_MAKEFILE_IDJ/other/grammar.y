%{
#include <stdio.h>
#include <stdlib.h>
// P : parentese ~~ ()
// S : simply bracket ~~ []
// C : curly bracket ~~ {}
%}

%token CHAR_TYPE INT_TYPE FLOAT_TYPE MAT_TYPE VOID
%token CHAR INT FLOAT 
%token LETTER_ DIGIT
%token ID NUM FN AHEAD
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
  float fval;
  char cval;
  char* sval;
}
%%

program : global-stmt-list

global-stmt-list : global-stmt-list global-stmt 
| global-stmt


global-stmt : decl-fun 
| def-fun 
| decl-var SEMI_COLON 
| attr-var SEMI_COLON
| block
| INT {printf("NUMMMMM %d\n", yyval.ival);}
| FLOAT {printf("FLOOAT %f\n", yyval.fval);}

def-fun : ID LP param-list-void RP base-type block {
  printf("Definicao de funcao!\n");
}

decl-fun : AHEAD ID LP param-list-void RP base-type SEMI_COLON {
  printf("DECLARACAO DE FUNCAOO\n");
}

decl-var : MAT_TYPE base-type ID LS NUM RS LS NUM RS 
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

num-list : num-list NUM 
| NUM 
| ID

stmt : RETURN expr SEMI_COLON
	
	| COPY LP ID ID RP
	
	| READ LP ID LS num-id RS LS num-id RS RP SEMI_COLON
	
	| READ LP ID LS num-id RS RP SEMI_COLON
	
	| READ LP ID RP SEMI_COLON
	
	| PRINT LP ID LS num-id RS LS num-id RS RP SEMI_COLON
	
	| PRINT LP ID LS num-id RS RP SEMI_COLON
	
	| PRINT LP ID RP SEMI_COLON
	
	| call SEMI_COLON
	
	| decl-var SEMI_COLON
	
	| attr-var SEMI_COLON
	
	| flux-control
	
	| loop
  | NUM SEMI_COLON

param-list-void : VOID 
| param-list

param-list : param-list param 
| param

param : base-type ID 
| MAT_TYPE base-type ID

loop : WHILE '(' expr ')' block

flux-control : IF LP expr RP block ELSE flux-control 
| IF LP expr RP block ELSE block

block : LC stmt-list RC { printf("BLOCO!!!\n");}
| LC RC {printf("Bloco vazio!\n");}

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
| ID
| NUM

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


%%
// extern void yyerror (char const *s);
void yyerror (char const *s) {
  fprintf (stderr, "%s\n", s);
}
int main() {
  yyparse();
}