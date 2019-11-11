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


SymEntry* add_entry(SymEntry** reshi, char* id, int tag) {
    SymEntry* newEntry = NULL;
    HASH_FIND_STR((*reshi), id, newEntry);  /* id already in the hash? */
    if (newEntry == NULL) {
      newEntry = SymEntry_New(id, tag, currScope);
      newEntry->local.line = numlines;
      newEntry->local.col = currCol;
      HASH_ADD_STR( (*reshi), id, newEntry );  /* id: name of key field */
      addToDel(&newEntry);
    }
    else {    // Checar se eh declaracao no msm escopo. Se for, nao adiciona e dah pau (retorna NULL);
      printf("Possivel conflito com %s:%s\n", id, newEntry->escopo);
      for(; newEntry->next; newEntry = newEntry->next) {
        continue;  // apenas para testar se encadeamento tah ok
        if(strcmp(id, newEntry->id) == 0 && strcmp(currScope, newEntry->escopo)) {
          printf("Erro: redeclaracao de %s:%s em l.%d, r.%d\n",
            currScope, id, newEntry->local.line, newEntry->local.col);
          return NULL;
        }
      }
      if( /* 0 &&  */strcmp(id, newEntry->id) == 0 && !strcmp(currScope, newEntry->escopo) ) {          
        printf("Erro: redeclaracao de %s:%s em l.%d, r.%d\n",
          currScope, id, newEntry->local.line, newEntry->local.col);
        return NULL;
      }
      else {
        newEntry->next = SymEntry_New(id, tag, currScope);
        newEntry->next->local.line = numlines;
        newEntry->next->local.col = currCol;
      }
    }
    return newEntry;
}

// funcao booleana.
// Retorna NULL caso nao o tenha sido; senao,
// retorna ponteiro para declracao mais prohxima.
SymEntry* was_declared(SymEntry** reshi, char* id){
  SymEntry* oldEntry = NULL;
  SymEntry* last_same_id = oldEntry;
  HASH_FIND_STR((*reshi), id, oldEntry);
  while( oldEntry ) {
    if( strcmp(oldEntry->id, id) != 0 ) {
      oldEntry = oldEntry->next;
    }
    else if(strcmp(oldEntry->escopo, currScope) == 0){  // declaracao sob mesmo escopo
      return oldEntry;
    }
    else if(strcmp(oldEntry->escopo, GLOBAL_SCOPE) == 0){
      last_same_id = oldEntry;
    }
  }
  return last_same_id;
}

void show_entry(SymEntry* s) {
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
    case HFUN:
      printf("<fun, %s, %s>", s->id, type2string(s->type));
  }
  printf("\t(%p)l. %d, c. %d\n", s,s->local.line, s->local.col);

}

void print_reshi(void) {
    SymEntry *s;
    SymEntry *nexti;
    printf(">>>>>> TABELA DE SIMBOLOS <<<<<<<\n");
    for(s=reshi; s != NULL;s = nexti) {
      nexti = s->hh.next;
      show_entry(s);
      while(s->next) {
        show_entry(s->next);
        s = s->next;
      }      
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
  Type type;
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

%type<_id> ID 
%type<type> BASE_TYPE
%type<ival> V_INT
%type<cval> V_ASCII
%type<fval> V_FLOAT
%%

program: globalStmtList {
  $$ = $1;
  root = $$;
  printf("Derivacao foi concluida.\n");
}


globalStmtList : %empty {
  $$ = NULL;
}
| globalStmtList globalStmt {
  if($1){
    MAKE_NODE(globalStmtList);
    add_Node_Child_If_Not_Null($$, $1);
    add_Node_Child_If_Not_Null($$, $globalStmt);
  }
  else
    $$ = $globalStmt;
  // if($1){
  //   $$ = $1;
  //   add_Node_Child_If_Not_Null($$, $globalStmt);
  // }
  // else {
  //   $$ = $globalStmt;
  // }
}

globalStmt : defFun 
| declFun ';' 
| declOrdeclInitVar

declFun : AHEAD BASE_TYPE ID {
  SymEntry* neoEntry = add_entry(&reshi, $ID, HFUN);
  neoEntry->tag = $BASE_TYPE;
  currScope = $ID;
} '(' paramListVoid ')' {
  SymEntry* tmp;
  HASH_FIND_STR(reshi, $ID, tmp);
  tmp->tag = HFUN;
  tmp->type = $BASE_TYPE;

  MAKE_NODE(declFun);
  
  add_Node_Child_If_Not_Null($$, Token_New("BASE_TYPE", type2string($BASE_TYPE)));
  add_Node_Child_If_Not_Null($$, Token_New(STR(ID), $ID));
  free($ID), $ID = NULL;
  add_Node_Child_If_Not_Null($$, $paramListVoid);
  currScope = GLOBAL_SCOPE;
}


typeAndNameSign : BASE_TYPE ID {
  SymEntry* neoEntry = add_entry(&reshi, $ID, $BASE_TYPE);

  printf("[typeAndNameSign] BASE_TYPE ID \n");
  MAKE_NODE(typeAndNameSign);
  $$->ival = 0;
  printf(" >>>>>> %s\n", type2string($BASE_TYPE));
  printf(" ------ %s\n", $ID);
  
  add_Node_Child_If_Not_Null($$, Token_New("BASE_TYPE", type2string($BASE_TYPE)));
  add_Node_Child_If_Not_Null($$, Token_New("ID", $ID));
  free($ID); $ID = NULL;
}
| BASE_TYPE ID '[' V_INT ']' {
  SymEntry* neoEntry = add_entry(&reshi, $ID, $BASE_TYPE);

  MAKE_NODE(typeAndNameSign);
  $$->ival = 1;
  add_Node_Child_If_Not_Null($$, Token_New("BASE_TYPE", type2string($BASE_TYPE)));
  add_Node_Child_If_Not_Null($$, Token_New("ID", $ID));
  free($ID); $ID = NULL;
  $$->childLast->ival = $V_INT;

}
| MAT_TYPE BASE_TYPE ID '[' V_INT ']' '[' V_INT ']'{
  MAKE_NODE(typeAndNameSign);
  $$->ival = 1;
  add_Node_Child_If_Not_Null($$, Token_New("MAT_TYPE", "mat"));
  $$->childLast->ival = $5;
  add_Node_Child_If_Not_Null($$, Token_New("BASE_TYPE", type2string($BASE_TYPE)));
  add_Node_Child_If_Not_Null($$, Token_New("ID", $ID));
  $$->childLast->ival = $8;
}

declOrdeclInitVar : typeAndNameSign ';'
| typeAndNameSign '=' rvalue ';' {
  MAKE_NODE(declOrdeclInitVar);
  add_Node_Child_If_Not_Null($$, $typeAndNameSign);
  add_Node_Child_If_Not_Null($$, $rvalue);
}

paramListVoid : paramList {
  No* tmp = $1;
  while(tmp) {
    printf("...%p", tmp);fflush(stdout);
    printf("<!>param-sval: %s\n", tmp->sval);
    tmp = tmp->nextAux;
  }
  printf("gg-easy\n"); fflush(stdout);
  $$ = $1;
}
| %empty {$$ = NULL;}

paramList : paramList ',' param {
  $3->nextAux = $1;
  $3->hasAux = 1;
  $$ = $3;
}
| param {
  $$ = $1;
  $$->hasAux = 0; 
}

param : BASE_TYPE ID {
  $$ = Token_New(STR(param), $ID);
  SymEntry* neoEntry = add_entry(&reshi, $ID, HID);
  neoEntry->type = $BASE_TYPE;
  $param->symEntry = neoEntry;
  // $$->ival = 0;  
  // add_Node_Child_If_Not_Null($$, Token_New("BASE_TYPE", type2string($BASE_TYPE)));
  // add_Node_Child_If_Not_Null($$, Token_New("ID",$ID));
  free($ID), $ID = NULL;

}
| BASE_TYPE ID '[' ']' {
  $$ = Token_New(STR(param), $ID);
  SymEntry* neoEntry = add_entry(&reshi, $ID, HID);
  if($BASE_TYPE == TYPE_INT) {
    neoEntry->type = TYPE_ARRAY_INT;
  }
  else if ($BASE_TYPE == TYPE_FLOAT) {
    neoEntry->type = TYPE_ARRAY_FLOAT;
  }
  else {
    // Nao deve entrar aqui.
    printf("BASE_TYPE deve ser apenas TYPE_INT ou TYPE_FLOAT\n");
    abort();
  }
  $param->symEntry = neoEntry;
  free($ID), $ID = NULL;
}
| MAT_TYPE BASE_TYPE ID {
  $param = Token_New(STR(param), $ID);
  SymEntry* neoEntry = add_entry(&reshi, $ID, HID);
  if($BASE_TYPE == TYPE_INT) {
    neoEntry->type = TYPE_MAT_INT;
  }
  else if ($BASE_TYPE == TYPE_FLOAT) {
    neoEntry->type = TYPE_MAT_FLOAT;
  }
  else {
    printf("BASE_TYPE deve ser apenas TYPE_INT ou TYPE_FLOAT\n");
    abort();
  }
  $param->symEntry = neoEntry;
  free($ID), $ID = NULL;
}


localStmtList : localStmtList localStmt {
  MAKE_NODE(localStmtList);
  add_Node_Child_If_Not_Null($$, $1);
  add_Node_Child_If_Not_Null($$, $localStmt);
}
| %empty {
  $$ = NULL;
  // MAKE_NODE(localStmtList);
}

localStmt : call ';' {
  MAKE_NODE(localStmt);
  add_Node_Child_If_Not_Null($$, $call);
}
| lvalue '=' rvalue ';'  {
  MAKE_NODE(localStmt);
  add_Node_Child_If_Not_Null($$, $lvalue);
  add_Node_Child_If_Not_Null($$, $rvalue);
}
| flowControl {
  MAKE_NODE(localStmt);
  add_Node_Child_If_Not_Null($$, $flowControl);
}
| loop {
  MAKE_NODE(localStmt);
  add_Node_Child_If_Not_Null($$, $loop);
}
| RETURN expr ';' {
  MAKE_NODE(localStmt);
  add_Node_Child_If_Not_Null($$, Token_New("RETURN", "return"));
  add_Node_Child_If_Not_Null($$, $expr);
}
| IREAD '(' lvalue ')' ';' {
  MAKE_NODE(localStmt);
  No* iread_no = Token_New("IREAD","IREAD");
  add_Node_Child_If_Not_Null($$, iread_no);
  add_Node_Child_If_Not_Null($$, $lvalue);
}
| FREAD '(' lvalue ')' ';' {
  MAKE_NODE(localStmt);
  No* fread_no = Token_New("FREAD","FREAD");
  add_Node_Child_If_Not_Null($$, fread_no);
  add_Node_Child_If_Not_Null($$, $lvalue);
}
| PRINT '(' lvalue ')' ';' {
  MAKE_NODE(localStmt);
  No* print_no = Token_New("PRINT","PRINT");
  add_Node_Child_If_Not_Null($$, print_no);
  add_Node_Child_If_Not_Null($$, $lvalue);
}
| PRINT '(' V_ASCII ')' ';' {
  MAKE_NODE(localStmt);
  $$->ival = $V_ASCII;
  add_Node_Child_If_Not_Null($$, Token_New("PRINT","PRINT"));
}
| COPY '(' lvalue lvalue ')' ';' {
  MAKE_NODE(localStmt);
  No* copy_no = Token_New("COPY","COPY");
  add_Node_Child_If_Not_Null( $$, copy_no );
  add_Node_Child_If_Not_Null( $$, $3 );
  add_Node_Child_If_Not_Null( $$, $4 );
}
| ';' {
  MAKE_NODE(localStmt);
  $$->ival = ';';
}

flowControl : IF '(' expr ')' block ELSE flowControl {
  MAKE_NODE(flowControl);
  add_Node_Child_If_Not_Null($$, Token_New("IF","if"));
  add_Node_Child_If_Not_Null($$, $expr);
  add_Node_Child_If_Not_Null($$, $block);
  add_Node_Child_If_Not_Null($$, Token_New("ELSE","else"));
  add_Node_Child_If_Not_Null($$, $7);
}
| IF '(' expr ')' block ELSE block {
  MAKE_NODE(flowControl);
  add_Node_Child_If_Not_Null($$, Token_New("IF","if"));
  add_Node_Child_If_Not_Null($$, $expr);
  add_Node_Child_If_Not_Null($$, $5);
  add_Node_Child_If_Not_Null($$, Token_New("ELSE","else"));
  add_Node_Child_If_Not_Null($$, $7);
}
| IF '(' expr ')' block {
  MAKE_NODE(flowControl);
  add_Node_Child_If_Not_Null($$, Token_New("IF","if"));
  add_Node_Child_If_Not_Null($$, $expr);
  add_Node_Child_If_Not_Null($$, $block);
}

loop : WHILE '(' expr ')' block {
  MAKE_NODE(loop);
  add_Node_Child_If_Not_Null($$, Token_New("WHILE","while"));
  add_Node_Child_If_Not_Null($$, $expr);
  add_Node_Child_If_Not_Null($$, $block);
}

defFun : BASE_TYPE ID '('{
  SymEntry* neoEntry = add_entry(&reshi, $ID, HFUN);
  neoEntry->tag = $BASE_TYPE;
  currScope = $ID;
} paramListVoid ')' '{' declList localStmtList '}' {
  SymEntry* tmp;
  HASH_FIND_STR(reshi, $ID, tmp);
  tmp->tag = HFUN;
  tmp->type = $BASE_TYPE;
  MAKE_NODE(defFun);
  No* _BASE_TYPE = Token_New(STR(BASE_TYPE), type2string($BASE_TYPE));
  No* _ID = Token_New(STR(ID), $ID);
  free($ID); $ID = NULL;
  add_Node_Child_If_Not_Null($$, _BASE_TYPE);
  add_Node_Child_If_Not_Null($$, _ID);
  if($paramListVoid)
    add_Node_Child_If_Not_Null($$, $paramListVoid);

  add_Node_Child_If_Not_Null($$, $declList);
  add_Node_Child_If_Not_Null($$, $localStmtList);
  currScope = GLOBAL_SCOPE;
}

numListList :  numListList '{' numList '}' {
  MAKE_NODE(numListList);
  add_Node_Child_If_Not_Null($$, $1);
  add_Node_Child_If_Not_Null($$, $numList);
}
| %empty {
  $$ = NULL;
  // MAKE_NODE(numListList);
}

numList : numList ',' num {
  MAKE_NODE(numList);
  add_Node_Child_If_Not_Null($$, $1);
  add_Node_Child_If_Not_Null($$, $num);
}
| num {
  MAKE_NODE(numList);
  add_Node_Child_If_Not_Null($$, $num);
}


block : '{' localStmtList '}' {
  MAKE_NODE(block);
  add_Node_Child_If_Not_Null($$, $localStmtList);
}

declList : declList declOrdeclInitVar {
  MAKE_NODE(declList);
  add_Node_Child_If_Not_Null($$, $1);
  add_Node_Child_If_Not_Null($$, $declOrdeclInitVar);
}
| %empty {
  $$ = NULL;
}

expr : expr '+' expr {
  MAKE_NODE(expr); 
  $$->ival = '+'; 
  add_Node_Child_If_Not_Null($$, $1); 
  add_Node_Child_If_Not_Null($$, $3);  
}
| expr '-' expr {
  MAKE_NODE(expr); 
  $$->ival = '-'; 
  add_Node_Child_If_Not_Null($$, $1); 
  add_Node_Child_If_Not_Null($$, $3);  
}
| expr '*' expr {
  MAKE_NODE(expr); 
  $$->ival = '*'; 
  add_Node_Child_If_Not_Null($$, $1); 
  add_Node_Child_If_Not_Null($$, $3);  

}
| expr '/' expr {
  MAKE_NODE(expr); 
  $$->ival = '/'; 
  add_Node_Child_If_Not_Null($$, $1); 
  add_Node_Child_If_Not_Null($$, $3);  
}
| expr '%' expr {
  MAKE_NODE(expr); 
  $$->ival = '%'; 
  add_Node_Child_If_Not_Null($$, $1); 
  add_Node_Child_If_Not_Null($$, $3);    
}
| expr '@' expr {
  MAKE_NODE(expr); 
  $$->ival = '@'; 
  add_Node_Child_If_Not_Null($$, $1); 
  add_Node_Child_If_Not_Null($$, $3);    
}
| expr MAT_POW expr {
  MAKE_NODE(expr); 
  $$->ival = MAT_POW; 
  add_Node_Child_If_Not_Null($$, $1); 
  add_Node_Child_If_Not_Null($$, $3);    
}
| expr EQ expr {
  MAKE_NODE(expr); 
  $$->ival = EQ; 
  add_Node_Child_If_Not_Null($$, $1); 
  add_Node_Child_If_Not_Null($$, $3);  
}
| expr NEQ expr {
  MAKE_NODE(expr); 
  $$->ival = NEQ; 
  add_Node_Child_If_Not_Null($$, $1); 
  add_Node_Child_If_Not_Null($$, $3);  
}
| expr GE expr {
  MAKE_NODE(expr); 
  $$->ival = GE; 
  add_Node_Child_If_Not_Null($$, $1); 
  add_Node_Child_If_Not_Null($$, $3);  
}
| expr LE expr {
  MAKE_NODE(expr); 
  $$->ival = LE; 
  add_Node_Child_If_Not_Null($$, $1); 
  add_Node_Child_If_Not_Null($$, $3);  
}
| expr '>' expr {
  MAKE_NODE(expr); 
  $$->ival = '>'; 
  add_Node_Child_If_Not_Null($$, $1); 
  add_Node_Child_If_Not_Null($$, $3);    
}
| expr '<' expr {
  MAKE_NODE(expr); 
  $$->ival = '<'; 
  add_Node_Child_If_Not_Null($$, $1); 
  add_Node_Child_If_Not_Null($$, $3);    
}
| expr AND expr {
  MAKE_NODE(expr); 
  $$->ival = AND; 
  add_Node_Child_If_Not_Null($$, $1); 
  add_Node_Child_If_Not_Null($$, $3);  
}
| expr OR expr {
  MAKE_NODE(expr); 
  $$->ival = OR; 
  add_Node_Child_If_Not_Null($$, $1); 
  add_Node_Child_If_Not_Null($$, $3);  
}
| '!' expr {
  MAKE_NODE(expr);
  $$->ival = '!';
  add_Node_Child_If_Not_Null($$, $2);
}
| '&' expr {
  MAKE_NODE(expr);
  $$->ival = '&';
  add_Node_Child_If_Not_Null($$, $2);
}
| '(' expr ')' {
  MAKE_NODE(expr);
  add_Node_Child_If_Not_Null($$, $2);
}
| ICAST '(' expr ')' {
  MAKE_NODE(expr);
  add_Node_Child_If_Not_Null($$, Token_New("ICAST", "ICAST"));
  add_Node_Child_If_Not_Null($$, $3);
}
| FCAST '(' expr ')' {
  MAKE_NODE(expr);
  add_Node_Child_If_Not_Null($$, Token_New("FCAST", "FCAST"));
  add_Node_Child_If_Not_Null($$, $3);
}
| lvalue
| call 
| num 

call : ID '(' arglist ')' {
  MAKE_NODE(call);
  add_Node_Child_If_Not_Null($$, Token_New("ID", $ID));
  add_Node_Child_If_Not_Null($$, $arglist);
}
| ID '('  ')' {
  MAKE_NODE(call);
  add_Node_Child_If_Not_Null($$, Token_New("ID", $ID));
}

arglist : arglist ',' arg {
  MAKE_NODE(arglist);
  add_Node_Child_If_Not_Null($$, $1);
  add_Node_Child_If_Not_Null($$, $3);
}
| arg {
  MAKE_NODE(arglist);
  add_Node_Child_If_Not_Null($$, $1);
}

arg : lvalue {
  MAKE_NODE(arg);
  add_Node_Child_If_Not_Null($$, $lvalue);
}
| ID '(' expr ')' '(' expr ')' {
  MAKE_NODE(arg);
  add_Node_Child_If_Not_Null($$, Token_New("ID", $ID));
  add_Node_Child_If_Not_Null($$, $3);
  add_Node_Child_If_Not_Null($$, $6);
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
  // MAKE_NODE(lvalue);
  // add_Node_Child_If_Not_Null($$, Token_New("ID", $ID));
  $$ = Token_New("ID", $ID);
  free($ID), $ID = NULL;
}
| ID '[' expr ']' {
  MAKE_NODE(lvalue);
  add_Node_Child_If_Not_Null($$, Token_New("ID", $ID));
  add_Node_Child_If_Not_Null($$, $expr);
}
| ID '[' expr ']' '[' expr ']' {
  MAKE_NODE(lvalue);
  add_Node_Child_If_Not_Null($$, Token_New("ID", $ID));
  add_Node_Child_If_Not_Null($$, $3);
  add_Node_Child_If_Not_Null($$, $6);
}

rvalue : expr
| '{' numList '}' {$$ = $2;}
| '[' numListList ']' {$$ = $2;}

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