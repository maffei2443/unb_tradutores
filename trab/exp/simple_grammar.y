%code requires {
  #include "Tree.h"
  No* root;
  No** items; // Lista de ponteiros para nohs q representam regras. DAR FREE sempre
  struct {
    int ival;
    float fval;
    char* sval;
    int allocated;
  } _;
}

%{
#include <stdio.h>
extern int yylineno;
extern int yylex();
extern int yylex_destroy();
void yyerror (const char *s);
%}
%token-table
%locations
%defines
%verbose
// Write a parser header file containing macro 
// definitions for the token type names defined in
// the grammar as well as a few other declarations.

%define parse.error verbose
%define parse.lac none
%define parse.trace

// %type<no> exp NUM program
%type<no> exp NUM program
%left '+' '-'
%left '*' '/'

// %token-table

%token NUM

%union {
  int val;
  No* no;
}
%%
program: exp {
  root = $$;
  printf("PROGRAMA CORRETO! %s\n", $program->sval);
}

exp : exp '+' exp {
  printf("Exp1 : %d\n", $1->ival);
  printf("Exp3 : %d\n", $3->ival);
  $$ = No_New($1->ival + $3->ival);
  $$->sval = "exp-add";
  add_Node_Child_If_Not_Null($$, $1);
  add_Node_Child_If_Not_Null($$, No_New('+'));
  add_Node_Child_If_Not_Null($$, $3);  
  printf("%d + %d = %d\n",$1->ival, $3->ival, $$->ival );
}
| exp '-' exp {
  $$ = No_New($1->ival - $3->ival);
  $$->sval = "exp-sub";
  add_Node_Child_If_Not_Null($$, $1);
  add_Node_Child_If_Not_Null($$, $3);
}
| exp '*' exp {
  $$ = No_New($1->ival * $3->ival);
  $$->sval = "exp-mul";
  add_Node_Child_If_Not_Null($$, $1);
  add_Node_Child_If_Not_Null($$, $3);
}
| exp '/' exp {
  $$ = No_New($1->ival / $3->ival);
  $$->sval = "exp-div";
  add_Node_Child_If_Not_Null($$, $1);
  add_Node_Child_If_Not_Null($$, $3);
}
| '(' exp ')' {
  $$ = $2;
}
| NUM {
  $$ = No_New( _.ival );
  $$->sval = "NUM";
  printf("NUM : %d\n", $$->ival);
  printf("Numero correto! %s\n", yytname[NUM]);
}

%%

void yyerror (const char *s) {
  fprintf (stderr, "%s | Line %d\n", s, yylineno);
}
int main() {
  root = No_New(0);
  printf("ggeasy\n");
  yyparse();  
  show_Sub_Tree(root, 1, IVAL);
  show_Lis(root, IVAL);
  show_Sub_Tree(root, 1, SVAL);
  show_Lis(root, SVAL);
  No_Destroy(root);
  yylloc;
  yylex_destroy();
}
