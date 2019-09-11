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
int numlines = 1, numcolumns = 1;
// int comm_block.line, comm_block.isChar, comm_block.notChar;  // contador de linhas e caracteres alpha-num

typedef struct {
  int lines, isChar, notChar;
  int lineInit, colInit;
} CommBlock;

CommBlock comm_block;

int charLnComment, notCharLnComment;
%}
%x LN_COMMENT
%x BL_COMMENT


EOL \n
%%

"/*"       {
        comm_block.lines = 0; comm_block.isChar = 0; comm_block.notChar=0;
        comm_block.lineInit = numlines; comm_block.colInit = numcolumns;
        numcolumns ++;
        BEGIN (BL_COMMENT);
  }
<BL_COMMENT>"*/"    {
    fprintf(stdout, "Comment has %d lines, %d alpha-num and %d others",
           comm_block.lines+1,
           comm_block.isChar,
           comm_block.notChar);
    fprintf(stdout, "");
    BEGIN (INITIAL);
}
<BL_COMMENT>[a-zA-Z0-9_]       {++ comm_block.isChar; ++numcolumns;}
<BL_COMMENT>{EOL}   {
  ++numlines; comm_block.lines++;
  numcolumns = 1;
}
<BL_COMMENT><<EOF>> {
  fprintf(stdout,"Fim de arquivo! Comentario iniciado em :\n");
  fprintf(stdout,"linha %d, coluna %d carece de fechamento.\n",
    comm_block.lineInit,
    comm_block.colInit);
  BEGIN(INITIAL); // FUNDAMENTAL
}

<BL_COMMENT>. {++comm_block.notChar;};

"//"       {
        charLnComment = 0; notCharLnComment = 0;
        BEGIN (LN_COMMENT);
  }
<LN_COMMENT>[a-zA-Z0-9_]       {
  charLnComment ++;
  numcolumns ++;
}
<LN_COMMENT>{EOL}    {
    // fprintf(stdout, "Comment line has %d alpha-num, %d others\n",
    ++numlines;
    // charLnComment,
    // notCharLnComment);
    BEGIN (INITIAL);
  }
<LN_COMMENT>. {
  ++notCharLnComment;
  ++numcolumns;
}

\n {
  printf("\n");
  numlines++;
  numcolumns=1;
}
. {
  printf("%s", yytext);
  numcolumns=1;
}
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