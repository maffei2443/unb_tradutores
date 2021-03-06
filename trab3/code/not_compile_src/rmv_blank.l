%{
int numlines = 0, numcolumns = 0;
int linesBlComment, charBlComment;  // contador de linhas e caracteres alpha-num
%}
%s BL_COMMENT
%s LN_COMMENT


EOL \n
%%
"/*"       {
        linesBlComment = 0; charBlComment = 0;
        BEGIN (BL_COMMENT);
  }
<BL_COMMENT>"*/"    {
    fprintf(stdout, "This comment block has %d lines ", linesBlComment+1);
    fprintf(stdout, "and %d alpha-num!\n", charBlComment);
    BEGIN (INITIAL);
}
<BL_COMMENT>{EOL}   {
  ++ numlines;  linesBlComment++;
  numcolumns = 1;
}
<BL_COMMENT>[a-zA-Z0-9_]       {++ charBlComment; }
. ;
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