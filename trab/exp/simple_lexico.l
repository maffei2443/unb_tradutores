%{
#include "simple_grammar.tab.h"
#include <stdio.h>


%}
%option yylineno
%option noyywrap
%option bison-bridge

%%

[0-9]+ {
  No* no = (No*)No_New(atoi(yytext));
  _.ival = atoi(yytext);
  free(no); no = NULL;
  
  return NUM;
}
[-*/()+] {
  return yytext[0];
}
. {

}
%%

// int _main() {
//   yylex();
// }