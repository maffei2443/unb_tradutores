%{
#include <stdio.h>
#include <stdlib.h>
#include "Array.h"
#include "Colorfy.h"
#include "SymTable.h"
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

StringStart stringStart;

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
void showString() {
  Magenta();
  fprintf(stdout, "String[l. %d, c. %d]\n", lineComm.lineInit, lineComm.colInit);
  Green();
  fprintf(stdout, "###########");
  BoldYellow();
  fprintf(stdout, "%s", currString.array);
  Green();
  fprintf(stdout, "###########\n\n");
  Reset();
}
void showMissingString() {
  BoldRed();
  fprintf(stdout, "Unterminated string[l. %d, c. %d]\n", stringStart.line, stringStart.col);
  Red();
  fprintf(stdout, "##########");
  BoldYellow();
  fprintf(stdout, "%s", currString.array);
  Red();
  fprintf(stdout, "##########\n\n");
  Reset();
}
void showType() {
  Magenta();
  fprintf(stdout, "String[l. %d, c. %d]\n", lineComm.lineInit, lineComm.colInit);
  Green();
  fprintf(stdout, "###########");
  BoldYellow();
  fprintf(stdout, "%s", currString.array);
  Green();
  fprintf(stdout, "###########\n\n");
  Reset();
}
void showInt(){
  BoldCyan();
  fprintf(stdout, "<%s>\n", yytext);
  Reset();
}
void showFluxControl(){
  BoldGreen();
  fprintf(stdout, "<%s>", yytext);
  Reset();
}
void showChar(){
  Magenta();
  fprintf(stdout, "<%s>\n", yytext);
  Reset();
}

void showFloat(){
  BoldCyan();
  fprintf(stdout, "<%s>\n", yytext);
  Reset();
}
void showMat(){
  fprintf(stdout, "\033[0;21m");
  fprintf(stdout, "<%s>\n", yytext);
  Reset();
}
void showReturn(){
  fprintf(stdout, "\033[0;66m");
  fprintf(stdout, "<%s>\n", yytext);
  Reset();
}
void showIterationControl(){
  fprintf(stdout, "\033[0;51m");
  fprintf(stdout, "<%s>\n", yytext);
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
    showLineComment();
    currCol = 1;
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
  ++currCol;
  stringStart.line = numlines;
  stringStart.col = currCol;
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
  showString();
  BEGIN(INITIAL);
}
<STRING>\n {
  showMissingString();
  ++numlines, currCol = 1;
  BEGIN(INITIAL);
}
<STRING><<EOF>> {
  showMissingString();
  BEGIN(INITIAL);
}
<STRING>. {
  Array_Insert(&currString, yytext);
}

{par} printf("%s-parenthesis: %c\n", yytext[0] == '(' ? "left": "right", yytext[0]);
;     printf("Statement-end: ;\n");
{matType}                  printf("Ops! matType = %s\n", yytext);

{reserved_words}/[^a-zA-Z0-9_] {
  switch(yytext[0]) {
    case 'i':
      if (yytext[1] == 'n') // int
        showInt();
      else                  // if
        showFluxControl();
      break;
    // outras palavras reservadas comecam todas com letras diferentes
    case 'c':
      showChar();
      break;
    case 'e':
      showFluxControl();
      break;
    case 'f':
      showFloat();
      break;
    case 'm':
      showMat();
      break;
    case 'r':
      showReturn();
      break;
    case 'w':
      showIterationControl();
      break;
  }
  printf("Reserved word: %s\n", yytext);
}

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

  SymTable* table = SymTable_Init();

  SymTable_Insert(table, "primeiro");
  SymTable_Insert(table, "segundo");
  SymTable_Insert(table, "primeiro");
  SymTable_Insert(table, "terceiro");
  SymTable_Insert(table, "terceiro");
  SymTable_Insert(table, "primeiro");

  fprintf(stdout, "%s\n", table->first->val);
  fprintf(stdout, "%d\n", table->first->counter);

  fprintf(stdout, "%s\n", table->first->next->val);
  fprintf(stdout, "%d\n", table->first->next->counter);

  fprintf(stdout, "%s\n", table->first->next->next->val);
  fprintf(stdout, "%d\n", table->first->next->next->counter);

  printf("%p\n", table->first);
  printf("%p\n", table->first->next);
  printf("%p\n", table->first->next->next);
  // printf("%p\n", table->first->next->prev);
  // fprintf(stdout, "Back-ptr: %s\n", table->first->next->prev->val);
  // fprintf(stdout, "Back-ptr: %d\n", table->first->next->prev->counter);

  return 0;

  // Array_Init(&currString, 20);

  // extern FILE *yyin, *yyout; 
  // int open = 0;
  // char* path = malloc(200 * sizeof(char));
  // if(argc > 1) {
  //   if(!(yyin = fopen(argv[1], "r"))) {
  //       perror(argv[1]);
  //       return (1);
  //   }
  // }
  // yylex();
  // if (open)    fclose(yyin);
  // delete(path);
  // Cyan();
  // printf("\n------EOF-------\n");

  // Array_Delete(&currString);

  // return 0; 
}