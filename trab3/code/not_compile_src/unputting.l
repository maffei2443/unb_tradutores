%{
#include <stdio.h>
%}
letter [a-zA-Z]
%%
[0-9]{letter}+ {
  printf("matched! %s\n", yytext);
  unput('P');
  unput('U');
  unput('T');
  unput('A');
  printf("match after unput: %s\n", yytext);
}
[0-9]+{letter}+ {
  printf("HACK²! %s\n", yytext);
}
.+ printf("rejected: %s\n", yytext);


