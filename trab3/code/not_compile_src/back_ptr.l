%%
. {
  printf("Chr: %s\n", yytext);
  REJECT;
  --yyin;
}
. {
  printf("Again: %s\n", yytext);
}
%% 
