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
#define PARAM_RPT_NAME_CHECK(__baseType, __id) \
  if(!neoEntry) {\
    neoEntry = last_decl(&reshi, yyvsp[__id]._id);    \
    printf("[Semantico] Parametros de mesmo nome! Arvore vai ficar inconsistente..\n");\
  }\
  else {\
    neoEntry->type = yyvsp[__baseType].type;\
    yyval.no->type = yyvsp[__baseType].type;\
    neoEntry->tag = TYPE_PARAM;\
  }

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

extern void yylex_destroy();
// 
unsigned nodeCounter;

extern int gambs_tam;
extern int gambs_qtd;
char* GLOBAL_SCOPE = "0global";

SymEntry* reshi;

char* currScope = NULL;
int check_signature = 0;
int decl_fun_rule = 0;
int def_fun_rule = 0;
int declared_curr_fun = 0;
int check_parameters = 0;
int err = 0;
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
}

globalStmt : defFun 
| declFun ';' 
| declOrdeclInitVar

declFun : AHEAD BASE_TYPE ID {
  decl_fun_rule = 1;
  SymEntry* tmp = last_decl(&reshi, $ID);
  if( !tmp ) {
    printf("DEVE ADICIONAR %s como declaracao de funcao\n", $ID);
    add_entry(&reshi, $ID, TYPE_DECL_FUN);
    err = 0;    
  }
  else {
    printf("[Semantico] |%s| nao pode ser declarado pois jah o foi em l.%d, c.%d\n", tmp->id, tmp->local.line, tmp->local.col);
  }
  currScope = $ID;
} '(' paramListVoid ')' {
  MAKE_NODE(declFun);
  SymEntry* tmp;
  HASH_FIND_STR(reshi, $ID, tmp);

  if(!tmp) {
    printf("tmp is NULL\n");
  }
  else if(!err) {
    link_symentry_no(&tmp, &$$);
    err = 0;
  }
  if(tmp) {
    tmp->tag = TYPE_DECL_FUN;
    tmp->type = $BASE_TYPE;
  }
  
  add_Node_Child_If_Not_Null($$, Token_New("BASE_TYPE", type2string($BASE_TYPE)));
  add_Node_Child_If_Not_Null($$, Token_New(STR(ID), $ID));
  printf("[%s] pre-declarou-se!\n", $ID);
  add_Node_Child_If_Not_Null($$, $paramListVoid);
  
  $$->param = $paramListVoid;
  link_symentry_no(&tmp, &$declFun);
  // if ($$->param) {
  //   printf("primeiro parametro de %s: %s\n", $ID, $$->param->sval);
  // }
  free($ID), $ID = NULL;
  currScope = GLOBAL_SCOPE;
  decl_fun_rule = 0;
}


typeAndNameSign : BASE_TYPE ID {
  SymEntry* oldEntry = last_decl(&reshi, $ID);
  printf("Recuperado da tabela de simbolos: %p\n", oldEntry);
  if(oldEntry) {
    if( !strcmp(oldEntry->escopo, currScope) ) {
      printf("[Semantico]\n");
    }
    else {
      printf("\tDeclaracoes sob escopos distintos.\n");
    }
  }

  SymEntry* neoEntry = add_entry(&reshi, $ID, $BASE_TYPE);
  neoEntry->type = neoEntry->tag;
  // printf("[typeAndNameSign : BASE_TYPE ID] neoEntry->tag: %s\n", type2string(neoEntry->tag));
  // printf("[typeAndNameSign : BASE_TYPE ID] neoEntry->type: %s\n", type2string(neoEntry->type));
  MAKE_NODE(typeAndNameSign);
  link_symentry_no(&neoEntry, &$$);
  
  add_Node_Child_If_Not_Null($$, Token_New("BASE_TYPE", type2string($BASE_TYPE)));
  add_Node_Child_If_Not_Null($$, Token_New("ID", $ID));
  free($ID);$ID = NULL;
}

| BASE_TYPE ID '[' num ']' {
  SymEntry* neoEntry = add_entry(&reshi, $ID, $BASE_TYPE == TYPE_INT ? TYPE_ARRAY_INT : TYPE_ARRAY_FLOAT);
  neoEntry->type = neoEntry->tag;
  MAKE_NODE(typeAndNameSign);
  link_symentry_no(&neoEntry, &$$);

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
| MAT_TYPE BASE_TYPE ID '[' num ']' '[' num ']' {
  SymEntry* neoEntry = add_entry(&reshi, $ID, $BASE_TYPE == TYPE_INT ? TYPE_MAT_INT : TYPE_MAT_FLOAT);
  neoEntry->type = neoEntry->tag;
  MAKE_NODE(typeAndNameSign);
  link_symentry_no(&neoEntry, &$$);

  MAKE_NODE(typeAndNameSign);
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

declOrdeclInitVar : typeAndNameSign ';' {}
| typeAndNameSign '=' rvalue ';' {
  MAKE_NODE(declOrdeclInitVar);
  add_Node_Child_If_Not_Null($$, $typeAndNameSign);
  add_Node_Child_If_Not_Null($$, $rvalue);
}

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

param : BASE_TYPE ID {
  $$ = Token_New(STR(param), $ID);
  SymEntry* funEntry = last_decl(&reshi, $ID);
  printf("!!! %p, %s: param @@@\n", funEntry, $ID);
  if(!declared_curr_fun) {
    SymEntry* neoEntry = add_entry(&reshi, $ID, TYPE_PARAM);
    if(neoEntry) {
      neoEntry->type =  $BASE_TYPE;
      $$->type =  $BASE_TYPE;
      PARAM_RPT_NAME_CHECK(-1, 0);
      link_symentry_no(&neoEntry, &$$);
    }
  }
  else {
    printf("1296 !!!\n");
  }
  $$->type = $BASE_TYPE;
  free($ID), $ID = NULL;
}
| BASE_TYPE ID '[' ']' {
  $$ = Token_New(STR(param), $ID);
  SymEntry* neoEntry = add_entry(&reshi, $ID, TYPE_PARAM );
  // SEMANTICO
  PARAM_RPT_NAME_CHECK(-3, -2);
  
  if($BASE_TYPE == TYPE_INT)    neoEntry->type = TYPE_MAT_INT;
  else if ($BASE_TYPE == TYPE_FLOAT) neoEntry->type = TYPE_ARRAY_FLOAT;
  else {
    printf("BASE_TYPE deve ser apenas TYPE_INT ou TYPE_FLOAT\n");
    abort();
  }
  $$->type = $BASE_TYPE;
  link_symentry_no(&neoEntry, &$$);
  free($ID), $ID = NULL;
}

| MAT_TYPE BASE_TYPE ID {
  $param = Token_New(STR(param), $ID);
  SymEntry* neoEntry = add_entry(&reshi, $ID, TYPE_PARAM);
  // Semantico
  PARAM_RPT_NAME_CHECK(-1, 0);

  if($BASE_TYPE == TYPE_INT) neoEntry->type = TYPE_MAT_INT;  
  else if ($BASE_TYPE == TYPE_FLOAT) neoEntry->type = TYPE_MAT_FLOAT;
  else {
    printf("BASE_TYPE deve ser apenas TYPE_INT ou TYPE_FLOAT\n");
    abort();
  }
  if(neoEntry)
    link_symentry_no(&neoEntry, &$$);  
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
  if($lvalue->type != $rvalue->type ||
    $lvalue->type == $rvalue->type && $lvalue->type == TYPE_UNDEFINED) {
    printf("[Semantico] Erro de tipo em atribuicao: <%s> = <%s>\n", type2string($lvalue->type), type2string($rvalue->type));
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
  def_fun_rule = 1;
  SymEntry* old = last_decl(&reshi, $ID);
  // CHECAGEM DE REDECLARACAO FEITA AQUI. CHECAGEM DE PARAMETROS,
  // NAO PODE SER FEITA AQUI
  printf("lastDecl: (%p)\n", old);
  if(old) {
    if(old->def_fun) {
      printf("[defFun-Semantico] Funcao %s jah foi definida em l.%d, c.%d\n",
      old->id, old->local.line, old->local.col);
    }
    else if(old->tag == TYPE_DECL_FUN) {
      fprintf(stderr, "Funcao %s foi pre-declarada\n", old->id);
      check_signature = 1;
      declared_curr_fun = 1;
    }
    else {
      fprintf(stderr,"Jah tem variavel com esse nome :/\n");
    }
  }
  else {
    printf("definindo funcao %s\n", $ID); fflush(stdout);
    SymEntry* neoEntry = add_entry(&reshi, $ID, TYPE_DEF_FUN);
    neoEntry->type = $BASE_TYPE;
    neoEntry->def_fun = 1;
  }
  currScope = $ID;
} paramListVoid ')' '{' declList localStmtList '}' {
  if(check_signature) {   
    fprintf(stderr,"Checando assinatura de %s\n", $ID);
    currScope = GLOBAL_SCOPE;
    SymEntry* entry = last_decl(&reshi, $ID);
    // assert(entry != NULL);  // se der NULL, algo deu errado pois a funcao jah era pra estar na symTable
    if(entry) {
      if(entry->def_fun) {
        mensagem_redeclaracao(entry);
        $$ = NULL;
      }
      else {
        fprintf(stderr,"entry->astNode: %p, $paramListVoid: %p \n", entry->astNode, $paramListVoid);
        int match = match_paramList(entry->astNode->param, $paramListVoid);
        if(match > 0){
          printf("DEFINICAO de %s BATE COM DECLARACAO!\n", $ID);
          // SymEntry* neoEntry = add_entry(&reshi, $ID, TYPE_DEF_FUN);
          // neoEntry->type = $BASE_TYPE;
        }
        else {
          printf("Lista de parametros de %s incompativel com sua declaracao!\n", $ID);
        }
      }
    }
    currScope = GLOBAL_SCOPE;
    check_signature = 0;
    declared_curr_fun = 0;
    // $$ = NULL;
  }
  
  MAKE_NODE(defFun);

  SymEntry* tmp;
  HASH_FIND_STR(reshi, $ID, tmp);
  if(!tmp) {
    printf("FDP\n"); fflush(stdout);
  }
  tmp->tag = TYPE_DEF_FUN;
  tmp->type = $BASE_TYPE;
  No* _BASE_TYPE = Token_New(STR(BASE_TYPE), type2string($BASE_TYPE));
  No* _ID = Token_New(STR(ID), $ID);
  free($ID);$ID = NULL;
  add_Node_Child_If_Not_Null($$, _BASE_TYPE);
  add_Node_Child_If_Not_Null($$, _ID);
  add_Node_Child_If_Not_Null($$, $paramListVoid);

  add_Node_Child_If_Not_Null($$, $declList);
  add_Node_Child_If_Not_Null($$, $localStmtList);  
  def_fun_rule = 0;
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
  printf("addExpr\n");
  $$->ival = '+';
  
  add_Node_Child_If_Not_Null($$, $1);
  add_Node_Child_If_Not_Null($$, $3);
  // SEMANTICO
  $$->type = bin_expr_type( $1->type, $3->type, '+');
  printf("tipoResultante: %s\n", type2string($$->type));
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
    printf("[Semantico] Erro: operando de & deve se lvalue.\n");
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
}
| FCAST '(' expr ')' {
  MAKE_NODE(expr);
  // TODO: checar se faz sentido a conversao
  $$->type = TYPE_FLOAT;  
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
  SymEntry* aux = last_decl(&reshi, $ID);
  if(!aux){
    printf("Funcao %s, l.%d c.%lu nao declarada!\n", $ID, numlines, currCol - (strlen($ID) + 2));
  }
  else {
    $$->type = aux->type;
    if(aux->tag != TYPE_DEF_FUN && aux->tag != TYPE_DECL_FUN ) {
      printf("[Semantico] %s nao eh funcao pra ser chamada.\n", aux->id);
    }
    else {
      // Checar lista de argumentos e vre se dah certo
    }
  }
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
    }
    else {
      printf("%s nao eh funcao para ser chamada\n", aux->id);
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
  MAKE_NODE(lvalue);
  No* tok = Token_New("ID", $ID);
  add_Node_Child_If_Not_Null($$, tok);
  // SEMANTICO    
  SymEntry* entry = last_decl(&reshi, $ID);
  printf("[ID: %s]entry->type: %s\n", $ID, type2string(entry->type));
  if(entry) {
    if(is_fun(entry->tag)) {
      printf("Identificador %s, l.%d c.%lu DECLARADO PREVIAMENTE como funcao em l.%d, c.%d!\n",
       $ID, numlines, currCol - (strlen($ID) + 2), entry->local.line, entry->local.col);
    }
    else {
      tok->type = entry->type;
      $$->type = entry->type;
      link_symentry_no(&entry, &tok);
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
  MAKE_NODE(lvalue);
  add_Node_Child_If_Not_Null($$, Token_New("ID", $ID));
  add_Node_Child_If_Not_Null($$, $expr);
  // SEMANTICO    
  if(!last_decl(&reshi, $ID)){printf("Variavel %s, l.%d nao declarada!\n", $ID, numlines);}
}
| ID '[' expr ']' '[' expr ']' {
  MAKE_NODE(lvalue);
  add_Node_Child_If_Not_Null($$, Token_New("ID", $ID));
  add_Node_Child_If_Not_Null($$, $3);
  add_Node_Child_If_Not_Null($$, $6);
  // SEMANTICO    
  if(!last_decl(&reshi, $ID)){printf("Variavel %s, l.%d nao declarada!\n", $ID, numlines);}
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
  print_reshi(reshi);
  yylex_destroy();
  
  free_All_Child(root);
  free_Lis(root);
}