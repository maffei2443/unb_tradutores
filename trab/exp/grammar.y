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
// extern int yylineno;
// extern int yylex(void);
%}
%define parse.error verbose
%define parse.lac none

// %type<no> exp NUM program
%type<no> exp NUM program
%left '+' '-'
// %token-table

%token NUM

%union {
  int val;
  No* no;
}
%%
program: exp {
  root = $$;
}

exp : exp '+' exp {
  printf("Exp1 : %d\n", $1->v);
  printf("Exp3 : %d\n", $3->v);
  $$ = No_New($1->v + $3->v);
  add_Node_Child($$, $1);
  add_Node_Child($$, $3);  
  printf("%d + %d = %d\n",$1->v, $3->v, $$->v );
}
| exp '-' exp {
  $$ = No_New($1->v + $3->v);
  add_Node_Child($$, $1);
  add_Node_Child($$, $3);
}
| NUM {
  $$ = No_New( _.ival );
  printf("NUM : %d\n", $$->v);
}

%%

void yyerror (char const *s) {
  fprintf (stderr, "%s | Line %d\n", s, yylineno);
}
int main() {
  root = No_New(0);
  printf("ggeasy\n");
  yyparse();  
  show_Sub_Tree(root, 1);
  show_Lis(root);
  No_Destroy(root);
}
