%{
#include <stdio.h>
#include <stdlib.h>
// P : parentese ~~ ()
// S : simply bracket ~~ []
// C : curly bracket ~~ {}
%}

%token CHAR INT FLOAT MAT VOID
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
%token ASCII
%%

program : global-stmt-list

global-stmt-list : global-stmt-list global-stmt 
| global-stmt

global-stmt : decl-fun 
| def-fun 
| decl-var; 
| attr-var;

def-fun : FN ID '(' param-list-void ')' base-type block

decl-fun : AHEAD FN ID '(' param-list-void ')' base-type;

decl-var : MAT base-type ID '[' NUM ']' '[' NUM ']' 
| base-type id-arr

id-arr : ID '[' num-id ']' 
| ID

attr-var : mat-attr 
| index-attr 
| simple-attr


simple-attr : ID '=' expr;

index-attr : ID '[' num-id ']' '=' expr;

mat-attr : ID '=' '['num-list-list']' 

| ID '['num-id']' '=' '{'num-list'}' 

| ID '['num-id']' '['num-id']' '=' expr

num-list-list :  num-list-list '{' num-list '}'
| num-list

num-list : num-list NUM 
| NUM 
| ID

stmt : RETURN expr;
	
	| COPY'(' ID ID')'
	
	| READ'(' ID '['num-id']' '['num-id']'')';
	
	| READ'(' ID '['num-id']' ')';
	
	| READ'(' ID ')';
	
	| PRINT'(' ID '['num-id']' '['num-id']' ')';
	
	| PRINT'(' ID '['num-id']' ')';
	
	| PRINT'(' ID ')';
	
	| call;
	
	| decl-var;
	
	| attr-var;
	
	| flux-control
	
	| loop

param-list-void : VOID 
| param-list

param-list : param-list param 
| param

param : base-type ID 
| MAT base-type ID

loop : WHILE'(' expr ')' block

flux-control : IF'(' expr ')' block ELSE flux-control 
| IF '('expr')' block ELSE block

block : LC stmt-list RC

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


aux : ID '[' expr ']' '[' expr ']' 
| ID '[' expr ']' 
| ID
| NUM

num-id : NUM 
| ID

call : ID '(' arg-list ')' 
| ID '('VOID')'

arg-list : arg-list ',' arg 
| arg

arg : mat-arg 
| aux

mat-arg : ID num-id num-id

ascii : '\'' ASCII '\''

base-type : CHAR 
| INT
| FLOAT


%%
void
yyerror (char const *s){
  fprintf (stderr, "%s\n", s);
}