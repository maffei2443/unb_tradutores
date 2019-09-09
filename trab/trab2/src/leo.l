%{
#include <stdio.h>
int num_lines = 0, num_chars = 0;
%}
letter_ [a-zA-Z_]
digit [0-9]
INT {digit}+
FLOAT {digit}+"."{digit}*
NUM {FLOAT}|{INT}
ID {letter_}({letter_}|{digit})*
%%



{FLOAT}    printf("PontoFlutuante: %s\n", yytext);
{ID}       printf("Identificador: %s\n", yytext);
