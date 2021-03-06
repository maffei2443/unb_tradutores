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
  {yyval.no = No_New(nodeCounter++);\
  if(!yyval.no) abort();\
  yyval.no->tname =  x  ;}
#define MAKE_NODE(x) INITNODE(STR(x))
// TODO: onde aparece setar variavel de erro!
#define PARAM_RPT_NAME_CHECK(__baseType, __id) \
  {if(!neoEntry) {\
    neoEntry = last_decl(&reshi, yyvsp[__id]._id);    \
    printf("[Semantico] Parametros de mesmo nome! Arvore vai ficar inconsistente..\n");\
    critical_error++;\
  }\
  else {\
    neoEntry->type = yyvsp[__baseType].type;\
    yyval.no->type = yyvsp[__baseType].type;\
    neoEntry->tag = TAG_PARAM;\
  }}
#include <string.h>
#define BLANK_INT "              "
#define BLANK_FLOAT "                           "
#define STUB 88
static int BLANK_FLOAT_SIZE = strlen(BLANK_FLOAT);
static int BLANK_INT_SIZE = strlen(BLANK_INT);

#include "Tree.h" // importante
#include "SemanticChecker.h"
#include "code_gen.h"
#include <stdio.h>
#include <stdlib.h>

extern int yylineno;
extern int currCol;
extern int numlines;
extern int yyleng;
extern int yylex();
void yyerror (char const *s);

extern void yylex_destroy();
// 
unsigned nodeCounter;

extern int gambs_tam;
extern int gambs_qtd;

extern unsigned long critical_error;
char* GLOBAL_SCOPE = "0global";

// Geracao de Codigo
extern short local_pos; // usado para variaveis locais
SymEntry* reshi;

char* currScope = NULL;
int check_signature = 0;
int declared_curr_fun = 0;
int check_parameters = 0;
int err = 0;
int aborta = 0;

int defFun_rule = 0;
int declFun_rule = 0;
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
%token BIN_OP
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
%type<ival> BIN_OP
%%

program : globalStmtList {
  $$ = $1;
  root = $$;
  printf("Derivacao foi concluida com root = %p.\n", $$);
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
}

globalStmt : defFun 
| declFun ';' 
| declOrdeclInitVar
| declFun error

declFun : AHEAD BASE_TYPE ID {
  declFun_rule = 1;
  SymEntry* tmp = last_decl(&reshi, $ID);
  if( !tmp ) {
    printf("DEVE ADICIONAR %s como declaracao de funcao\n", $ID);
    add_entry(&reshi, $ID, TAG_DECL_FUN, -1);
    err = 0;    
  }
  else {
    printf("[Semantico] |%s| nao pode ser declarado pois jah o foi em l.%d, c.%d\n", tmp->id, tmp->local.line, tmp->local.col);
    err = 1;
  }
  currScope = $ID;
} '(' paramListVoid ')' {
  MAKE_NODE(declFun);
  SymEntry* tmp;
  HASH_FIND_STR(reshi, $ID, tmp);

  if(!tmp) {
    printf("tmp is NULL! Erro logico incorrigivel.\n");
    abort();
  }
  tmp->tag = TAG_DECL_FUN;
  tmp->type = $BASE_TYPE;
  if(!err) {
    link_symentry_no(&tmp, &$$);
    err = 0;
  }
  
  add_Node_Child_If_Not_Null($$, Token_New("BASE_TYPE", type2string($BASE_TYPE)));
  add_Node_Child_If_Not_Null($$, Token_New(STR(ID), $ID));
  printf("[%s] pre-declarou-se!\n", $ID);
  
  add_Node_Child_If_Not_Null($$, $paramListVoid);
  $$->param = $paramListVoid; // Para rahpido acesso    
  free($ID), $ID = NULL;
  
  currScope = GLOBAL_SCOPE;
  declFun_rule = 0;
  err = 0;
}


typeAndNameSign : BASE_TYPE ID {
  SymEntry* oldEntry = last_decl(&reshi, $ID);
  printf("Recuperado da tabela de simbolos: %p\n", oldEntry);
  printf("base_type: %s", type2string($BASE_TYPE));
  char err = 0;
  if(oldEntry) {
    if( !strcmp(oldEntry->escopo, currScope) ) {
      printf("[Semantico] Erro: Redeclaracao de %s:%s!\n", oldEntry->escopo, oldEntry->id);
      err = 1;
    }
    else {
      printf("\tDeclaracoes sob escopos distintos.\n");
    }
  }

  if (!err) {
    SymEntry* neoEntry = add_entry(&reshi, $ID, TAG_UNDEFINED, local_pos++);
    if(neoEntry) {  //TODO: trtar esse caso
      neoEntry->type = $BASE_TYPE;
      MAKE_NODE(typeAndNameSign);
      printf("[typeAndNameSign] ALOCOU %p\n", $$);
      link_symentry_no(&neoEntry, &$$);      
      add_Node_Child_If_Not_Null($$, Token_New("BASE_TYPE", type2string($BASE_TYPE)));
      add_Node_Child_If_Not_Null($$, Token_New("ID", $ID));
    }
    else {
      printf("ERRO LOGICO: NAO DEVERIA ENTRAR AQUI! %s:%s ...\n", neoEntry->escopo, $ID);
    }
  }
  else {
    $$ = NULL;
  }
  free($ID);$ID = NULL;  
}

| BASE_TYPE ID '[' num ']' {
  // TODO: TESTAR!
  /// Checar:
  /// 1 - Se nao existe OU existe mas nao eh mesmo escopo, tah ok
  /// 2 - Se num eh inteiro, tah ok
  /// 3 - Soh entao cria-se o noh
  SymEntry* oldEntry = last_decl(&reshi, $ID);
  printf("Recuperado da tabela de simbolos: %p\n", oldEntry);
  
  char err = 0;
  if(oldEntry) {
    if( !strcmp(oldEntry->escopo, currScope) ) {
      printf("[Semantico] Erro: Redeclaracao de %s:%s!\n", oldEntry->escopo, oldEntry->id);
      err = 1;
    }
    else {
      printf("\tDeclaracoes sob escopos distintos.\n");
    }
  }

  if (!err) {
    if ($num->type != TYPE_INT) {
      printf("[Semantico] Erro: Tamanho de vetor deve ser um inteiro! Encontrado: %s\n", type2string($num->type));
      $$ = NULL;
    }  else if ($num->ival < 0) {
      printf("[Semantico] Erro: Tamanho deve ser >= 0\n");
    }  else {
      SymEntry* neoEntry = add_entry(&reshi, $ID, TAG_UNDEFINED, local_pos++);
      Type type = $BASE_TYPE == TYPE_FLOAT ? TYPE_ARRAY_FLOAT : TYPE_ARRAY_INT;
      if(neoEntry) {
        // TODO: checar se num eh inteiro. Se nao for, ERRO
        neoEntry->type = type;
        neoEntry->base_type = $BASE_TYPE;
        neoEntry->col = $num->ival;      
        MAKE_NODE(typeAndNameSign);
        link_symentry_no(&neoEntry, &$$);      
        add_Node_Child_If_Not_Null($$, Token_New("BASE_TYPE", type2string($BASE_TYPE)));
        add_Node_Child_If_Not_Null($$, Token_New("ID", $ID));
        add_Node_Child_If_Not_Null($$, $num);
      }
      else {
        printf("[BASE_TYPE ID '[' num ']'] ERRO LOGICO: NAO DEVERIA ENTRAR AQUI! %s:%s ...\n", neoEntry->escopo, $ID);
        $$ = NULL;
      }
    }
  }
  else {
    $$ = NULL;
  }

  if(!$$) {
    printf("  [Semantico] Nao adicionou (%s) aa tabela de simbolos (redeclaracao, tamanho nao inteiro, algo deu errado).\n", $ID);
  }
  free($ID);$ID = NULL;
}

| MAT_TYPE BASE_TYPE ID '[' num ']' '[' num ']' {
  // Procedimento analogo ao de cima,
  SymEntry* oldEntry = last_decl(&reshi, $ID);
  printf("Recuperado da tabela de simbolos: %p\n", oldEntry);
  
  char err = 0;
  if(oldEntry) {
    if( !strcmp(oldEntry->escopo, currScope) ) {
      printf("[Semantico] Erro: Redeclaracao de %s:%s!\n", oldEntry->escopo, oldEntry->id);
      err = 1;
    }
    else {
      printf("\tDeclaracoes sob escopos distintos.\n");
    }
  }

  if (!err) {
    char firstNum = $5->type != TYPE_INT;
    char secNum = $8->type != TYPE_INT;
    if(firstNum || secNum) {
      if(firstNum) {
        printf("[Semantico] ERRO[2]: Quantidade de linhas de matriz deve ser um inteiro. (%s encontrado)\n", type2string($5->type));
      }
      if(secNum) {
        printf("[Semantico] ERRO[2]: Quantidade de colunas de matriz deve ser um inteiro. (%s encontrado)\n", type2string($8->type));
      }
      $$ = NULL;
    }
    else {
      Type type = $BASE_TYPE == TYPE_FLOAT ? TYPE_MAT_FLOAT : TYPE_MAT_INT;
      SymEntry* neoEntry = add_entry(&reshi, $ID, TAG_UNDEFINED, local_pos++);
      if(neoEntry) {
        // TODO: checar se num eh inteiro. Se nao for, ERRO
        MAKE_NODE(typeAndNameSign);
        $$->type = type;
        link_symentry_no(&neoEntry, &$$);      
        add_Node_Child_If_Not_Null($$, Token_New("BASE_TYPE", type2string(type)));
        add_Node_Child_If_Not_Null($$, Token_New("ID", $ID));
        add_Node_Child_If_Not_Null($$, $5);
        add_Node_Child_If_Not_Null($$, $8);
        neoEntry->line = $5->ival;
        neoEntry->col = $8->ival;
        neoEntry->type = type;
      }
      else {
        printf("[BASE_TYPE ID '[' num ']'] ERRO LOGICO: NAO DEVERIA ENTRAR AQUI! %s:%s ...\n", neoEntry->escopo, $ID);
        $$ = NULL;
      }
    }
  }
  else {
    $$ = NULL;
  }
  if(!$$) {
    printf("\t[Semantico] Nao adicionou (%s) aa tabela de simbolos (redeclaracao, tamanho nao inteiro, algo deu errado).\n", $ID);
  }
  free($ID); $ID = NULL;
}


declOrdeclInitVar : typeAndNameSign ';'
| typeAndNameSign '=' rvalue ';' {
  if($1 == NULL || $3 == NULL) {
    $$ = NULL;
    printf("[Semantico] NAo foi possivel construir <declOrdeclInitVar> devido a erro semantico.\n");
  }
  else {
    MAKE_NODE(declOrdeclInitVar);
    add_Node_Child_If_Not_Null($$, $typeAndNameSign);
    add_Node_Child_If_Not_Null($$, $rvalue);
    Type class = Type_Class($1->type);
    printf("[type] %s\n", type2string($1->type));
    printf("[CLASS] %s\n", type2string(class));
    if( class == TYPE_MAT) {
      if ($rvalue->type != TYPE_LIST_LIST) {
        printf("[Semantico] Erro: inicializacao de matriz com %s\n", type2string($rvalue->type));
      }
    }

  }
}
| typeAndNameSign '=' rvalue error

paramListVoid : paramList {
  // childLast eh usado como auxiliar para criar a lista na ordem correta ;)
  $1->childLast = NULL;
  $$ = $1;
  printf("[paramListVoid] %p\n", $paramListVoid);
  printf("[paramListVoid->type] %s\n", type2string($paramListVoid->type));

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
| param 

param : BASE_TYPE {
  if(defFun_rule) {
    printf("[Semantico] ErroCritico: parametros em definicao de funcao precisam ser nomeados!\n");
    critical_error++;
  }
  $$ = Token_New(STR(param), type2string($BASE_TYPE));
  $$->type = $BASE_TYPE;
}
| MAT_TYPE BASE_TYPE {
  if(defFun_rule) {
    printf("[Semantico] ErroCritico: parametros em definicao de funcao precisam ser nomeados!\n");
    critical_error++;
  }  
  $$ = Token_New(STR(param), type2string($BASE_TYPE));
  $$->type = $BASE_TYPE == TYPE_INT ? TYPE_MAT_INT : TYPE_MAT_FLOAT;
}
| BASE_TYPE ID {
  if( defFun_rule ) {
    $$ = Token_New(STR(param), $ID );
    if(!declared_curr_fun) {
      // Associar temporario a parametro?
      SymEntry* neoEntry = add_entry(&reshi, $ID, TAG_PARAM, local_pos++);
      if(neoEntry) {
        neoEntry->type =  $BASE_TYPE;
        $$->type =  $BASE_TYPE;
        PARAM_RPT_NAME_CHECK(-1, 0);
        link_symentry_no(&neoEntry, &$$);
      }
    }
    else {
      printf("Funcao (%s) jah foi declarada/definida!\n", $ID);
    }
    $$->type = $BASE_TYPE;
  }
  else {  // eh declaracao; entao, nao precisa dos nomes. Simplesmente, ignore-o.
    $$ = Token_New(STR(param), type2string($BASE_TYPE) );
    $$->type = $BASE_TYPE;
  }
  free($ID), $ID = NULL;
}
| BASE_TYPE ID '[' ']' {
  if( defFun_rule ) {
    $$ = Token_New(STR(param), $ID);
    SymEntry* neoEntry = add_entry(&reshi, $ID, TAG_PARAM , local_pos++);
    // SEMANTICO

    PARAM_RPT_NAME_CHECK(-3, -2);
    
    if($BASE_TYPE == TYPE_INT)    neoEntry->type = TYPE_ARRAY_INT;
    else if ($BASE_TYPE == TYPE_FLOAT) neoEntry->type = TYPE_ARRAY_FLOAT;
    else {
      printf("BASE_TYPE deve ser apenas TYPE_INT ou TYPE_FLOAT\n");
      abort();
    }
    $$->type = neoEntry->type;
    if(neoEntry)
      link_symentry_no(&neoEntry, &$$);
  }
  else {
    $$ = Token_New(STR(param), type2string($BASE_TYPE == TYPE_INT ? TYPE_ARRAY_INT : TYPE_ARRAY_FLOAT) );
  }
  free($ID), $ID = NULL;
}

| MAT_TYPE BASE_TYPE ID {
  // TODO: checar por declaracao previa de parametro!
  if( defFun_rule ) {
    $$ = Token_New(STR(param), $ID);
    SymEntry* neoEntry = add_entry(&reshi, $ID, TAG_PARAM, local_pos++);
    // Semantico
    PARAM_RPT_NAME_CHECK(-1, 0);
    
    link_symentry_no(&neoEntry, &$$);  
    if($BASE_TYPE == TYPE_INT) neoEntry->type = TYPE_MAT_INT;  
    else if ($BASE_TYPE == TYPE_FLOAT) neoEntry->type = TYPE_MAT_FLOAT;
    else {
      printf("BASE_TYPE deve ser apenas TYPE_INT ou TYPE_FLOAT\n");
      abort();
    }
  }
  else {
    $$ = Token_New(STR(param), type2string($BASE_TYPE == TYPE_INT ? TYPE_MAT_INT : TYPE_MAT_FLOAT) );
  }
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
  // TODO: CHECAR TIPOS!
  MAKE_NODE(localStmt);
  if($lvalue->type != $rvalue->type ||
    $lvalue->type == $rvalue->type && $lvalue->type == TYPE_UNDEFINED) {
    printf("[Semantico] Warning de tipo em atribuicao: <%s> = <%s>\n", type2string($lvalue->type), type2string($rvalue->type));
  }
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
| RETURN expr error{$$=NULL;}
| IREAD '(' lvalue ')' ';' {
  MAKE_NODE(localStmt);
  No* iread_no = Token_New("IREAD","IREAD");
  add_Node_Child_If_Not_Null($$, iread_no);
  add_Node_Child_If_Not_Null($$, $lvalue);
  if($lvalue->type != TYPE_INT) {
    printf("[Semantico] Erro: Leitura de inteiro sobre tipo |%s|\n", type2string($lvalue->type));
  }
}
| FREAD '(' lvalue ')' ';' {
  MAKE_NODE(localStmt);
  No* fread_no = Token_New("FREAD","FREAD");
  add_Node_Child_If_Not_Null($$, fread_no);
  add_Node_Child_If_Not_Null($$, $lvalue);
  if($lvalue->type != TYPE_FLOAT) {
    printf("[Semantico] Erro: Leitura de inteiro sobre tipo |%s|\n", type2string($lvalue->type));
  }  
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
| IF '(' expr error block ELSE block {
  printf("Erro : IF ( expr error block ELSE block\n");
  printf("Falta FECHAR parentese\n");  
  $$ = NULL;
}
| IF error expr ')' block ELSE block {
  printf("Erro : IF ( expr error block ELSE block\n");
  printf("Falta ABRIR parentese\n");  
  $$ = NULL;  
}
| IF '(' error ')' block {
  printf("Erro : IF ( error ) block ELSE block\n");
  printf("Expressao mal formada\n");  
  $$ = NULL;  
}

loop : WHILE '(' expr ')' block {
  MAKE_NODE(loop);
  add_Node_Child_If_Not_Null($$, Token_New("WHILE","while"));
  add_Node_Child_If_Not_Null($$, $expr);
  add_Node_Child_If_Not_Null($$, $block);
}

defFun : BASE_TYPE ID '('{
  defFun_rule = 1;
  local_pos = 0;
  SymEntry* old = last_decl(&reshi, $ID);
  // CHECAGEM DE REDECLARACAO FEITA AQUI. 
  printf("lastDecl: (%p)\n", old);
  if(old) {
    if(old->tag == TAG_DEF_FUN) {
      printf("[defFun-Semantico] Erro: Funcao %s jah foi definida em l.%d, c.%d\n",
      old->id, old->local.line, old->local.col);
      aborta = 1;
    }
    else if(old->tag == TAG_DECL_FUN) {
      fprintf(stderr, "Funcao %s foi pre-declarada\n", old->id);      
      check_signature = 1;
      // declared_curr_fun = 1;
    }
    else {
      fprintf(stderr,"Jah tem variavel com esse (%s) nome :/\n", old->id);
      aborta = 1;
    }
  }
  else {
    printf("definindo funcao %s\n", $ID); fflush(stdout);
    SymEntry* neoEntry = add_entry(&reshi, $ID, TAG_DEF_FUN, -1);
    if(!neoEntry) {
      printf("Erro na definicao de funcao %s [bug]\n", $ID);
    }
    else {
      neoEntry->type = $BASE_TYPE;
      neoEntry->def_fun = 1;
    }
  }
  currScope = $ID;
} paramListVoid ')' '{' declList localStmtList '}' {
  if(!aborta) {
    if( check_signature ) {
      fprintf(stderr,"Checando assinatura de %s\n", $ID);
      currScope = GLOBAL_SCOPE;
      SymEntry* entry = last_decl(&reshi, $ID);
      // assert(entry != NULL);  // se der NULL, algo deu errado pois a funcao jah era pra estar na symTable
      if(entry) {
        if(entry->def_fun) {
          entry->tag = TAG_DEF_FUN;
          entry->def_fun = 1;
          mensagem_redeclaracao(entry);
          $$ = NULL;
        }
        else {

          int match = match_paramList(entry->astNode->param, $paramListVoid);
          if(match <= 0){
            printf("Lista de parametros de %s incompativel com sua declaracao!\n", $ID);
            critical_error++;
          }
        }
      }
      currScope = GLOBAL_SCOPE;
      check_signature = 0;
      declared_curr_fun = 0;
      defFun_rule = 0;
      // $$ = NULL;
    }
  }
  
  MAKE_NODE(defFun);

  SymEntry* tmp;
  HASH_FIND_STR(reshi, $ID, tmp);

  if (!aborta) {  // nao modificar a entrada jah existente da tabela de simbolos
    tmp->tag = TAG_DEF_FUN;
    tmp->type = $BASE_TYPE;
    $$->param = $paramListVoid;
    link_symentry_no(&tmp, &$$);
  }
  else
    aborta = 0;
  No* _BASE_TYPE = Token_New(STR(BASE_TYPE), type2string($BASE_TYPE));
  No* _ID = Token_New(STR(ID), $ID);
  add_Node_Child_If_Not_Null($$, _BASE_TYPE);
  add_Node_Child_If_Not_Null($$, _ID);
  add_Node_Child_If_Not_Null($$, $paramListVoid);
  add_Node_Child_If_Not_Null($$, $declList);
  add_Node_Child_If_Not_Null($$, $localStmtList);  
  
  currScope = GLOBAL_SCOPE;
  free($ID);$ID = NULL;
  defFun_rule = 0;
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
//  TODO: CHECAR TIPO EM TODOS OS CASOS
expr : expr '+' expr {
  MAKE_NODE(expr);
  $$->ival = '+';
  
  add_Node_Child_If_Not_Null($$, $1);
  add_Node_Child_If_Not_Null($$, $3);
  // SEMANTICO
  $$->type = bin_expr_type( $1->type, $3->type, '+');
  // GERACO DE CODIGO
  
  char buf[600];
  if($1->is_const == $3->is_const) {  // ambos constantes ou nao constantes
    if($1->is_const){

      switch ($1->type) {
        case TYPE_INT: sprintf(buf, "t%d = %d + %d\n", temp_next() , $1->ival, $3->ival); break;
        case TYPE_FLOAT: sprintf(buf, "t%d = %f + %f\n", temp_next() , $1->fval, $3->fval); break;
        default:break;
      }
    }
    else {
      // TODO: verificar se eh parametro, local ou global. Em cada caso deve
      // ser feito algo diferente:
      // - global: apenas sar o nome do identificador, pois nao hah clash
      // - parametro: verificar em qual local da pilha estah o parametro
      // - local: usar temporarios de algum jeito.
      //  + TODO: tratar esse caso
      printf("\t\vHEYHEYHEY!\n");
      sprintf(buf, "t%d = %s + %s\n", temp_next() , $1->child->sval, $3->child->sval);
    }
  }
  else {
    printf("TOUCA\n");
  }
  printf("TOPPer: %s\n", buf);
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
  printf("tipoResultante: %s\n", type2string($$->type));

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
  // TODO: RECLAMAR SE NAO "BOOL"
  $$->type = TYPE_INT;
  $$->ival = '!';
  add_Node_Child_If_Not_Null($$, $2);
}
| '&' expr {
  MAKE_NODE(expr);
  // CHECAR SE EH LVAL; SE NAO FOR, TEM QUE DAR ERRO
  if(strcmp($2->tname, "lvalue")) {
    printf("[Semantico] Erro: operando de & deve ser lvalue.\n");
  }
  $$->type = TYPE_POINTER;
  $$->ival = '&';
  add_Node_Child_If_Not_Null($$, $2);
}
| '(' expr ')' {$$ = $2;}
| ICAST '(' expr ')' {
  MAKE_NODE(expr);
  // TODO: checar se faz sentido a conversao
  $$->type = TYPE_INT;
  add_Node_Child_If_Not_Null($$, Token_New("ICAST", "ICAST"));
  add_Node_Child_If_Not_Null($$, $3);
  if(Type_Class($3->type) != TYPE_SCALAR) {
    printf("[Semantico] Erro: nao pode converter nao-escalar (e.g %s) para inteiro.\n",
      type2string($3->type));
  }
}
| FCAST '(' expr ')' {
  MAKE_NODE(expr);
  // TODO: checar se faz sentido a conversao
  $$->type = TYPE_FLOAT;  
  add_Node_Child_If_Not_Null($$, Token_New("FCAST", "FCAST"));
  add_Node_Child_If_Not_Null($$, $3);
  if(Type_Class($3->type) != TYPE_SCALAR) {
    printf("[Semantico] Erro: nao pode converter nao-escalar (e.g %s) para inteiro.\n",
      type2string($3->type));
  }  
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
  SymEntry* aux = last_decl(&reshi, $ID);
  if(!aux){
    printf("Funcao %s, l.%d c.%lu nao declarada!\n", $ID, numlines, currCol - (strlen($ID) + 2));
  }
  else{
    $$->type = aux->type;
    if(is_fun (aux->tag)) {
      printf("%s eh uma funcao!.\n", aux->id);
      printf("\t astNode: %p!.\n", aux->astNode);
      // Ver se assinatura bate com a declaracao!
      int match = match_paramList(aux->astNode->param, $argList);
      if(match > 0) 
        printf("[++++Semantico++++] Argumentos de %s corretos\n", $ID);
      else
        printf("[----Semantico----] Uso indevido de %s\n", $ID); 
    }
    else {
      printf("%s nao eh funcao para ser chamada\n", aux->id);
    }    
  }
  free($ID); $ID = NULL;
}
| ID '('  ')' {
  MAKE_NODE(call);
  add_Node_Child_If_Not_Null($$, Token_New("ID", $ID));
  // SEMANTICO  
  SymEntry* aux = last_decl(&reshi, $ID);
  if(!aux){
    printf("Funcao %s, l.%d c.%lu nao declarada!\n", $ID, numlines, currCol - (strlen($ID) + 2));
  }
  else{
    $$->type = aux->type;
    if(is_fun (aux->tag)) {
      printf("%s eh uma funcao!.\n", aux->id);
      printf("\t astNode: %p!.\n", aux->astNode);
      // Ver se assinatura bate com a declaracao!
      int match = match_paramList(aux->astNode->param, NULL);
      if(match > 0) 
        printf("[++++Semantico++++] Argumentos de %s corretos\n", $ID);
      else
        printf("[----Semantico----] Uso indevido de %s\n", $ID);
      
    }
    else {
      printf("%s nao eh funcao para ser chamada\n", aux->id);
    }    
  }
  free($ID); $ID = NULL;
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

arg : lvalue 
| ID '(' expr ')' '(' expr ')' {
  MAKE_NODE(arg);
  add_Node_Child_If_Not_Null($$, Token_New("ID", $ID));
  add_Node_Child_If_Not_Null($$, $3);
  add_Node_Child_If_Not_Null($$, $6);
  // SEMANTICO    
  SymEntry* entry = last_decl(&reshi, $ID);
  if(!entry) {  // var na odeclarada
    printf("[Semantico] Erro: Variavel %s, l.%d nao declarada\n", $ID, numlines);    
  }
  else {
    if(is_fun(entry->tag)) {
      printf("[Semantico] Erro: Uso inadequado de funcao %s, l.%d\n", $ID, numlines);
    }
    else if(Type_Class(entry->type) != TYPE_MAT ) {
      printf("[Semantico] Erro: Variavel %s, l.%d nao eh matriz\n", $ID, numlines);    
    }
    else {
      $$->type = entry->type;
      printf("argType: %s\n", type2string($$->type));
      // TODO: checar dimensoes, mas isso eh em tempo de excucao
    }
  }
  free($ID); $ID = NULL;
}

num : V_INT {
  MAKE_NODE(num);
  $$->ival = $V_INT;
  // SEMANTICO
  $$->is_const = 1;
  $$->type = TYPE_INT;
  // Code generation
  char buf[20];
  sprintf(buf, "%d", $1);  
  // $$->code = Code_New(buf);
}
| V_FLOAT {
  MAKE_NODE(num);
  $$->fval = $V_FLOAT;
  // SEMANTICO
  $$->is_const = 1;
  $$->type = TYPE_FLOAT;
}


lvalue : ID {
  MAKE_NODE(lvalue);
  No* tok = Token_New("ID", $ID);
  SymEntry* entry = last_decl(&reshi,$ID);
  if(!entry)  abort();
  $$->type = entry->type;
  // $$->base_type = entry->base_type;
  add_Node_Child_If_Not_Null($$, tok);
  // SEMANTICO
  SymEntry* old = last_decl(&reshi, $ID);
  // CHECK FOR NULL (== nao declarado)
  // printf("[ID: %s]old->type: %s\n", $ID, type2string(old->type));
  if(old) {
    if(is_fun(old->tag)) {
      printf("Identificador %s, l.%d c.%lu DECLARADO PREVIAMENTE como funcao em l.%d, c.%d!\n",
       $ID, numlines, currCol - (strlen($ID) + 2), old->local.line, old->local.col);
    }
    else {
      SET_TYPE_AND_UNI_LINK(old, tok)
    }
  }
  else {
    $$->type = TYPE_UNDEFINED;
    printf("Variavel %s, l.%d c.%lu nao declarada!\n", $ID, numlines, currCol - (strlen($ID) + 2));
  }
  // printf("lvalue->type=%s \n", type2string( $$->type ));
  free($ID), $ID = NULL;
}
| ID '[' expr ']' {
  // TODO: CHECAR SE ID EH MATRIZ ou ARRAY. Senao, erro.
  // TODO: INDEXACAO SOH SE TIPO FOR INTEIRO!
  MAKE_NODE(lvalue);
  No* tok = Token_New("ID", $ID);

  add_Node_Child_If_Not_Null($$, tok);
  add_Node_Child_If_Not_Null($$, $expr);
  
  // SEMANTICO
  SymEntry* old = last_decl(&reshi, $ID);
  if(!old){
    printf("Variavel %s, l.%d nao declarada!\n", $ID, numlines);
  }
  else {
    if(old->col == -1) {
      printf("[Semantico] Erro: %s nao eh indexavel!\n",  old->id);
    }
    else {
      set_type_and_uni_link($$, old, tok);
    }
  }
  free($ID); $ID = NULL;
}
| ID '[' expr ']' '[' expr ']' {
  // TODO: CHECAR SE ID EH MATRIZ. Senao, erro.
  // TODO: INDEXACAO SOH SE TIPO FOR INTEIRO!
  MAKE_NODE(lvalue);
  No* tok = Token_New("ID", $ID);

  add_Node_Child_If_Not_Null($$, tok);
  add_Node_Child_If_Not_Null($$, $3);
  add_Node_Child_If_Not_Null($$, $6);
  // SEMANTICO    
  SymEntry* old = last_decl(&reshi, $ID);
  if(!old){
    printf("Variavel %s, l.%d nao declarada!\n", $ID, numlines);
  } else if(old->type != TYPE_MAT) {
    printf("[Semantico] Variavel (%s:%s) nao eh matriz para ser indexada duplamente!\n", old->escopo, old->id);
  } else {
    set_type_and_uni_link($$, old, tok);
  }
  
  free($ID); $ID = NULL;
}

rvalue : expr
| '{' numList '}' {
  $$ = $2;
  $$->type = TYPE_LIST;
}
| '{' numListList '}' {
  $$ = $2;
  $$->type = TYPE_LIST_LIST;
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
  // char* a = "a";
  // for(int x = 0; x < 4; x++) {
  //   free(widen(a, TYPE_INT, TYPE_FLOAT));
  // }
  // return 9;
  yyparse();
  if(root) {
    show_Sub_Tree(root, 1, SVAL);
    show_Lis(root,SVAL);
  }
  print_reshi(reshi);
  yylex_destroy();
  
  free_All_Child(root);
  // free_Lis(root);
  // delGambs();
  delete_all(reshi);
  temp_next();
}