%{
int numlines = 0, numcolumns = 0;
int linesBlComment, charBlComment;  // contador de linhas e caracteres alpha-num
%}
%s BL_COMMENT
%s LN_COMMENT


EOL \n
%%
<LN_COMMENT>[a-zA-Z0-9_]       {++ charLnComment; }
<LN_COMMENT>{EOL}    {
    fprintf(stdout, "This comment line has %d alpha-num\n", charLnComment);
    BEGIN (INITIAL);
  }
<LN_COMMENT>. ;

. {;}
%% 
  
int yywrap(){return 1;} 
  
// OK ESTA FUNCIONANDO!
int main(int argc, int** argv) { 
  extern FILE *yyin, *yyout; 
  int open = 0;
  char* path = malloc(200 * sizeof(char));
  const char * dir = "to_parse/";
  long unsigned tam = strlen( dir );
  memcpy(path, dir,  tam*sizeof(char)+1);
  if(argc > 1) {
    memcpy(path+tam, argv[1], strlen(argv[1]) * sizeof(char));
    if(!(yyin = fopen(path, "r"))) {
        perror(argv[1]);
        return (1);
    }
  }
  yylex();
  if (open)    fclose(yyin);
  return 0; 
} 