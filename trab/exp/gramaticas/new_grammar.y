%code requires {
  #include "Tree.h"
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
  yyval.no = No_New(nodeCounter++);\
  if(!yyval.no) abort();\
  yyval.no->tname =  x  ;
#define MAKE_NODE(x) INITNODE(STR(x))
#include "Tree.h" // importante
#include "SemanticChecker.h"
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
// 
Type bin_expr_type(Type left, Type right, int op);
unsigned nodeCounter;

static int gambs_tam = 0;
static int gambs_qtd = 0;
char* GLOBAL_SCOPE = "0global";

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
  for(int i = 0;i < gambs_qtd;i++){
    printf("id: %s\n", (gambs[i])->id);
    SymEntry_Destroy(gambs[i]);
    gambs[i] = NULL;
  }
  free(gambs);
}


SymEntry* add_entry(SymEntry** reshi, char* id, int tag) {
    SymEntry* newEntry = NULL;
    HASH_FIND_STR((*reshi), id, newEntry);/* id already in the hash? */
    if (newEntry == NULL) {
      newEntry = SymEntry_New(id, tag, currScope);
      newEntry->local.line = numlines;
      newEntry->local.col = currCol;
      HASH_ADD_STR( (*reshi), id, newEntry );/* id: name of key field */
      addToDel(&newEntry);
    }
    else {    // Checar se eh declaracao no msm escopo. Se for, nao adiciona e dah pau (retorna NULL);
      printf("Possivel conflito com %s:%s\n", id, newEntry->escopo);
      for(;newEntry->next;newEntry = newEntry->next) {
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

// Retorna NULL caso nao o tenha sido;senao,
// retorna ponteiro para declracao mais prohxima.


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
    for(s=reshi;s != NULL;s = nexti) {
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
%right '@'
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
%type<no> numList block declList expr call argList 
%type<no> arg rvalue lvalue num typeAndNameSign

%type<_id> ID 
%type<type> BASE_TYPE
%type<ival> V_INT
%type<cval> V_ASCII
%type<fval> V_FLOAT
%%

program : globalStmtList {
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
  if(! was_declared(&reshi, $ID) ) {
    SymEntry* neoEntry = add_entry(&reshi, $ID, HFUN);
    neoEntry->tag = $BASE_TYPE;
  }
  else {
    // TODO: CHECAR SE EXISTE BATEM OS PARAMETROS!
  }
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
  // TODO: checar se funcao foi declarado e a QUANTIDADE DE PARAMETROS!.
  // E os TIPOS de parametros


}


typeAndNameSign : BASE_TYPE ID {
  SymEntry* neoEntry = add_entry(&reshi, $ID, $BASE_TYPE);

  // printf("[typeAndNameSign] BASE_TYPE *ID* \n");
  MAKE_NODE(typeAndNameSign);
  $$->ival = 0;
  printf(" >>>>>> %s\n", type2string($BASE_TYPE));
  printf(" ------ %s\n", $ID);
  
  add_Node_Child_If_Not_Null($$, Token_New("BASE_TYPE", type2string($BASE_TYPE)));
  add_Node_Child_If_Not_Null($$, Token_New("ID", $ID));
  free($ID);$ID = NULL;
}
| BASE_TYPE ID '[' num ']' {
  SymEntry* neoEntry = add_entry(&reshi, $ID, $BASE_TYPE);

  MAKE_NODE(typeAndNameSign);
  $$->ival = 1;
  add_Node_Child_If_Not_Null($$, Token_New("BASE_TYPE", type2string($BASE_TYPE)));
  add_Node_Child_If_Not_Null($$, Token_New("ID", $ID));
  // SEMANTICO!
  if($num->type == TYPE_FLOAT) {
    printf("[Semantico] ERRO: Indexacao soh pode ser feita com indices inteiros. (%f encontrado)\n", $num->fval);
  }
  add_Node_Child_If_Not_Null($$, $num);
  free($ID);$ID = NULL;
  // $$->childLast->ival = $V_INT;

}
| MAT_TYPE BASE_TYPE ID '[' num ']' '[' num ']'{
  MAKE_NODE(typeAndNameSign);
  $$->ival = 1;
  add_Node_Child_If_Not_Null($$, Token_New("MAT_TYPE", "mat"));
  if($5->type == TYPE_FLOAT) {
    printf("[Semantico] ERRO: Indexacao soh pode ser feita com indices inteiros. (%f encontrado)\n", $5->fval);
  }
  if($8->type == TYPE_FLOAT) {
    printf("[Semantico] ERRO: Indexacao soh pode ser feita com indices inteiros. (%f encontrado)\n", $8->fval);
  }

  add_Node_Child_If_Not_Null($$, Token_New("BASE_TYPE", type2string($BASE_TYPE)));
  add_Node_Child_If_Not_Null($$, Token_New("ID", $ID));
  add_Node_Child_If_Not_Null($$, $5);
  add_Node_Child_If_Not_Null($$, $8);  
}

declOrdeclInitVar : typeAndNameSign ';'
| typeAndNameSign '=' rvalue ';' {
  MAKE_NODE(declOrdeclInitVar);
  add_Node_Child_If_Not_Null($$, $typeAndNameSign);
  add_Node_Child_If_Not_Null($$, $rvalue);
}

paramListVoid : paramList {
  // Usado como auxiliar para criar a lista na ordem correta.
  $1->childLast = NULL;
  $$ = $1;
}
| %empty {$$ = NULL;}

paramList : paramList ',' param {
  // Para mantes a ordem correta dos parametros
  if(!$1->hasAux) {
    $1->hasAux = 1;
    $1->nextAux = $param;
    $1->childLast = $param;
  }
  else {
    $1->childLast->nextAux = $param;
    $1->childLast = $param;
  }
  $$ = $1;
}
| param {
  $$ = $1;
  $$->hasAux = 0;
}

param : BASE_TYPE ID {
  $$ = Token_New(STR(param), $ID);
  SymEntry* neoEntry = add_entry(&reshi, $ID, HID);
  neoEntry->type = $BASE_TYPE;
  $$->type = $BASE_TYPE;
  $param->symEntry = neoEntry;
  // $$->ival = 0;
  // add_Node_Child_If_Not_Null($$, Token_New("BASE_TYPE", type2string($BASE_TYPE)));
  // add_Node_Child_If_Not_Null($$, Token_New("ID",$ID));
  
  if(was_declared(&reshi, $ID))
    printf("%s foi declarado\n", $ID);
  else
    printf("%s NAO FOI declarado\n", $ID);
  
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
  $$->type = $BASE_TYPE;
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
  $$->type = neoEntry->type;
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
| PRINT '(' rvalue ')' ';' {
  MAKE_NODE(localStmt);
  No* print_no = Token_New("PRINT","PRINT");
  add_Node_Child_If_Not_Null($$, print_no);
  add_Node_Child_If_Not_Null($$, $rvalue);
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
  // Nao faz mal, mas nao eh util!
  $$ = NULL;
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
  neoEntry->type = $BASE_TYPE;
  currScope = $ID;
} paramListVoid ')' '{' declList localStmtList '}' {
  SymEntry* tmp;
  HASH_FIND_STR(reshi, $ID, tmp);
  tmp->tag = HFUN;
  tmp->type = $BASE_TYPE;
  MAKE_NODE(defFun);
  No* _BASE_TYPE = Token_New(STR(BASE_TYPE), type2string($BASE_TYPE));
  No* _ID = Token_New(STR(ID), $ID);
  free($ID);$ID = NULL;
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
  // SEMANTICO
  $$->type = bin_expr_type( $1->type, $3->type, '+');
}
| expr '-' expr {
  MAKE_NODE(expr);
  $$->ival = '-';
  add_Node_Child_If_Not_Null($$, $1);
  add_Node_Child_If_Not_Null($$, $3);
  // SEMANTICO
  $$->type = bin_expr_type( $1->type, $3->type, '-');
}
| expr '*' expr {
  MAKE_NODE(expr);
  $$->ival = '*';
  add_Node_Child_If_Not_Null($$, $1);
  add_Node_Child_If_Not_Null($$, $3);
  // SEMANTICO
  $$->type = bin_expr_type( $1->type, $3->type, '*');

}
| expr '/' expr {
  MAKE_NODE(expr);
  $$->ival = '/';
  add_Node_Child_If_Not_Null($$, $1);
  add_Node_Child_If_Not_Null($$, $3);
  // SEMANTICO
  $$->type = bin_expr_type( $1->type, $3->type, '/');
}
| expr '%' expr {
  MAKE_NODE(expr);
  $$->ival = '%';
  add_Node_Child_If_Not_Null($$, $1);
  add_Node_Child_If_Not_Null($$, $3);
  // SEMANTICO
  $$->type = bin_expr_type( $1->type, $3->type, '%');
}
| expr '@' expr {
  MAKE_NODE(expr);
  $$->ival = '@';
  add_Node_Child_If_Not_Null($$, $1);
  add_Node_Child_If_Not_Null($$, $3);
  // SEMANTICO
  $$->type = bin_expr_type( $1->type, $3->type, '@');
}
| expr MAT_POW expr {
  MAKE_NODE(expr);
  $$->ival = MAT_POW;
  add_Node_Child_If_Not_Null($$, $1);
  add_Node_Child_If_Not_Null($$, $3);
  // SEMANTICO
  $$->type = bin_expr_type( $1->type, $3->type, MAT_POW);
}
| expr EQ expr {
  MAKE_NODE(expr);
  $$->ival = EQ;
  add_Node_Child_If_Not_Null($$, $1);
  add_Node_Child_If_Not_Null($$, $3);
  // SEMANTICO
  $$->type = bin_expr_type( $1->type, $3->type, EQ);
}
| expr NEQ expr {
  MAKE_NODE(expr);
  $$->ival = NEQ;
  add_Node_Child_If_Not_Null($$, $1);
  add_Node_Child_If_Not_Null($$, $3);
  // SEMANTICO
  $$->type = bin_expr_type( $1->type, $3->type, NEQ);
}
| expr GE expr {
  MAKE_NODE(expr);
  $$->ival = GE;
  add_Node_Child_If_Not_Null($$, $1);
  add_Node_Child_If_Not_Null($$, $3);
  // SEMANTICO
  $$->type = bin_expr_type( $1->type, $3->type, GE);
}
| expr LE expr {
  MAKE_NODE(expr);
  $$->ival = LE;
  add_Node_Child_If_Not_Null($$, $1);
  add_Node_Child_If_Not_Null($$, $3);
  // SEMANTICO
  $$->type = bin_expr_type( $1->type, $3->type, LE);
}
| expr '>' expr {
  MAKE_NODE(expr);
  $$->ival = '>';
  add_Node_Child_If_Not_Null($$, $1);
  add_Node_Child_If_Not_Null($$, $3);
  // SEMANTICO
  $$->type = bin_expr_type( $1->type, $3->type, '>');
}
| expr '<' expr {
  MAKE_NODE(expr);
  $$->ival = '<';
  add_Node_Child_If_Not_Null($$, $1);
  add_Node_Child_If_Not_Null($$, $3);
  // SEMANTICO
  $$->type = bin_expr_type( $1->type, $3->type, '<');
}
| expr AND expr {
  MAKE_NODE(expr);
  $$->ival = AND;
  add_Node_Child_If_Not_Null($$, $1);
  add_Node_Child_If_Not_Null($$, $3);
  // SEMANTICO
  $$->type = bin_expr_type( $1->type, $3->type, AND);
}
| expr OR expr {
  MAKE_NODE(expr);
  $$->ival = OR;
  add_Node_Child_If_Not_Null($$, $1);
  add_Node_Child_If_Not_Null($$, $3);
  // SEMANTICO
  $$->type = bin_expr_type( $1->type, $3->type, OR);
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

call : ID '(' argList ')' {
  MAKE_NODE(call);
  add_Node_Child_If_Not_Null($$, Token_New("ID", $ID));
  add_Node_Child_If_Not_Null($$, $argList);
  // SEMANTICO  
  // TODO: checar se ID eh mesmo funcao. Depois, checar os PARAMETROS, ver se os tipos batem
  SymEntry* aux = was_declared(&reshi, $ID);
  if(!aux){
    printf("Funcao %s, l.%d c.%lu nao declarada!\n", $ID, numlines, currCol - (strlen($ID) + 2));
  }
  else {
    if(aux->tag != HFUN) {
      printf("%s nao eh uma funcao.\n", aux->id);
    }
  }
}
| ID '('  ')' {
  MAKE_NODE(call);
  add_Node_Child_If_Not_Null($$, Token_New("ID", $ID));
  // SEMANTICO  
  SymEntry* aux = was_declared(&reshi, $ID);
  if(!aux){
    printf("Funcao %s, l.%d c.%lu nao declarada!\n", $ID, numlines, currCol - (strlen($ID) + 2));
  }
  else {
    if(aux->tag != HFUN) {
      printf("%s nao eh uma funcao.\n", aux->id);
    }
  }
}

argList : argList ',' arg {
  // Mesmo esquema da lista de parametros
  if(!$1->hasAux) {
    $1->hasAux = 1;
    $1->nextAux = $arg;
    $1->childLast = $arg;
  }
  else {
    $1->childLast->nextAux = $arg;
    $1->childLast = $arg;
  }
  $$ = $1;
}
| arg 

arg : lvalue {
  MAKE_NODE(arg);
  add_Node_Child_If_Not_Null($$, $lvalue);
}
| ID '(' expr ')' '(' expr ')' {
  MAKE_NODE(arg);
  add_Node_Child_If_Not_Null($$, Token_New("ID", $ID));
  add_Node_Child_If_Not_Null($$, $3);
  add_Node_Child_If_Not_Null($$, $6);
  // SEMANTICO    
  if(!was_declared(&reshi, $ID)){printf("Variavel %s, l.%d\n", $ID, numlines);}

}

num : V_INT {
  MAKE_NODE(num);
  $$->ival = $V_INT;
  // SEMANTICO
  $$->is_const = 1;
  $$->type = TYPE_INT;
}
| V_FLOAT {
  MAKE_NODE(num);
  $$->fval = $V_FLOAT;
  // SEMANTICO
  $$->is_const = 1;
  $$->type = TYPE_FLOAT;
}


lvalue : ID {
  // MAKE_NODE(lvalue);
  // add_Node_Child_If_Not_Null($$, Token_New("ID", $ID));
  $$ = Token_New("ID", $ID);
  // SEMANTICO    
  SymEntry* entry = was_declared(&reshi, $ID);
  if(entry) {
    if(entry->tag == HFUN ) {
      printf("Identificador %s, l.%d c.%lu DECLARADO PREVIAMENTE como funcao em l.%d, c.%d!\n",
       $ID, numlines, currCol - (strlen($ID) + 2), entry->local.line, entry->local.col);
    }
  }
  else {
    printf("Variavel %s, l.%d c.%lu nao declarada!\n", $ID, numlines, currCol - (strlen($ID) + 2));
  }

  free($ID), $ID = NULL;
}
| ID '[' expr ']' {
  MAKE_NODE(lvalue);
  add_Node_Child_If_Not_Null($$, Token_New("ID", $ID));
  add_Node_Child_If_Not_Null($$, $expr);
  // SEMANTICO    
  if(!was_declared(&reshi, $ID)){printf("Variavel %s, l.%d nao declarada!\n", $ID, numlines);}
}
| ID '[' expr ']' '[' expr ']' {
  MAKE_NODE(lvalue);
  add_Node_Child_If_Not_Null($$, Token_New("ID", $ID));
  add_Node_Child_If_Not_Null($$, $3);
  add_Node_Child_If_Not_Null($$, $6);
  // SEMANTICO    
  if(!was_declared(&reshi, $ID)){printf("Variavel %s, l.%d nao declarada!\n", $ID, numlines);}
}

rvalue : expr
| '{' numList '}' {$$ = $2;}
| '[' numListList ']' {$$ = $2;}

%%
//  Retorna TYPE_UNDEFINED nos casos:
// - left/right ser TYPE_UNDEFINED
// - left/right ser TYPE_VOID
// - left/right ser TYPE_ARRAY
// - expressão mal formada como por exemplo divisão de 
// escalar por matriz
Type bin_expr_type(Type left, Type right, int op) {
  Type leftClass = Type_Class(left);
  Type rightClass = Type_Class(right);
  if(left == TYPE_UNDEFINED || right == TYPE_UNDEFINED) return TYPE_UNDEFINED;// erro de inicializacao...
  else if(left == TYPE_VOID || right == TYPE_VOID ) return TYPE_VOID;// tentando usar retorno de funcao VOID
  else if(leftClass == TYPE_ARRAY || rightClass == TYPE_ARRAY) return TYPE_UNDEFINED;
  // NAO SE PODE OPERAR SOBRE ARRAYS.
 
  switch (op)  {
    case '+': case '-':
      if(leftClass == rightClass) max(left, right);
      else if(left == TYPE_MAT && right == TYPE_SCALAR) return left;
      else return TYPE_UNDEFINED;
    case '*':
      if(leftClass == rightClass) max(left, right);
      else if(left == TYPE_SCALAR && right == TYPE_MAT) return left;
      else return TYPE_UNDEFINED;
    case '/':
      if(leftClass == rightClass) max(left, right);
      else if(left == TYPE_MAT && right ==  TYPE_SCALAR ) return left;
      else return TYPE_UNDEFINED;
    case '@':
      if(leftClass == TYPE_MAT && rightClass == TYPE_MAT) return max(left, right);
      else return TYPE_UNDEFINED;
      /* code */
    case MAT_POW:
      if((left == TYPE_MAT_INT || left == TYPE_MAT_FLOAT)
        && (right == TYPE_INT || right == TYPE_FLOAT)) {
        return left == TYPE_MAT_INT ? TYPE_MAT_INT : TYPE_MAT_FLOAT;
      }
      else
        return TYPE_UNDEFINED;

    case EQ:  case NEQ:
    case GE:  case LE:
    case '<':  case '>':
    case AND:  case OR:
      return TYPE_INT;
    default: 
      return TYPE_UNDEFINED;
  }
}


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
  free(gambs);gambs = NULL;
  free_All_Child(root);
  free_Lis(root);
}