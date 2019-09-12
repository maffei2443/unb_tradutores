%{
#include <stdio.h>
#include <stdlib.h>
#include "Array.h"
#include "Colorfy.h"
int numlines = 1, currCol = 1;

typedef struct {
  int lines, isChar, notChar;
  int lineInit, colInit;
} CommBlock;

CommBlock comm_block;

typedef struct  {
  int lineInit,
      colInit,
      notChar,
      isChar;
} LineComment;
LineComment lineComm;

Array currString;
typedef struct {
  int line,
      col;
} StringStart;

void showBlockComment() {
  Magenta();
  fprintf(stdout, "Comentario[l. %d, c. %d]\n", comm_block.lineInit, comm_block.colInit);
  Yellow();
  fprintf(stdout, "###########");
  Red();
  fprintf(stdout, "%s", currString.array);
  Yellow();
  fprintf(stdout, "###########\n\n");
  Reset();
}
void showLineComment() {
  Magenta();
  fprintf(stdout, "Comentario[l. %d, c. %d]\n", lineComm.lineInit, lineComm.colInit);
  Yellow();
  fprintf(stdout, "###########");
  Red();
  fprintf(stdout, "%s", currString.array);
  Yellow();
  fprintf(stdout, "###########\n\n");
  Reset();
}

%}
%x LN_COMMENT
%x BL_COMMENT
%x STRING
EOL \n

delim [ \t\n]
ws {delim}+

digit [0-9]
letter_ [a-zA-Z_]

matType <\s*(int|float|char)\s*>

INT [0-9]+
exp [eE][+-]?{digit}+
FLOAT {digit}*("."{digit}*{exp}?|("."{digit}*)?{exp})
NUM {FLOAT}|{INT}

ID {letter_}({letter_}|{digit})*
relOp >=|<=|==|!=|>|<
binMathOp [+-*/@]|@@
binLogiOp &&|\|\||^|&
unaryOp !|-|&
comment \/\/.*

base_types int|float|char
types mat|{base_types}
flux_control while|if|else|return
reserved_words {types}|{flux_control}

sep [ \t\n\(\)<>[\]\{},.;=]
par [()]

%%

"/*"       {
        comm_block.lines = 0; comm_block.isChar = 0; comm_block.notChar=0;
        comm_block.lineInit = numlines; comm_block.colInit = currCol;
        currCol += 2;        
        Array_Init(&currString, 20);
        BEGIN (BL_COMMENT);
  }
<BL_COMMENT>"*/"    {
    showBlockComment();
    currCol += 2;
    Array_Delete(&currString);
    BEGIN (INITIAL);  
}
<BL_COMMENT>[a-zA-Z0-9_]+       {
  comm_block.isChar += yyleng;
  currCol += yyleng;
  Array_Insert(&currString, yytext);
}
<BL_COMMENT>{EOL}   {
  ++numlines; comm_block.lines++;
  currCol = 1;
  Array_Insert(&currString, yytext);
}
<BL_COMMENT><<EOF>> {
  fprintf(stdout,"Fim de arquivo! Comentario iniciado em :\n");
  fprintf(stdout,"linha %d, coluna %d carece de fechamento.\n",
    comm_block.lineInit,
    comm_block.colInit);
  fprintf(stdout, "Comentario: %s\n", currString.array);
  BEGIN(INITIAL); // FUNDAMENTAL
}

<BL_COMMENT>. {
  ++comm_block.notChar; ++currCol;
  Array_Insert(&currString, yytext);
};

"//"       {
        lineComm.lineInit = numlines; lineComm.colInit = currCol+2;
        lineComm.isChar = 0; lineComm.notChar = 0;
        currCol+= 2;
        Array_Init(&currString, 20);
        BEGIN (LN_COMMENT);
  }
<LN_COMMENT>[a-zA-Z0-9_]+       {
  lineComm.isChar += yyleng;
  currCol += yyleng;
  Array_Insert(&currString, yytext);
}
<LN_COMMENT>{EOL}    {
    ++numlines;
    currCol = 1;
    showLineComment();
    Array_Delete(&currString);
    BEGIN (INITIAL);
  }
<LN_COMMENT>. {
  ++lineComm.notChar;
  ++currCol;
  Array_Insert(&currString, yytext);
}

\\/\" {
  // N faz parte da linguagem. Tratamento: considerar que a string
  // começa em >"<.
  fprintf(stdout,"Error: |%s| encontered at l. %d, r. %d.\n", yytext, numlines, currCol);
}

\" {
  // <STRING> HEAD
  Array_Delete(&currString);
  Array_Init(&currString, 10);
  BEGIN(STRING);
}

<STRING>[^"\\\n] {
  if( 1 + currString.size > 256) {
    // string muito grande. Erro!
    abort();
  }
  currCol++;
  Array_Insert(&currString, yytext);
}
<STRING>\\\\ {
  Array_Insert(&currString, yytext);
  fprintf(stdout, "Escaped back-slash\n");
}
<STRING>\\\" {
  Array_Insert(&currString, yytext);
  fprintf(stdout, "Scaped quotes\n");
}
<STRING>\" {
  fprintf(stdout, "End of string: |%s|\n", currString.array);
  BEGIN(INITIAL);
}
<STRING>\n {
  fprintf(stdout, "Unterminated string: |%s|\n", currString.array);
  BEGIN(INITIAL);
  ++numlines, currCol = 1;
}
<STRING><<EOF>> {
  fprintf(stdout, "Unterminated string: |%s|\n", currString.array);
  BEGIN(INITIAL);
}
<STRING>. {
  Array_Insert(&currString, yytext);
}

{par} printf("%s-parenthesis: %c\n", yytext[0] == '(' ? "left": "right", yytext[0]);
;     printf("Statement-end: ;\n");
{matType}                  printf("Ops! matType = %s\n", yytext);

{reserved_words}/{sep}     printf("Found a reserved word: %s\n", yytext);

{ID}    {          
          printf("ID: %s\n", yytext);
  }
{relOp} {
          printf("relOp: %s\n", yytext);
}
{FLOAT}    {
            if(strlen(yytext) > 1)printf("FLOAT: %s\n", yytext);
            else {
              printf("Simbolo: .\n");
            }          
}
{INT}      {
            printf("Int: %s\n", yytext);
}

\n  ++numlines, currCol = 1;
" "+   {
  currCol += yyleng;
}
. {
  fprintf(stdout, "Unknown: %c\n", yytext[0]);
  currCol++;
}
%%

int yywrap() {
  return 1;
}

void delete(void* p) {
  free(p);
  p = NULL;
}

int main(int argc, int** argv) {

  Array_Init(&currString, 20);

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
  delete(path);
  Cyan();
  printf("\n------EOF-------\n");

  Array_Delete(&currString);

  return 0; 
}