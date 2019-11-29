#include <stdio.h>
#include "Common.h"
#include "Prints.h"
extern char * yytext;
extern int yyleng;
extern int numlines;
extern StringStart stringStart;
extern int currCol;
#ifdef SILENT
  #define fprintf 
#endif
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

void showFlowControl(){
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
void showCurly() {
  Red();
  fprintf(stdout, "%s-curly ", yytext[0] == '{' ? "left":"right"  );
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

void showAhead() {
  BoldRed();
  fprintf(stdout, "AHEAD ");
  BoldCyan();
  fprintf(stdout, "|---> <" );
  BoldRed();
  fprintf(stdout, "%s", yytext);
  BoldCyan();
  fprintf(stdout, ">\n");
  Reset();
}
void showCopy() {
  BoldRed();
  fprintf(stdout, "COPY ");
  BoldCyan();
  fprintf(stdout, "|---> <" );
  BoldRed();
  fprintf(stdout, "%s", yytext);
  BoldCyan();
  fprintf(stdout, ">\n");
  Reset();
}
void showPrint() {
  BoldRed();
  fprintf(stdout, "PRINT ");
  BoldCyan();
  fprintf(stdout, "|---> <" );
  BoldRed();
  fprintf(stdout, "%s", yytext);
  BoldCyan();
  fprintf(stdout, ">\n");
  Reset();
}
void showRead() {
  BoldRed();
  fprintf(stdout, "READ ");
  BoldCyan();
  fprintf(stdout, "|---> <" );
  BoldRed();
  fprintf(stdout, "%s", yytext);
  BoldCyan();
  fprintf(stdout, ">\n");
  Reset();
}