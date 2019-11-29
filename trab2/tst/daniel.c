%{
#include <stdio.h>
int num_lines = 0, num_chars = 0;
%}

%%
^[ \t]+$ {printf("espacçoooo: >%s<\n", yytext);}
\n      {printf("back-slash n\n");++num_lines; ++num_chars;}
[a-z]+       {printf("char: %s\n", yytext);++num_chars;}
.       {printf("ponto: |%s|\n", yytext);}
