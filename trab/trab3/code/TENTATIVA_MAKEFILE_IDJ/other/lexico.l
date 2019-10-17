%{
#include "grammar.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include "Array.h"
#include "Colorfy.h"
#include "SymTable.h"
#include "Common.h"
#include "Prints.h"
int numlines = 1, currCol = 1;
long long unsigned ERRORS_IN_SRC = 0;

StringStart stringStart;

// SymTable* table;

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
FLOAT {digit}+"."{digit}+
NUM {FLOAT}|{INT}

ID {letter_}({letter_}|{digit})*
relOp >=|<=|==|!=|>|<
binMathOp @@|[-+*/@]
binLogiOp &&|\|\||^|&|\|
unaryOp !|&
comment \/\/.*

void void
base_types int|float|char
types mat|{base_types}
flux_control while|if|else|return
reserved_words {types}|{flux_control}|{void}

sep [ \t\n\(\)<>[\]\{},.;=]
par [()]
bracket [\[\]]
curly [{}]

achar '(\\|\\?[a-zA-Z0-9_\\])'
%%
{achar} {

  if(yyleng == 3 && yytext[1] == '\\'){
    fprintf(stderr, "Error: missing <'> at l. %d, r. %d\n", numlines, currCol+2);
    ERRORS_IN_SRC++;
    currCol += yyleng;
    // TODO : 
  }
  else {
    currCol += yyleng;
    showCharVal();
    return ASCII;
  }
  
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
    return MAT_TYPE;
}

{par} {
  showPar();
  currCol += yyleng;
  return yytext[0] == '(' ? LP : RP;
}

{curly} {
  showCurly();
  currCol += yyleng;
  return yytext[0] == '{' ? LC : RC;
}
{bracket} {
  showBracket();
  currCol += yyleng;
  return yytext[0] == '[' ? LS : RS;
}
;     {
  showStmtEnd();
  currCol += yyleng;
  return SEMI_COLON;  
}
[,.] {
  showDotOrComma();
  currCol += yyleng;
  return yytext[0] == '.' ? DOT : COMMA;
}

{reserved_words}/[^a-zA-Z0-9_] {
  printf("RES_WORD: %s\n", yytext);
  char yy0 = yytext[0];
  char yy1 = yytext[1];
  switch(yy0) {
    case 'i':
      if (yy1 == 'n') // int
        showBaseType();
      else                  // if
        showFluxControl();
      currCol += yyleng;
      return yy1 == 'n' ? INT_TYPE : IF;
    // outras palavras reservadas comecam todas com letras diferentes
    case 'c':
      showBaseType(); currCol += yyleng;
      return CHAR_TYPE;
    case 'f':
      showBaseType(); currCol += yyleng;
      return FLOAT_TYPE;
    case 'e':
      showFluxControl(); currCol += yyleng;
      return ELSE;
    case 'r':
      showFluxControl(); currCol += yyleng;
      return RETURN;
    case 'w':
      showFluxControl(); currCol += yyleng;
      return WHILE;
    case 'm':
      showMat(); currCol += yyleng;
      return MAT_TYPE;
    case 'v':
      printf("voide!\n");
      return VOID;
    // TODO
    // COPY PRINT READ
    defaulf:
      currCol += yyleng;
      printf("OPS! FALTOU PRINT para %s\n", yytext);
  }
}

{ID} {          
    showID();
    currCol += yyleng;
    return ID;
}
{relOp} {
  showRelOp();
  currCol += yyleng;
  char yy0 = yytext[0], yy1 = yytext[1];
  if(yyleng < 2) {
    switch(yy0) {
      case '>':        
        return GT;
      case '<':
        return LT;
    }
  }
  else
    switch(yy0) {
      case '>': return GE;
      case '<': return LE;
      case '=': return EQ;
      case '!': return NEQ;
    }
}
{binMathOp} {
  showBinMathOp();
  currCol += yyleng;
  if(yyleng == 2) {
    return MAT_POW;
  }
  else {
    switch(yytext[0]) {
      case '-': return SUB;
      case '+': return ADD;
      case '/': return DIV;
      case '*': return MUL;
      case '@': return MAT_MUL;
    }
  }
}

{binLogiOp} {
  showBinLogiOp();
  currCol += yyleng;
  if(yyleng == 2) {
    switch(yytext[0]) {
      case '&': return AND;
      case '|': return OR;
    }
  }
  else {
    switch(yytext[0]) {
      case '^': return XOR_BITWISE;
      case '&': return AND_BITWISE;
      case '|': return OR_BITWISE;
    }
  }

}

{FLOAT}    {
  yylval = atof(yytext);
  return FLOAT_TYPE;
}
{INT}      {
  yylval = atoi(yytext);
  showIntVal();
  return NUM;
}

\n  ++numlines, currCol = 1;
" "+   {
  currCol += yyleng;
}
= {
  currCol++;
  showAttrOp();
  return ATTR;
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

// int _main(int argc, int** argv) {
//   Array_Init(&currString, 20);
//   extern FILE *yyin, *yyout; 
//   int open = 0;
//   char* path = malloc(200 * sizeof(char));
//   if(argc > 1) {
//     if(!(yyin = fopen(argv[1], "r"))) {
//         perror(argv[1]);
//         return (1);
//     }
//   }
//   // yylex();
//   if (open)    fclose(yyin);
//   delete(path);
//   Cyan();
//   printf("\n------EOF-------\n");
//   Array_Delete(&currString);
//   if (ERRORS_IN_SRC > 0) {
//     BoldRed();
//     fprintf(stdout, "Code does not belong to language.\n");
//     fprintf(stdout, "%llu errors were found.\n", ERRORS_IN_SRC);
//   }
//   else {
//     BoldGreen();
//     fprintf(stdout, "Congrats! The code is in the language.\n");
//   }
//   Reset();
//   return 0; 
// }