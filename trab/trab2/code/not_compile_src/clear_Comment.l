%{
/*
  Este arquivo contem as regras necessarias "reduzir" os comentarios
de um arquivo em C, substituindo cada comentario por um linha informando:
  - numero de linhas (no caso de comentariode bloco)
  - quantidade de caracteres alfa-numericos
  - quantidade de ontros caracteres (que nao alfa-num nem \n)

Cada conjunto de regras foi baseado nos arquivos:
  - clear_blockComments.l
  -clear_lineComment.l
*/
int numlines = 0, numcolumns = 0;
int linesBlComment, charBlComment, notCharBlComment;  // contador de linhas e caracteres alpha-num

int charLnComment, notCharLnComment;
%}
%s LN_COMMENT
%s BL_COMMENT


EOL \n
%%

"/*"       {
        linesBlComment = 0; charBlComment = 0;
        BEGIN (BL_COMMENT);
  }
<BL_COMMENT>"*/"    {
    fprintf(stdout, "Comment has %d lines, %d alpha-num and %d others",
           linesBlComment+1,
           charBlComment,
           notCharBlComment);
    BEGIN (INITIAL);
}
<BL_COMMENT>[a-zA-Z0-9_]       {++ charBlComment; }
<BL_COMMENT>{EOL}   {
  ++ numlines;  linesBlComment++;
  numcolumns = 1;
}
<BL_COMMENT>. {++notCharBlComment;};

"//"       {
        charLnComment = 0; notCharLnComment = 0;
        BEGIN (LN_COMMENT);
  }
<LN_COMMENT>[a-zA-Z0-9_]       {++ charLnComment; }
<LN_COMMENT>{EOL}    {
    fprintf(stdout, "Comment line has %d alpha-num, %d others\n",
    charLnComment,
    notCharLnComment);
    BEGIN (INITIAL);
  }
<LN_COMMENT>. {++notCharLnComment;};

\n printf("\n");
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