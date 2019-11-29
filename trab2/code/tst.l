%{
#include <stdio.h>
int num_lines = 0, num_chars = 0;
%}
digit [0-9]
letter_ [a-zA-Z_]


%%
[0-9]*[0-9]/[a-z]{1} printf("int: %s", yytext);
[0-9]*[0-9]/[^e\.] ;

