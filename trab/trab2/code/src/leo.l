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

// SymTable* table;
void _blue_dash_red_token() {
  Blue();
  fprintf(stdout, "|---> " );
  BoldCyan();
  fprintf(stdout, "<");
  BoldRed();
  fprintf(stdout, "%s", yytext);
  BoldCyan();
  fprintf(stdout, ">\n");
  Reset();
}

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
void showBaseType() {
  char c = yytext[0];
  BoldGreen();
  fprintf(stdout, "%s-type ", c == 'i' ? "int" : (c == 'c' ? "char" : "float" ) );
  _blue_dash_red_token();
  Reset();
}

void showCharVal(){
  Green();
  fprintf(stdout, "char-val ");
  _blue_dash_red_token();
}
void showFloatVal(){
  Green();
  fprintf(stdout, "float-val ");
  _blue_dash_red_token();
}
void showIntVal(){
  Green();
  fprintf(stdout, "int-val ");
  _blue_dash_red_token();
}

void showFluxControl(){
  BoldMagenta();
  fprintf(stdout, "flux-control ");
  _blue_dash_red_token();
}
void showMat(){
  Red();
  fprintf(stdout, "mat-type " );
  _blue_dash_red_token();
}

void showPar() {
  Red();
  fprintf(stdout, "%s-par ", yytext[0] == '(' ? "left":"right"  );
  _blue_dash_red_token();
}
void showBracket() {
  Yellow();
  fprintf(stdout, "%s-bracket ", yytext[0] == '[' ? "left":"right"  );
  _blue_dash_red_token();
}
void showSquare() {
  Red();
  fprintf(stdout, "%s-squarebracket ", yytext[0] == '[' ? "left":"right"  );
  _blue_dash_red_token();
}

void showMatParam() {
  Red();
  fprintf(stdout, "mat-param ");
  _blue_dash_red_token();
}
void showStmtEnd() {
  BoldRed();
  fprintf(stdout, "Statement-end ");
  _blue_dash_red_token();
}
void showRelOp() {
  Gray();
  fprintf(stdout, "rel-op ");
  _blue_dash_red_token();
}
void showBinLogiOp(){
  char c = yytext[0];
  Gray();
  fprintf(stdout, "logi-op%s ", c == '&' && yyleng < 2 ? "*" : "");
  _blue_dash_red_token();
}
void showBinMathOp() {
  BoldGray();
  fprintf(stdout, "math-op ");
  _blue_dash_red_token();
}
void showUnaryOp() {
  char c = yytext[0];
  BoldGray();
  fprintf(stdout, "unary-op%s ", c == '&' || c == '-' ? "*" : "");
  _blue_dash_red_token();
}


void showID() {
  BoldRed();
  fprintf(stdout, "ID ");
  BoldCyan();
  fprintf(stdout, "|---> <" );
  BoldRed();
  fprintf(stdout, "%s", yytext);
  BoldCyan();
  fprintf(stdout, ">\n");
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
binMathOp @@|[-+*/@]
binLogiOp &&|\|\||^|&|\|
unaryOp !|-|&
comment \/\/.*

base_types int|float|char
types mat|{base_types}
flux_control while|if|else|return
reserved_words {types}|{flux_control}

sep [ \t\n\(\)<>[\]\{},.;=]
par [()]
bracket [\[\]]
square [{}]

achar ('.')
%%
{achar} {
  showCharVal();
}
"/\*"       {
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

{matType} {
      showMatParam();
}

{par} {
  showPar();
  // SymTable_Insert(table, yytext);
}

{square} {
  showSquare();
}
{bracket} {
  showBracket();
}
;     {
    showStmtEnd();
}
[,.]

{reserved_words}/[^a-zA-Z0-9_] {
  switch(yytext[0]) {
    case 'i':
      if (yytext[1] == 'n') // int
        showBaseType();
      else                  // if
        showFluxControl();
      break;
    // outras palavras reservadas comecam todas com letras diferentes
    case 'c':
    case 'f':
      showBaseType();
      break;
    case 'e':
    case 'r':
    case 'w':
      showFluxControl();
      break;
    case 'm':
      showMat();
      break;
    defaulf:
      printf("OPS! FALTOU PRINT para %s\n", yytext);
      abort();
  }
}

{ID}    {          
          showID();
  }
{relOp} {
  showRelOp();
}
{binMathOp} {
  showBinMathOp();
}
{binLogiOp} {
  showBinLogiOp();  // wrapper for above function
}

{FLOAT}    {
            if(strlen(yytext) > 1)showFloatVal();
            else {
              printf("Simbolo: .\n");
            }          
}
{INT}      {
      showIntVal();
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

// void Show_Gambs(char * token, char * val) {
//     Blue();
//     fprintf(stdout, "________________________________________");
//     fprintf(stdout, "______________________________________________\n");
//     Reset();
//     fprintf(stdout,"%s%40s%40d\n", token, val);
// }

int main(int argc, int** argv) {
/* 
  SymTable* table = SymTable_Init();


  SymTable_Insert(table, "primeiro");
  SymTable_Insert(table, "segundo");
  SymTable_Insert(table, "primeiro");
  SymTable_Insert(table, "terceiro");
  SymTable_Insert(table, "terceiro");
  SymTable_Insert(table, "primeiro");

  Node * first = table->first;
  Node * sec = first->next;
  Node * ter = sec->next;

  fprintf(stdout, "%s\n", first->val);
  fprintf(stdout, "%d\n", first->counter);

  fprintf(stdout, "%s\n", sec->val);
  fprintf(stdout, "%d\n", sec->counter);

  fprintf(stdout, "%s\n", ter->val);
  fprintf(stdout, "%d\n", ter->counter);

  printf("addr: \n");
  printf("\t%p\n", first);
  printf("\t%p\n", first->next);
  printf("\t%p\n", first->next->next);
  printf("end-addr: \n");

  printf("prev: \n");
  printf("\t%p\n", first->prev);
  printf("\t%p\n", first->next->prev);
  printf("\t%p\n", first->next->next->prev);
  printf("end-prev: \n");

  printf("next: \n");
  printf("\t%p\n", first->next);
  printf("\t%p\n", first->next->next);
  printf("\t%p\n", first->next->next->next);
  printf("end-prev: \n");

  fprintf(stdout, "Back-ptr: %s\n", first->next->prev->val);
  fprintf(stdout, "Back-ptr: %d\n", first->next->prev->counter);

  return 0;
*/
  Array_Init(&currString, 20);
  // table = SymTable_Init();
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
  // SymTable_Show(table);
  Array_Delete(&currString);

  return 0; 
}