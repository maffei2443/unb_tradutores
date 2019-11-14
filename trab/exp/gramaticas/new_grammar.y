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
    neoEntry = was_declared(&reshi, yyvsp[__id]._id);    \
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
int decl_fun = 0;
int def_fun = 0;
int check_parameters = 0;
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
  decl_fun = 1;
  SymEntry* tmp = was_declared(&reshi, $ID);
  if( !tmp ) {
    SymEntry* neoEntry = add_entry(&reshi, $ID, TYPE_FUN);
    neoEntry->tag = $BASE_TYPE;
  }
  else {
    printf("%s nao pode ser definido pois jah foi declarado em l.%d, c.%d\n", tmp->id, tmp->local.line, tmp->local.col);
  }
  currScope = $ID;
} '(' paramListVoid ')' {
  SymEntry* tmp;
  HASH_FIND_STR(reshi, $ID, tmp);
  tmp->tag = TYPE_FUN;
  tmp->type = $BASE_TYPE;

  MAKE_NODE(declFun);
  
  add_Node_Child_If_Not_Null($$, Token_New("BASE_TYPE", type2string($BASE_TYPE)));
  add_Node_Child_If_Not_Null($$, Token_New(STR(ID), $ID));
  free($ID), $ID = NULL;
  add_Node_Child_If_Not_Null($$, $paramListVoid);
  currScope = GLOBAL_SCOPE;
  decl_fun = 0;
}


typeAndNameSign : BASE_TYPE ID {
  SymEntry* neoEntry = add_entry(&reshi, $ID, $BASE_TYPE);
  printf("[typeAndNameSign] %p\n", neoEntry);
  printf("[typeAndNameSign->tag] %s\n", type2string(neoEntry->tag));
  MAKE_NODE(typeAndNameSign);
  link_symentry_no(neoEntry, $$);
  
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
  SymEntry* neoEntry = add_entry(&reshi, $ID, TYPE_PARAM);
  PARAM_RPT_NAME_CHECK(-1, 0);
  link_symentry_no(neoEntry, $$);
  free($ID), $ID = NULL;
}
| BASE_TYPE ID '[' ']' {
  $$ = Token_New(STR(param), $ID);
  SymEntry* neoEntry = add_entry(&reshi, $ID, TYPE_PARAM );
  // SEMANTICO
  PARAM_RPT_NAME_CHECK(-3, -2);
  
  if($BASE_TYPE == TYPE_INT)    neoEntry->type = TYPE_ARRAY_INT;
  else if ($BASE_TYPE == TYPE_FLOAT) neoEntry->type = TYPE_ARRAY_FLOAT;
  else {
    printf("BASE_TYPE deve ser apenas TYPE_INT ou TYPE_FLOAT\n");
    abort();
  }
  $$->type = $BASE_TYPE;
  link_symentry_no(neoEntry, $$);
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
  link_symentry_no(neoEntry, $$);  
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
  def_fun = 1;
  SymEntry* old = was_declared(&reshi, $ID);
  if(old) {
    if(old->tag == TYPE_FUN) {
      if(old->def_fun){
        printf("[Semantico] Funcao %s jah foi definida em l.%d, c.%d\n",
        old->id, old->local.line, old->local.col);
      }
      else {
        // PODE SER QUE FUNCAO TENHA ASSINATURA DIFERENTE!
        check_signature = 1;
      }
    }
    else {
      printf("[Semantico] Identificador %s jah foi definida em l.%d, c.%d como nao-funcao!\n",
        old->id, old->local.line, old->local.col);
    }
  }
  else {
    SymEntry* neoEntry = add_entry(&reshi, $ID, TYPE_FUN);
    neoEntry->type = $BASE_TYPE;
  }
  currScope = $ID;
} paramListVoid ')' {
  if(check_signature) {
    printf("ADD O CAO\n");
    if(match_paramList(was_declared(&reshi, $ID), $paramListVoid) > 0){
      SymEntry* neoEntry = add_entry(&reshi, $ID, TYPE_FUN);
      neoEntry->type = $BASE_TYPE;      
    }
    else {
      printf("Lista de parametros de %s incompativel com sua declaracao!\n", $ID);
    }
    check_signature = 0;
  }
} '{' declList localStmtList '}' {
  
  SymEntry* tmp;
  HASH_FIND_STR(reshi, $ID, tmp);
  tmp->tag = TYPE_FUN;
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
  def_fun = 0;
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
    if(aux->tag != TYPE_FUN) {
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
    if(aux->tag != TYPE_FUN) {
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
  $$ = $1;
  // MAKE_NODE(arg);
  // add_Node_Child_If_Not_Null($$, $lvalue);
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
    if(entry->tag == TYPE_FUN ) {
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