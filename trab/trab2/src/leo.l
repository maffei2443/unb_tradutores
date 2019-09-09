%{
#include <stdio.h>
#include <stdlib.h>
int num_lines = 0, num_chars = 0;
%}

delim [ \t\n]
ws {delim}+

digit [0-9]
letter_ [a-zA-Z_]

matType <\s*(int|float)\s*>

INT [0-9]+
exp [eE][+-]?{digit}+
FLOAT {digit}*("."{digit}*{exp}?|("."{digit}*)?{exp})
NUM {FLOAT}|{INT}

ID {letter_}({letter_}|{digit})*
relOp >=|<=|==|!=|>|<
binMathOp [+-*/]
binLogiOp &&|\|\||^|&
unaryOp !|-|&
comment //.*

base_types int|float
types mat|{base_types}
flux_control while|if|else|return
reserved_words {types}|{flux_control}

sep [ \t\n\(\)<>[\]\{},.;]
%%
{matType}                  printf("Ops! matType = %s\n", yytext);

{reserved_words}/{sep}     printf("Found a reserved word: %s\n", yytext);

r/{INT} printf("yytext: %s\n", yytext);
{ID}    {
          
          printf("ID: %s\n", yytext);
  }
{relOp} {
          printf("relOp: %s\n", yytext);

}
{FLOAT}    {
            if(strlen(yytext) > 1)printf("FLOAT: %s\n", yytext);
            else printf("skipping '.'!");
}
{INT}      {
            printf("INT: %s", yytext);
}

[ \t] {printf("espaco: >%s<\n", yytext);}

%%

int yywrap() {
  return 1;
}