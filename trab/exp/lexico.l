%{
#include "grammar.tab.h"
#include <stdio.h>


%}
%option yylineno
%option noyywrap
%option bison-bridge

%%

[0-9]+ {
  printf("[lex] %s\n", yytext);
  No* no = (No*)No_New(atoi(yytext));
  _.ival = atoi(yytext);
  free(no); no = NULL;
  printf("num: %d\n ", _.ival);
  
  return NUM;
}
[-()+] {
  return yytext[0];
}
. {

}
%%

// int _main() {
//   yylex();
// }