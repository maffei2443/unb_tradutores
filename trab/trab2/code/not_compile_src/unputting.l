%{
#include <stdio.h>
%}
letter [a-zA-Z]
%%
[0-9]{letter}{2} {
  printf("matched! %s\n", yytext);
  unput(yytext[0]);
  printf("unputted! %c\n", yytext[0]);
}
[0-9]{letter} {
  printf("HACK²! %s\n", yytext);
}
. printf("rejected: %s\n", yytext);


