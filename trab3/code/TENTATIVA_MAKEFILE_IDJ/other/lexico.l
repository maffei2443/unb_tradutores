%{
#include "grammar.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include "Array.h"
#include "Colorfy.h"

#include "Common.h"
#include "Prints.h"
#include "uthash.h"
#include "utlist.h"
int numlines = 1, currCol = 1;
long long unsigned ERRORS_IN_SRC = 0;
int escopo = 0;
StringStart stringStart;

typedef struct {
  int line, col;
  int scope;
  struct Local * next;
} Local;

typedef struct {
  char id[257];
  int tag;
  union {
    int ival;
    float fval;
    char cval;
  } u;
  UT_hash_handle hh;
  Local local;
} SymEntry;

enum _HASH_TYPES{
  HINT, HFLOAT, HID, HCHR, HRES_WORD
};

int CurrTokenTag;

SymEntry* reshi = NULL;

// Se nao existe, inicializar local. Se jah existe,
SymEntry* add_entry(char* id) {
    SymEntry* newEntry;
    HASH_FIND_STR(reshi, id, newEntry);  /* id already in the hash? */
    if (newEntry == NULL) {
      newEntry = (SymEntry *)malloc(sizeof(SymEntry));
      strcpy(newEntry->id, id);
      newEntry->local.line = numlines;
      newEntry->local.col = currCol; newEntry->local.next = NULL;
      newEntry->tag = CurrTokenTag;
      HASH_ADD_STR( reshi, id, newEntry );  /* id: name of key field */
      // printf(">>>>> Inseriu %s\n", newEntry->id);
    }
    return newEntry;
}

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

matType <\s*(int|float|char)\s*>

INT [0-9]+
exp [eE][+-]?{digit}+
FLOAT {digit}+"."{digit}+
NUM {FLOAT}|{INT}

ID {letter_}({letter_}|{digit})*
relOp >=|<=|==|!=|>|<
binMathOp @@|[-+*/@]
binLogiOp &&|\|\|
unaryOp !|&
comment \/\/.*

void void
base_types int|float|char
types mat|{base_types}
flux_control while|if|else|return
reserved_words {types}|{flux_control}|{void}|"ahead"|"COPY"|"PRINT"|"READ"

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
    yylval.cval = yytext[0];
    currCol += yyleng;
    showCharVal();
    CurrTokenTag = HCHR;
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
    ;
}

{par} {
  showPar();
  currCol += yyleng;
  return yytext[0] == '(' ? LP : RP;
  ;
}

{curly} {
  showCurly();
  currCol += yyleng;
  if(yytext[0] == '{') {
    escopo++; return LC;
  }
  else {
    escopo--; return RC;
  }
  ;
}
{bracket} {
  showBracket();
  currCol += yyleng;
  return yytext[0] == '[' ? LS : RS;
  ;
}
;     {
  showStmtEnd();
  currCol += yyleng;
  return SEMI_COLON;  
  ;
}
[,.] {
  showDotOrComma();
  currCol += yyleng;
  return yytext[0] == '.' ? DOT : COMMA;
  ;
}

{reserved_words}/[^a-zA-Z0-9_] {
  CurrTokenTag = HRES_WORD;
  add_entry(yytext);
  // printf("RES_WORD: %s\n", yytext);
  char yy0 = yytext[0];
  char yy1 = yytext[1];
  switch(yy0) {
    case 'i':
      if (yy1 == 'n') // int
        showBaseType();
      else                  // if
        showFlowControl();
      currCol += yyleng;
      return yy1 == 'n' ? INT_TYPE : IF;
      break;
    // outras palavras reservadas comecam todas com letras diferentes
    case 'c':
      showBaseType(); currCol += yyleng;
      return CHAR_TYPE;
      break;
    case 'f':
      showBaseType(); currCol += yyleng;
      return FLOAT_TYPE;
      break;
    case 'e':
      showFlowControl(); currCol += yyleng;
      return ELSE;
      break;
    case 'r':
      showFlowControl(); currCol += yyleng;
      return RETURN;
      break;
    case 'w':
      showFlowControl(); currCol += yyleng;
      return WHILE;
      break;
    case 'm':
      showMat(); currCol += yyleng;
      return MAT_TYPE;
      break;
    case 'v':
      printf("voide!\n");
      return VOID;
      break;
    // TODO
    // COPY PRINT READ
    case 'a':
      showAhead(); currCol += yyleng;
      return AHEAD;
      break;
    case 'C':
      showCopy(); currCol += yyleng;
      return COPY;
      break;
    case 'P':
      showPrint(); currCol += yyleng;
      return PRINT;
      break;
    case 'R':
      showRead(); currCol += yyleng;
      return READ;
      break;
    
    defaulf:
      currCol += yyleng;
      break;
  }
}

{ID} {          
    CurrTokenTag = HID;
    SymEntry* tmp = add_entry(yytext);
    // printf("ID RECUPERADO DA HASH : %s\n", tmp->id);
    showID();
    yylval._id = malloc(yyleng + 1);
    memcpy(yylval._id, yytext, yyleng+1);
    currCol += yyleng;
    return ID;
    ;
}
{relOp} {
  showRelOp();
  currCol += yyleng;
  char yy0 = yytext[0], yy1 = yytext[1];
  if(yyleng < 2) {
    switch(yy0) {
      case '>':        
        return GT;
        ;
      case '<':
        return LT;
        ;
    }
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
  showBinMathOp();
  currCol += yyleng;
  if(yyleng == 2) {
    return MAT_POW;
    ;
  }
  else {
    switch(yytext[0]) {
      case '-': return SUB;
      ;
      case '+': return ADD;
      ;
      case '/': return DIV;
      ;
      case '*': return MUL;
      ;
      case '@': return MAT_MUL;
      ;
    }
  }
}

{binLogiOp} {
  showBinLogiOp();
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
  CurrTokenTag = HFLOAT;
  SymEntry* t = add_entry(yytext);
  yylval.fval = atof(yytext);
  t->u.fval = yylval.fval;
  showFloatVal();
  return V_FLOAT;
  ;
}
{INT}      {
  CurrTokenTag = HINT;
  SymEntry* t = add_entry(yytext);
  yylval.ival = atoi(yytext);
  t->u.ival = yylval.ival;
  showIntVal();
  return V_INT;
  ;
}

\n  ++numlines, currCol = 1;
" "+   {
  currCol += yyleng;
}
= {
  currCol++;
  showAttrOp();
  return ATTR;
  ;
}
. {
  ++ERRORS_IN_SRC;
  showErrorCharMessage();
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

void print_reshi() {
    SymEntry *s;
    for(s=reshi; s != NULL; s=s->hh.next) {        
        switch(s->tag) {
          case HFLOAT:
            printf("<type, Id>: < float ,%s >", s->id);
            printf("\tVal: %f\n", s->u.fval);
            break;
          case HINT:
            printf("<type, Id>: < int ,%s >", s->id);
            printf("\tVal: %d\n", s->u.ival); 
          case HID:
            break;
            printf("<type, Id>: < id ,%s >", s->id);            
            break;
          case HCHR:
            printf("<type, Id>: < char ,%s >", s->id);
            printf("\tVal: %c\n", s->u.cval); 
            break;
          case HRES_WORD:
            printf("<type, Id>: < res-word,%s >", s->id);        
            break;
        }
        printf("\t\tl. %d, c. %d\n", s->local.line, s->local.col);
    }
}

int _main(int argc, int** argv) {
  Array_Init(&currString, 20);
  Array_Delete(&currString);
  // char c[][10] = {"return", "while", "if", "else", "int", "float"};
  // add_entry(c[0]);  add_entry(c[1]);
  // add_entry(c[2]);  add_entry(c[3]);

  extern FILE *yyin, *yyout; 
  int open = 0;
  char* path = malloc(200 * sizeof(char));
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
  print_reshi();
  Reset();
  yylex_destroy();
}