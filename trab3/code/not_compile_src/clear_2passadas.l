%{
int numlines = 0, numcolumns = 0;
int linesBlComment;
%}
%s BL_COMMENT
%s LN_COMMENT


EOL \n
%%
"/*"      {linesBlComment = 0; BEGIN (BL_COMMENT); }
<BL_COMMENT>"*/"    {
    BEGIN (INITIAL);
    fprintf(stdout, "This comment block has %d lines!", linesBlComment);
}
<BL_COMMENT>{EOL}   {
  ++ numlines;  linesBlComment++;
  numcolumns = 1;
}
<BL_COMMENT>.       {++ numcolumns; }

"//".+\n           {;}
\n {fprintf(stdout, "new line\n"); numlines++;}
[ \t]+ {
      fprintf(stdout, "Branco: |%s|\n", yytext);} 
      fprintf(yyout, " ", yytext);} 
    }
.       { fprintf(yyout, "%s", yytext); }

%% 
  
int yywrap(){return 1;} 
  
// driver code  
int main(int argc, int** argv) { 
  extern FILE *yyin, *yyout; 
  if(argc > 1) {
    if(!(yyin = fopen(argv[1], "r"))) {
        perror(argv[1]);
        return (1);
      }
  }
  yyout = fopen("cleared.txt", "w"); 
  yylex();
  fclose(yyout);

  yyin = fopen("cleared.txt", "r");
  yyout = fopen("compact.c", "w");
  yylex();

  /* yyin and yyout as pointer 
  of File type */
  return 0; 
} 