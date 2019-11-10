%{
#include "new_grammar.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include "Array.h"
// #include "Colorfy.h"

#include "Common.h"
#include "Prints.h"
#include "uthash.h"
int numlines = 1, currCol = 1;
long long unsigned ERRORS_IN_SRC = 0;
int escopo = 0;
StringStart stringStart;




extern SymEntry* reshi;
extern SymEntry* add_entry(SymEntry** , char*, int);
extern void addToDel(SymEntry** p);

// Se nao existe, inicializar local. Se jah existe,
// {digit}*("."{digit}*{exp}?|("."{digit}*)?{exp})
%}
%option yylineno

%x LN_COMMENT
%x BL_COMMENT
%x STRING
EOL \n

delim [ \t\n]
ws {delim}+

digit [0-9]
letter_ [a-zA-Z_]

matType <\s*(int|float)\s*>

INT [0-9]+
exp [eE][+-]?{digit}+
FLOAT {digit}+"."{digit}+
NUM {FLOAT}|{INT}

ID {letter_}({letter_}|{digit})*
relOp >=|<=|==|!=|>|<
binMathOp @@|[-+*/@%]
binLogiOp &&|\|\|
unaryOp !|&
comment \/\/.*

base_types int|float
types mat|{base_types}
flux_control while|if|else|return
reserved_words {types}|{flux_control}|"COPY"|"PRINT"|"IREAD"|"FREAD"|"ICAST"|"FCAST"|"ahead"

sep [ \t\n\(\)<>[\]\{},.;=]
par [()]
bracket [\[\]]
curly [{}]

achar '([a-zA-Z0-9_]?)'
%%
{achar} {
  if(yyleng == 3 && yytext[1] == '\\'){
    fprintf(stderr, "Error: missing <'> at l. %d, r. %d\n", numlines, currCol+2);
    // ERRORS_IN_SRC++;
    currCol += yyleng;
    // TODO : 
  }
  else {
    if(yyleng == 3)
      yylval.cval = yytext[1];
    else
      yylval.cval = '\n';
    currCol += yyleng;
    // showCharVal();    
    return V_ASCII;
    ;
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
    // showBlockComment();
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
  fprintf(stderr,"Fim de arquivo! Comentario iniciado em :\n");
  fprintf(stderr,"linha %d, coluna %d carece de fechamento.\n",
    comm_block.lineInit,
    comm_block.colInit);
  fprintf(stderr, "Comentario: %s\n", currString.array);
  // ++ERRORS_IN_SRC;
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
    // showLineComment();
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
  // showString();
  currCol += yyleng;
  BEGIN(INITIAL);
}
<STRING>\n {
  // showMissingString();
  ++numlines, currCol = 1;
  BEGIN(INITIAL);
}
<STRING><<EOF>> {
  ++ERRORS_IN_SRC;
  // showMissingString();
  currCol += yyleng;
  BEGIN(INITIAL);
}
<STRING>. {
  currCol += yyleng;
  Array_Insert(&currString, yytext);
}

{matType} {
  // showMatParam();
  currCol += yyleng;
  return MAT_TYPE;
    ;
}

{par} {
  // showPar();
  currCol += yyleng;
  return yytext[0];
  ;
}

{curly} { 
  // showCurly();
  currCol += yyleng;
  return yytext[0];
  ;
}
{bracket} {
  // showBracket();  
  currCol += yyleng;
  return yytext[0];
  ;
}
;     {
  // showStmtEnd();
  currCol += yyleng;
  return ';';  
  ;
}
[,.] { 
  // showDotOrComma();
  currCol += yyleng;
  return yytext[0];
  ;
}

{reserved_words}/[^a-zA-Z0-9_] {  
  // printf("RES_WORD: %s\n", yytext);
  char yy0 = yytext[0];
  char yy1 = yytext[1];
  switch(yy0) {
    case 'a':
      // showAhead();
      currCol += yyleng;
      return AHEAD;
      break;
    case 'i':
      if (yy1 == 'n') {// int 
        yylval.type = R_INT;
        // showBaseType();
      }
      else{ // if
        // showFlowControl();
      } 
      currCol += yyleng;
      return yy1 == 'n' ? BASE_TYPE : IF;
      break;
    case 'f':
      // showBaseType(); currCol += yyleng;
      yylval.type = R_FLOAT;
      return BASE_TYPE;
      break;
    case 'e':
      // showFlowControl(); currCol += yyleng;
      return ELSE;
      break;
    case 'r':
      // showFlowControl(); currCol += yyleng;
      return RETURN;
      break;
    case 'w':
      // showFlowControl(); currCol += yyleng;
      return WHILE;
      break;
    case 'm':
      // showMat(); currCol += yyleng;
      return MAT_TYPE;
      break;
    case 'C':
      // showCopy(); currCol += yyleng;
      return COPY;
      break;
    case 'P':
      // showPrint(); currCol += yyleng;
      return PRINT;
      break;
    case 'I':
      printf("I...: %s\n", yytext);
      currCol += yyleng;
      if(yy1 == 'R') return IREAD;
      else if (yy1 == 'C') return ICAST;
    case 'F':
      printf("F...: %s\n", yytext);
      currCol += yyleng;
      if(yy1 == 'R') return FREAD;
      else if (yy1 == 'C') return FCAST;
    
  }
}

{ID} {              
    SymEntry* tmp = add_entry(&reshi, yytext, HID);
    // showID();
    yylval._id = malloc(yyleng + 1);
    memcpy(yylval._id, yytext, yyleng+1);
    currCol += yyleng;
    return ID;
    ;
}
{relOp} {
  // showRelOp();
  currCol += yyleng;
  char yy0 = yytext[0], yy1 = yytext[1];
  if(yyleng < 2) {  // '<' ou '>'
    return yy0;
    }  
  else
    switch(yy0) {
      case '>': return GE;
      ;
      case '<': return LE;
      ;
      case '=': return EQ;
      ;
      case '!': return NEQ;
      ;
    }
}
{binMathOp} {
  // showBinMathOp();  
  currCol += yyleng;
  if(yyleng == 2) {
    return MAT_POW;
    ;
  }
  else {
    return yytext[0];
    ;
  }
}

{binLogiOp} {
  // showBinLogiOp();  
  currCol += yyleng;
  if(yyleng == 2) {
    switch(yytext[0]) {
      case '&': return AND;
      ;
      case '|': return OR;
      ;
    }
  }
}

{FLOAT}    {
  // showFloatVal();
  currCol += yyleng;
  yylval.fval = atof(yytext);
  return V_FLOAT;
  ;
}
{INT}      {
  showIntVal();
  currCol += yyleng;
  yylval.ival = atoi(yytext);
  return V_INT;
  ;
}
{unaryOp} {
  printf("UNARIO: %s\n", yytext);
  currCol += yyleng;
  return yytext[0];
  ;
}

\n+  {numlines += yyleng, currCol = 1;}
" "+   {
  currCol += yyleng;
}
\t+ currCol += yyleng;
= {
  showAttrOp();
  currCol++;
  return '=';
  ;
}
. {
  ++ERRORS_IN_SRC;
  // showErrorCharMessage();
  currCol++;
  return ERRU;
  ;
}
%%

int yywrap() {
  return 1;
  ;
}

void delete(void** p) {
  free(*p);
  *p = NULL;
}

extern void print_reshi(void);
int _main(int argc, char** argv) {
  Array_Init(&currString, 20);
  Array_Delete(&currString);

  extern FILE *yyin, *yyout; 
  int open = 0;
  char* path = calloc(200, sizeof(char));
  if(argc > 1) {
    if(!(yyin = fopen(argv[1], "r"))) {
        perror(argv[1]);
        return (1);
        ;
    }
  }
  while(yylex());


  if (open)    fclose(yyin);
  delete((void*)&path);
  Cyan();
  printf("\n------EOF-------\n");
  if (ERRORS_IN_SRC > 0) {
    BoldRed();
    fprintf(stdout, "Code does not belong to language.\n");
    fprintf(stdout, "%llu errors were found.\n", ERRORS_IN_SRC);
  }
  else {
    BoldGreen();
    fprintf(stdout, "Congrats! The code is in the language.\n");
  }
  // print_reshi();
  Reset();
  yylex_destroy();
}