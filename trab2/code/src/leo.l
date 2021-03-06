%{
#include <stdio.h>
#include <stdlib.h>
#include "Array.h"
#include "Colorfy.h"
#include "SymTable.h"
int numlines = 1, currCol = 1;
long long unsigned ERRORS_IN_SRC = 0;
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
void showAttrOp() {
  BoldGray();
  fprintf(stdout, "attr-op ");
  _blue_dash_red_token();
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

void showDotOrComma() {
  Gray();
  fprintf(stdout,"token ");
  _blue_dash_red_token();
}
void showErrorCharMessage() {
  BoldRed(),  fprintf(stdout,"Error:"), Reset();
  fprintf(stdout, " stray ");
  BoldRed(), fprintf(stdout, "'%c'[l. %d, c. %d]", yytext[0], numlines, currCol), Reset();
  fprintf(stdout, " in program.\n");
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
// {digit}*("."{digit}*{exp}?|("."{digit}*)?{exp})
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
FLOAT {digit}+"."{digit}*|{digit}*"."{digit}+
NUM {FLOAT}|{INT}

ID {letter_}({letter_}|{digit})*
relOp >=|<=|==|!=|>|<
binMathOp @@|[-+*/@]
binLogiOp &&|\|\||^|&|\|
unaryOp !|&
comment \/\/.*

base_types int|float|char
types mat|{base_types}
flux_control while|if|else|return
reserved_words {types}|{flux_control}

sep [ \t\n\(\)<>[\]\{},.;=]
par [()]
bracket [\[\]]
square [{}]

achar '(\\|\\?[a-zA-Z0-9_\\])'
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
  ++ERRORS_IN_SRC;
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
    ++ERRORS_IN_SRC;
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
  currCol += yyleng;
}

\" {
  // <STRING> HEAD
  currCol += yyleng;
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
  currCol += yyleng;
}
<STRING>\\\" {
  Array_Insert(&currString, yytext);
  fprintf(stdout, "Scaped quotes\n");
  currCol += yyleng;
}
<STRING>\" {
  showString();
  currCol += yyleng;
  BEGIN(INITIAL);
}
<STRING>\n {
  showMissingString();
  ++numlines, currCol = 1;
  BEGIN(INITIAL);
}
<STRING><<EOF>> {
  ++ERRORS_IN_SRC;
  showMissingString();
  currCol += yyleng;
  BEGIN(INITIAL);
}
<STRING>. {
  currCol += yyleng;
  Array_Insert(&currString, yytext);
}

{matType} {
    showMatParam();
    currCol += yyleng;
}

{par} {
  showPar();
  currCol += yyleng;
  // SymTable_Insert(table, yytext);
}

{square} {
  showSquare();
  currCol += yyleng;
}
{bracket} {
  showBracket();
  currCol += yyleng;
}
;     {
    showStmtEnd();
    currCol += yyleng;
}
[,.] {
  showDotOrComma();
  currCol += yyleng;
}

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
  }
  currCol += yyleng;
}

{ID}    {          
    showID();
    currCol += yyleng;
}
{relOp} {
  showRelOp();
  currCol += yyleng;
}
{binMathOp} {
  showBinMathOp();
  currCol += yyleng;
}
{binLogiOp} {
  showBinLogiOp();
  currCol += yyleng;
}

{FLOAT}    {
            if(strlen(yytext) > 1)showFloatVal();            
}
{INT}      {
      showIntVal();
}

\n  ++numlines, currCol = 1;
" "+   {
  currCol += yyleng;
}
= {
  currCol++;
  showAttrOp();
}
. {
  ++ERRORS_IN_SRC;
  showErrorCharMessage();
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
  return 0;
}