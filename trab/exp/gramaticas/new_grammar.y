%code requires {
  #include "Tree.h"
  #include "Common.h"
  No* root;
  struct {
    int ival;
    float fval;
    char* sval;
    int allocated;
  } _;
}

%{

#define STR(x) #x 
#define INITNODE(x) \
  yyval.no = No_New(nodeCounter++); \
  if(!yyval.no) abort(); \
  yyval.no->tname =  x  ;
#define MAKE_NODE(x) INITNODE(STR(x))
#define  GLOBAL_SCOPE "0global"
#include "Common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern int yylineno;
extern int currCol;
extern int numlines;
extern int yyleng;
extern int yylex();
void yyerror (char const *s);
void print_reshi();
extern void yylex_destroy();
extern SymEntry* SymEntry_New(char*, int, char*);
unsigned nodeCounter;

static int gambs_tam = 0;
static int gambs_qtd = 0;
SymEntry* reshi;
SymEntry** gambs;
char* currScope = NULL;
void addToDel(SymEntry** p) {
  if(gambs_qtd  >= gambs_tam) {
    gambs_tam = 2 * (gambs_tam + 1);    
    gambs = (SymEntry**)realloc(gambs, gambs_tam*sizeof(SymEntry*));
  }
  gambs[gambs_qtd] = *p;
  // printf("AddToDel: %p\n", gambs[gambs_qtd]);
  // printf("\tcom id: %s\n", gambs[gambs_qtd]->id);
  gambs_qtd++;
}

void delGambs() {
  printf("QTD : %d\n", gambs_qtd);
  for(int i = 0; i < gambs_qtd; i++){
    printf("id: %s\n", (gambs[i])->id);
    SymEntry_Destroy(gambs[i]);
    gambs[i] = NULL;
  }
  free(gambs);
}


int lastTag;   // gambs para setar corretamente se eh int,float, etc [?]
SymEntry* add_entry(SymEntry** reshi, char* id, int tag) {
    SymEntry* newEntry = NULL;
    HASH_FIND_STR((*reshi), id, newEntry);  /* id already in the hash? */
    if (newEntry == NULL) {
      // printf("ADDING %s do RESHI\n", id);
      newEntry = SymEntry_New(id, tag, currScope);
      newEntry->local.line = numlines;
      newEntry->local.col = currCol;
      HASH_ADD_STR( (*reshi), id, newEntry );  /* id: name of key field */
      addToDel(&newEntry);
      // printf(">>>>> Inseriu %s\n", newEntry->id);
    }
    else {
      printf("COULD NOT ADD %s to HASH\n", id);
    }
    return newEntry;
}

void print_reshi(void) {
    SymEntry *s;
    printf(">>>>>> TABELA DE SIMBOLOS <<<<<<<\n");
    for(s=reshi; s != NULL;) {
      printf("%10s: ", s->escopo);        
      switch(s->tag) {
        case HFLOAT:
          printf("< float, %s >", s->id);
          printf("\tVal: %f", s->u.fval);
          break;
        case HINT:
          printf("< int, %s >", s->id);
          printf("\tVal: %d", s->u.ival);
          break;
        case HID:
          printf("< id ,%s >", s->id);            
          break;
        case HCHR:
          printf("< char, %s >", s->id);
          printf("\tVal: %c\t", s->u.cval); 
          break;
        case HRES_WORD:
          printf("< res-word, %s >", s->id);        
          break;
      }
      printf("\t(%p)l. %d, c. %d\n", s,s->local.line, s->local.col);
      void* toFree = (void*)s;
      s=s->hh.next;
      SymEntry_Destroy(toFree);
    }
  printf("---------------------------\n");
}


%}
%define parse.error verbose
%define parse.lac none
%define parse.trace

%token-table
%locations

%left EQ NEQ GE LE
%left AND
%left OR
%left '<' '>'
%left '+' '-'
%left '%'
%left '*' '/' 
%left '@'
%right MAT_POW
%left '!' '&'

%union {
  char* _id;
  int ival;
  float fval;
  char cval;
  No* no;
}

%token BASE_TYPE WHILE V_INT V_FLOAT V_ASCII AHEAD
%token MAT_TYPE IF ID ICAST FCAST ELSE


%token RETURN PRINT IREAD FREAD COPY
%token AND OR
%token ERRU

%type<no> program
%type<no> globalStmtList globalStmt declFun param declOrdeclInitVar paramListVoid 
%type<no> paramList localStmtList localStmt flowControl 
%type<no> loop defFun numListList
%type<no> numList block declList expr call arglist 
%type<no> arg rvalue lvalue num typeAndNameSign

%type<_id> ID BASE_TYPE
%type<ival> V_INT
%type<cval> V_ASCII
%type<fval> V_FLOAT
%%

program: globalStmtList {
  $$ = $1;
  // MAKE_NODE(program);
  // add_Node_Child($program, $globalStmtList);
  root = $$;
  printf("Derivacao foi concluida.\n");
}


globalStmtList : %empty {
  $$ = NULL;
}
| globalStmtList globalStmt {
  if($1){
    MAKE_NODE(globalStmtList);
    add_Node_Child($$, $1);
  }
  else {
    $$ = $globalStmt;
  }
}

globalStmt : defFun 
| declFun ';' 
| declOrdeclInitVar

declFun : AHEAD BASE_TYPE ID {currScope = $ID;} '(' paramListVoid ')' {
  MAKE_NODE(declFun);
  // SymEntry
  // add_entry(&reshi)
  add_Node_Child($$, Token_New("BASE_TYPE", $BASE_TYPE));
  add_Node_Child($$, Token_New(STR(ID), $ID));
  
  free($ID), $ID = NULL;
  add_Node_Child($$, $paramListVoid);
  currScope = GLOBAL_SCOPE;
}

param : BASE_TYPE ID {
  printf("param : BASE_TYPE ID\n");
  MAKE_NODE(param);
  $$->ival = 0;
  add_Node_Child($$, Token_New("BASE_TYPE", $BASE_TYPE));
  add_Node_Child($$, Token_New("ID",$ID));
  printf("ID: %s\n", $ID);
  free($ID), $ID = NULL;

}
| BASE_TYPE ID '[' ']' {
  MAKE_NODE(param);
  add_Node_Child($$, Token_New("BASE_TYPE", $BASE_TYPE));
  add_Node_Child($$, Token_New("ID", $ID));
  printf("ID: %s\n", $ID);
  free($ID), $ID = NULL;
}
| MAT_TYPE BASE_TYPE ID {
  MAKE_NODE(param);
  $$->ival = 2;
  add_Node_Child($$, Token_New("MAT_TYPE", "mat"));
  add_Node_Child($$, Token_New("BASE_TYPE", $BASE_TYPE));
  add_Node_Child($$, Token_New("ID", $ID));
  printf("ID: %s\n", $ID);
  free($ID), $ID = NULL;

}

typeAndNameSign : BASE_TYPE ID {
  printf("[typeAndNameSign] BASE_TYPE ID \n");
  MAKE_NODE(typeAndNameSign);
  $$->ival = 0;
  printf(" >>>>>> %s\n", $BASE_TYPE);
  printf(" ------ %s\n", $ID);
  
  add_Node_Child($$, Token_New("BASE_TYPE", $BASE_TYPE));
  add_Node_Child($$, Token_New("ID", $ID));
  free($ID); $ID = NULL;
}
| '+' ID {
  printf("[TODELETE]  ID \n");
  MAKE_NODE(typeAndNameSign);
  $$->ival = 0;
  printf(" ------ %s\n", $ID);
  add_Node_Child($$, Token_New("ID", $ID));
  free($ID); $ID = NULL;
}
| BASE_TYPE ID '[' V_INT ']' {
  MAKE_NODE(typeAndNameSign);
  $$->ival = 1;
  add_Node_Child($$, Token_New("BASE_TYPE", $BASE_TYPE));
  add_Node_Child($$, Token_New("ID", $ID));
  free($ID); $ID = NULL;
  $$->childLast->ival = $V_INT;

}
| MAT_TYPE BASE_TYPE ID '[' V_INT ']' '[' V_INT ']'{
  MAKE_NODE(typeAndNameSign);
  $$->ival = 1;
  add_Node_Child($$, Token_New("MAT_TYPE", "mat"));
  $$->childLast->ival = $5;
  add_Node_Child($$, Token_New("BASE_TYPE", $BASE_TYPE));
  add_Node_Child($$, Token_New("ID", $ID));
  $$->childLast->ival = $8;
}

declOrdeclInitVar : typeAndNameSign ';'
| typeAndNameSign '=' rvalue ';' {
  MAKE_NODE(declOrdeclInitVar);
  add_Node_Child($$, $typeAndNameSign);
  add_Node_Child($$, $rvalue);
}

paramListVoid : paramList {$$ = $1;}
| %empty {
  MAKE_NODE(paramListVoid);
}

paramList : paramList ',' param {
  if(!strcmp("param", $1->tname)) { // $1 eh parametro
    $$ = $1;
    add_Node_Next($$, $param);
  }
  else {
    MAKE_NODE(paramList);
    add_Node_Next($$, $1);
    add_Node_Next($$, $param);
  }
  // add_Node_Child($$, $1);
  
}
| param

localStmtList : localStmtList localStmt {
  MAKE_NODE(localStmtList);
  add_Node_Child($$, $1);
  add_Node_Child($$, $localStmt);
}
| %empty {
  $$ = NULL;
  // MAKE_NODE(localStmtList);
}

localStmt : call ';' {
  MAKE_NODE(localStmt);
  add_Node_Child($$, $call);
}
| lvalue '=' rvalue ';'  {
  MAKE_NODE(localStmt);
  add_Node_Child($$, $lvalue);
  add_Node_Child($$, $rvalue);
}
| flowControl {
  MAKE_NODE(localStmt);
  add_Node_Child($$, $flowControl);
}
| loop {
  MAKE_NODE(localStmt);
  add_Node_Child($$, $loop);
}
| RETURN expr ';' {
  MAKE_NODE(localStmt);
  add_Node_Child($$, Token_New("RETURN", "return"));
  add_Node_Child($$, $expr);
}
| IREAD '(' lvalue ')' ';' {
  MAKE_NODE(localStmt);
  No* iread_no = Token_New("IREAD","IREAD");
  add_Node_Child($$, iread_no);
  add_Node_Child($$, $lvalue);
}
| FREAD '(' lvalue ')' ';' {
  MAKE_NODE(localStmt);
  No* fread_no = Token_New("FREAD","FREAD");
  add_Node_Child($$, fread_no);
  add_Node_Child($$, $lvalue);
}
| PRINT '(' lvalue ')' ';' {
  MAKE_NODE(localStmt);
  No* print_no = Token_New("PRINT","PRINT");
  add_Node_Child($$, print_no);
  add_Node_Child($$, $lvalue);
}
| PRINT '(' V_ASCII ')' ';' {
  MAKE_NODE(localStmt);
  $$->ival = $V_ASCII;
  add_Node_Child($$, Token_New("PRINT","PRINT"));
}
| COPY '(' lvalue lvalue ')' ';' {
  MAKE_NODE(localStmt);
  No* copy_no = Token_New("COPY","COPY");
  add_Node_Child( $$, copy_no );
  add_Node_Child( $$, $3 );
  add_Node_Child( $$, $4 );
}
| ';' {
  MAKE_NODE(localStmt);
  $$->ival = ';';
}

flowControl : IF '(' expr ')' block ELSE flowControl {
  MAKE_NODE(flowControl);
  add_Node_Child($$, Token_New("IF","if"));
  add_Node_Child($$, $expr);
  add_Node_Child($$, $block);
  add_Node_Child($$, Token_New("ELSE","else"));
  add_Node_Child($$, $7);
}
| IF '(' expr ')' block ELSE block {
  MAKE_NODE(flowControl);
  add_Node_Child($$, Token_New("IF","if"));
  add_Node_Child($$, $expr);
  add_Node_Child($$, $5);
  add_Node_Child($$, Token_New("ELSE","else"));
  add_Node_Child($$, $7);
}
| IF '(' expr ')' block {
  MAKE_NODE(flowControl);
  add_Node_Child($$, Token_New("IF","if"));
  add_Node_Child($$, $expr);
  add_Node_Child($$, $block);
}

loop : WHILE '(' expr ')' block {
  MAKE_NODE(loop);
  add_Node_Child($$, Token_New("WHILE","while"));
  add_Node_Child($$, $expr);
  add_Node_Child($$, $block);
}


defFun : BASE_TYPE ID '(' paramListVoid ')' '{' {
  SymEntry* tmp;
  HASH_FIND_STR(reshi, $ID, tmp);
  tmp->tag = HFUN;
  currScope = $ID;
} declList localStmtList '}' {
  MAKE_NODE(defFun);
  No* _BASE_TYPE = Token_New(STR(BASE_TYPE), $BASE_TYPE);
  No* _ID = Token_New(STR(ID), $ID);
  free($ID); $ID = NULL;
  add_Node_Child($$, _BASE_TYPE);
  add_Node_Child($$, _ID);
  add_Node_Child($$, $paramListVoid);
  add_Node_Child($$, $declList);
  add_Node_Child($$, $localStmtList);
  currScope = GLOBAL_SCOPE;
}

numListList :  numListList '{' numList '}' {
  MAKE_NODE(numListList);
  add_Node_Child($$, $1);
  add_Node_Child($$, $numList);
}
| %empty {
  $$ = NULL;
  // MAKE_NODE(numListList);
}

numList : numList ',' num {
  MAKE_NODE(numList);
  add_Node_Child($$, $1);
  add_Node_Child($$, $num);
}
| num {
  MAKE_NODE(numList);
  add_Node_Child($$, $num);
}


block : '{' localStmtList '}' {
  MAKE_NODE(block);
  add_Node_Child($$, $localStmtList);
}

declList : declList declOrdeclInitVar {
  MAKE_NODE(declList);
  add_Node_Child($$, $1);
  add_Node_Child($$, $declOrdeclInitVar);
}
| %empty {
  MAKE_NODE(declList);
}

expr : expr '+' expr {
  MAKE_NODE(expr); 
  $$->ival = '+'; 
  add_Node_Child($$, $1); 
  add_Node_Child($$, $3);  
}
| expr '-' expr {
  MAKE_NODE(expr); 
  $$->ival = '-'; 
  add_Node_Child($$, $1); 
  add_Node_Child($$, $3);  
}
| expr '*' expr {
  MAKE_NODE(expr); 
  $$->ival = '*'; 
  add_Node_Child($$, $1); 
  add_Node_Child($$, $3);  

}
| expr '/' expr {
  MAKE_NODE(expr); 
  $$->ival = '/'; 
  add_Node_Child($$, $1); 
  add_Node_Child($$, $3);  
}
| expr '%' expr {
  MAKE_NODE(expr); 
  $$->ival = '%'; 
  add_Node_Child($$, $1); 
  add_Node_Child($$, $3);    
}
| expr '@' expr {
  MAKE_NODE(expr); 
  $$->ival = '@'; 
  add_Node_Child($$, $1); 
  add_Node_Child($$, $3);    
}
| expr MAT_POW expr {
  MAKE_NODE(expr); 
  $$->ival = MAT_POW; 
  add_Node_Child($$, $1); 
  add_Node_Child($$, $3);    
}
| expr EQ expr {
  MAKE_NODE(expr); 
  $$->ival = EQ; 
  add_Node_Child($$, $1); 
  add_Node_Child($$, $3);  
}
| expr NEQ expr {
  MAKE_NODE(expr); 
  $$->ival = NEQ; 
  add_Node_Child($$, $1); 
  add_Node_Child($$, $3);  
}
| expr GE expr {
  MAKE_NODE(expr); 
  $$->ival = GE; 
  add_Node_Child($$, $1); 
  add_Node_Child($$, $3);  
}
| expr LE expr {
  MAKE_NODE(expr); 
  $$->ival = LE; 
  add_Node_Child($$, $1); 
  add_Node_Child($$, $3);  
}
| expr '>' expr {
  MAKE_NODE(expr); 
  $$->ival = '>'; 
  add_Node_Child($$, $1); 
  add_Node_Child($$, $3);    
}
| expr '<' expr {
  MAKE_NODE(expr); 
  $$->ival = '<'; 
  add_Node_Child($$, $1); 
  add_Node_Child($$, $3);    
}
| expr AND expr {
  MAKE_NODE(expr); 
  $$->ival = AND; 
  add_Node_Child($$, $1); 
  add_Node_Child($$, $3);  
}
| expr OR expr {
  MAKE_NODE(expr); 
  $$->ival = OR; 
  add_Node_Child($$, $1); 
  add_Node_Child($$, $3);  
}
| '!' expr {
  MAKE_NODE(expr);
  $$->ival = '!';
  add_Node_Child($$, $2);
}
| '&' expr {
  MAKE_NODE(expr);
  $$->ival = '&';
  add_Node_Child($$, $2);
}
| '(' expr ')' {
  MAKE_NODE(expr);
  add_Node_Child($$, $2);
}
| ICAST '(' expr ')' {
  MAKE_NODE(expr);
  add_Node_Child($$, Token_New("ICAST", "ICAST"));
  add_Node_Child($$, $3);
}
| FCAST '(' expr ')' {
  MAKE_NODE(expr);
  add_Node_Child($$, Token_New("FCAST", "FCAST"));
  add_Node_Child($$, $3);
}
| lvalue {
  MAKE_NODE(expr);
  add_Node_Child($$, $lvalue);
}
| call {
  MAKE_NODE(expr);
  add_Node_Child($$, $call);
}
| num {
  MAKE_NODE(expr);
  add_Node_Child($$, $num);
}

call : ID '(' arglist ')' {
  MAKE_NODE(call);
  add_Node_Child($$, Token_New("ID", $ID));
  add_Node_Child($$, $arglist);
}
| ID '('  ')' {
  MAKE_NODE(call);
  add_Node_Child($$, Token_New("ID", $ID));
}

arglist : arglist ',' arg {
  MAKE_NODE(arglist);
  add_Node_Child($$, $1);
  add_Node_Child($$, $3);
}
| arg {
  MAKE_NODE(arglist);
  add_Node_Child($$, $1);
}

arg : lvalue {
  MAKE_NODE(arg);
  add_Node_Child($$, $lvalue);
}
| ID '(' expr ')' '(' expr ')' {
  MAKE_NODE(arg);
  add_Node_Child($$, Token_New("ID", $ID));
  add_Node_Child($$, $3);
  add_Node_Child($$, $6);
}

num: V_INT {
  MAKE_NODE(num);
  $$->ival = $V_INT;
}
| V_FLOAT {
  MAKE_NODE(num);
  $$->fval = $V_FLOAT;
}


lvalue: ID {
  MAKE_NODE(lvalue);
  add_Node_Child($$, Token_New("ID", $ID));
  free($ID), $ID = NULL;
}
| ID '[' expr ']' {
  MAKE_NODE(lvalue);
  add_Node_Child($$, Token_New("ID", $ID));
  add_Node_Child($$, $expr);
}
| ID '[' expr ']' '[' expr ']' {
  MAKE_NODE(lvalue);
  add_Node_Child($$, Token_New("ID", $ID));
  add_Node_Child($$, $3);
  add_Node_Child($$, $6);
}

rvalue : expr {
  MAKE_NODE(rvalue);
  add_Node_Child($$, $expr);
}
| '{' numList '}' {
  MAKE_NODE(rvalue);
  add_Node_Child($$, $numList);
}
| '[' numListList ']' {
  MAKE_NODE(rvalue);
  add_Node_Child($$, $numListList);
}

%%

void yyerror (char const *s) {
  fprintf (stderr, "%s | l. %d, c. %d\n", s, numlines, currCol - yyleng);
  fprintf (stderr, "%s | l. %d, c. %d\n", s, yylloc.first_line, yylloc.first_column);
}

void nullify(void** p) {
  *p = NULL;
}

int main(){
  currScope = GLOBAL_SCOPE;
  reshi = NULL;
  nodeCounter = 0;
  yyparse();
  if(root) {
    show_Sub_Tree(root, 1, SVAL);
    show_Lis(root,SVAL);
  }
  print_reshi();
  yylex_destroy();
  // delGambs();
  free(gambs); gambs = NULL;
  free_All_Child(root);
  free_Lis(root);
}