%{
#define forn(i, n) for(int i = 0; i < n;i++)
int numlines = 0, numcolumns = 0;
%}

EOL \n
TAB \t
%%
[ \t\n]+       {
        fprintf(stdout, " ");
        // BEGIN(EXTRA_BLANK);
}
. printf("%s", yytext);
%% 
  
int yywrap(){return 1;} 
  
// OK ESTA FUNCIONANDO!
int main(int argc, int** argv) { 
  extern FILE *yyin, *yyout; 
  int open = 0;
  char* path = malloc(200 * sizeof(char));
  if(argc > 1) {
    if(!(yyin = fopen(argv[1], "r"))) {
        perror(argv[1]);
        return (1);
    }
  }
  yylex();
  if (open)    fclose(yyin);
  printf("\n------EOF-------\n");
  return 0; 
} 