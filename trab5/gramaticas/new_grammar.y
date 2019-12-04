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
#define INITNODE(x) \
  {yyval.no = No_New(nodeCounter++);\
  if(!yyval.no) abort();\
  yyval.no->tname =  x  ;}
#define MAKE_NODE(x) INITNODE(STR(x))
// TODO: onde aparece setar variavel de erro!
#define PARAM_RPT_NAME_CHECK(__baseType, __id) \
  if(!neoEntry) {\
    neoEntry = last_decl(&reshi, yyvsp[__id]._id);    \
    ERRSHOW(printf("[Semantico] Parametros de mesmo nome! Arvore vai ficar inconsistente..\n"));\
  }\
  else {\
    neoEntry->type = yyvsp[__baseType].type;\
    yyval.no->type = yyvsp[__baseType].type;\
    neoEntry->tag = TAG_PARAM;\
  }
#define BLANK_INT "              "
#define BLANK_FLOAT "                           "
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
static int BLANK_FLOAT_SIZE = strlen(BLANK_FLOAT);
static int BLANK_INT_SIZE = strlen(BLANK_INT);

#include "Tree.h" // importante
#include "SemanticChecker.h"
#include "code_gen.h"
#include "Common.h"
#include "Colorfy.h"
#include "Stack.h"
extern int yylineno;
extern int currCol;
extern int numlines;
extern int yyleng;
extern int yylex();
void yyerror (char const *s);

extern void yylex_destroy();
// 
unsigned nodeCounter;

char* GLOBAL_SCOPE = "0global";

SymEntry* reshi;

char* currScope = NULL;
int check_signature = 0;
int decl_fun_rule = 0;
int def_fun_rule = 0;
int declared_curr_fun = 0;
int check_parameters = 0;
int err = 0;
int aborta = 0;

extern Stack* new_flow_stack;
extern Stack* after_if_stack;


%}
%define parse.error verbose
%define parse.lac none
%define parse.trace

%token-table
%locations

%left ARITM REL_OP BIN_LOGI
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
%type<ival> ARITM REL_OP BIN_LOGI
%token ARITM REL_OP BIN_LOGI

%token BASE_TYPE WHILE V_INT V_FLOAT V_ASCII AHEAD
%token MAT_TYPE IF ID ICAST FCAST ELSE


%token RETURN PRINT IREAD FREAD COPY
%token AND OR
%token BIN_OP
%token ERRU

%type<no> program
%type<no> globalStmtList globalStmt declFun param declOrdeclInitVar paramListVoid 
%type<no> paramList localStmtList localStmt flowControl
%type<no> newFlowControl
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
| declFun error

declFun : AHEAD BASE_TYPE ID {
  decl_fun_rule = 1;
  SymEntry* tmp = last_decl(&reshi, $ID);
  if( !tmp ) {
    printf("DEVE ADICIONAR %s como declaracao de funcao\n", $ID);
    add_entry(&reshi, $ID, TAG_DECL_FUN);
    err = 0;    
  }
  else {
    ERRSHOW(printf("[Semantico] |%s| nao pode ser declarado pois jah o foi em l.%d, c.%d\n", tmp->id, tmp->local.line, tmp->local.col));
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
    tmp->tag = TAG_DECL_FUN;
    tmp->type = $BASE_TYPE;
  }
  
  add_Node_Child_If_Not_Null($$, Token_New("BASE_TYPE", type2string($BASE_TYPE)));
  add_Node_Child_If_Not_Null($$, Token_New(STR(ID), $ID));
  printf("[%s] pre-declarou-se!\n", $ID);
  
  add_Node_Child_If_Not_Null($$, $paramListVoid);
  $$->param = $paramListVoid; // Para rahpido acesso
  
  link_symentry_no(&tmp, &$$);
  
  free($ID), $ID = NULL;
  currScope = GLOBAL_SCOPE;
  decl_fun_rule = 0;
}


declOrdeclInitVar : typeAndNameSign ';'
| typeAndNameSign '=' rvalue ';' {
  if($1 == NULL || $3 == NULL) {
    $$ = NULL;
    ERRSHOW(printf("[Semantico] NAo foi possivel construir <declOrdeclInitVar> devido a erro semantico.\n"));
  }
  else {
    MAKE_NODE(declOrdeclInitVar);
    add_Node_Child_If_Not_Null($$, $typeAndNameSign);
    add_Node_Child_If_Not_Null($$, $rvalue);
    No* decl = $1, *rval = $3;
    Type t1 = $1->type, t2 = $3->type;
    
    Type left_class = Type_Class(t1);
    Type right_class = Type_Class(t2);

    char* r;
    char* l = get_addr($1);

    if(left_class == right_class) {
      if(t1 == t2) {
          CODESHOW( printf("mov %s, %s\n", get_addr(decl), get_addr(rval)) );
      } else {  // efetuar conversoes, jah que sao de mesma classe
        // Converter do tipo de rvalue -> declOrInitVar 
        if(left_class < right_class) {
          printf("[Warning] Conversao %s -> %s vai perder informacao\n", type2string(t1), type2string(t2));
          // r = narrow(rval,decl);
          switch(left_class) {
            case TYPE_MAT: CODESHOW(printf("Converter para matriz de int\n")); break;
            case TYPE_ARRAY: CODESHOW(printf("Nao se pode operar sobre arrays %d\n", 2)); break;
            case TYPE_SCALAR: CODESHOW(printf("Converter float -> int\n")); break;
          } 
        } else {  // conversao widen
          CODESHOW(printf("Widening ..."));
          r = widen(rval,decl);
          switch(left_class) {
            case TYPE_MAT: CODESHOW(printf("Convertes para matriz de float\n")); break;
            case TYPE_ARRAY: CODESHOW(printf("Nao se pode operar sobre arrays %d\n", 2)); break;
            case TYPE_SCALAR: { CODESHOW(printf("Convertendo... "));break;}
          }
          CODESHOW(printf("mov %s, %s\n", l, r));
        }        
      }
    } else {
      if( left_class == TYPE_SCALAR ) {
        if (right_class == TYPE_SCALAR) {
          printf("Atibuicao entre escalares ok\n");
        }
        else {
          ERRSHOW(printf("[Semantico] Erro de Atribuicao: %s = %s\n!", type2string(t1), type2string(t2)));
        }
      } else if ( left_class == TYPE_MAT ) {
        if(right_class == TYPE_MAT) {
          CODESHOW(printf("TODO: atribuicao de matriz para matriz: %s <- %s\n", 
            type2string(t1), type2string(t2)));
        }
      } else if( left_class == TYPE_MAT) {
        if ($rvalue->type != TYPE_LIST_LIST) {
          ERRSHOW(printf("[Semantico] Erro: inicializacao de matriz com %s\n", type2string($rvalue->type)));
        }
        else {
          CODESHOW(printf("INICIALIZAR MATRIZ COM NUMEROS\n"));
        }
      }
    }
    DESTROY_PTR(l); DESTROY_PTR(r);
  }
  
}
| typeAndNameSign '=' rvalue error

typeAndNameSign : BASE_TYPE ID {
  SymEntry* oldEntry = last_decl(&reshi, $ID);
  // printf("Recuperado da tabela de simbolos: %p\n", oldEntry);
  // printf("base_type: %s\n", type2string($BASE_TYPE));
  char err = 0;
  if(oldEntry) {
    if( !strcmp(oldEntry->escopo, currScope) ) {
      ERRSHOW(printf("[Semantico] Erro: Redeclaracao de %s:%s!\n", oldEntry->escopo, oldEntry->id));
      err = 1;
    }
    else {
      printf("\tDeclaracoes sob escopos distintos.\n");
    }
  }

  if (!err) {
    SymEntry* neoEntry = add_entry(&reshi, $ID, TAG_UNDEFINED);
    if(neoEntry) {  // DE UTUDO CERTO
      neoEntry->type = $BASE_TYPE;
      MAKE_NODE(typeAndNameSign);
      link_symentry_no(&neoEntry, &$$);      
      add_Node_Child_If_Not_Null($$, Token_New("BASE_TYPE", type2string($BASE_TYPE)));
      add_Node_Child_If_Not_Null($$, Token_New("ID", $ID));
      
      // para facilitar geracao de cohdigo
      point_no_symentry(&neoEntry, &$$);      
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
  // printf("Recuperado da tabela de simbolos: %p\n", oldEntry);
  
  char err = 0;
  if(oldEntry) {
    if( !strcmp(oldEntry->escopo, currScope) ) {
      ERRSHOW(printf("[Semantico] Erro: Redeclaracao de %s:%s!\n", oldEntry->escopo, oldEntry->id));
      err = 1;
    }
    else {
      printf("\tDeclaracoes sob escopos distintos.\n");
    }
  }

  if (!err) {
    if ($num->type != TYPE_INT) {
      ERRSHOW(printf("[Semantico] Erro: Tamanho de vetor deve ser um inteiro! Encontrado: %s\n", type2string($num->type)));
      $$ = NULL;
    }  else if ($num->ival < 0) {
      ERRSHOW(printf("[Semantico] Erro: Tamanho deve ser >= 0\n"));
    }  else {   // DEU TUDO CERTO! 
      SymEntry* neoEntry = add_entry(&reshi, $ID, TAG_UNDEFINED);
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

        // para facilitar geracao de cohdigo
        point_no_symentry(&neoEntry, &$$);
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
    ERRSHOW(printf("[Semantico] Nao adicionou (%s) aa tabela de simbolos (redeclaracao, tamanho nao inteiro, algo deu errado).\n", $ID));
  }
  free($ID);$ID = NULL;
}

| MAT_TYPE BASE_TYPE ID '[' num ']' '[' num ']' {
  // Procedimento analogo ao de cima,
  SymEntry* oldEntry = last_decl(&reshi, $ID);
  // printf("Recuperado da tabela de simbolos: %p\n", oldEntry);
  
  char err = 0;
  if(oldEntry) {
    if( !strcmp(oldEntry->escopo, currScope) ) {
      ERRSHOW(printf("[Semantico] Erro: Redeclaracao de %s:%s!\n", oldEntry->escopo, oldEntry->id));
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
        ERRSHOW(printf("[Semantico] ERRO[2]: Quantidade de linhas de matriz deve ser um inteiro. (%s encontrado)\n", type2string($5->type)));
      }
      if(secNum) {
        ERRSHOW(printf("[Semantico] ERRO[2]: Quantidade de colunas de matriz deve ser um inteiro. (%s encontrado)\n", type2string($8->type)));
      }
      $$ = NULL;
    }
    else {    // TUDO CERTO: PODE CIRAR O NOH
      Type type = $BASE_TYPE == TYPE_FLOAT ? TYPE_MAT_FLOAT : TYPE_MAT_INT;
      SymEntry* neoEntry = add_entry(&reshi, $ID, TAG_UNDEFINED);
      if(neoEntry) {
        // TODO: checar se num eh inteiro. Se nao for, ERRO
        MAKE_NODE(typeAndNameSign);
        $$->type = type;
        // link_symentry_no(&neoEntry, &$$);
        // [ WARNING ] todo: testar!  Nao deve dar problema... eh soh pra facilitar geracao de codigo

        // add_Node_Child_If_Not_Null($$, Token_New("BASE_TYPE", type2string(type)));
        add_Node_Child_If_Not_Null($$, Token_New("ID", $ID));
        add_Node_Child_If_Not_Null($$, $5);
        add_Node_Child_If_Not_Null($$, $8);
        neoEntry->line = $5->ival;
        neoEntry->col = $8->ival;
        neoEntry->type = type;
        // para facilitar geracao de cohdigo
        // point_no_symentry(&neoEntry, &$$);
        $$->symEntry = neoEntry;
        $$->type = neoEntry->type;
        // ERRSHOW(printf("[typeAndNameSign] BEFORE %p->is_param = %d\n",$$, $$->is_param));
        link_symentry_no(&neoEntry, &$$);
        // printf("");
        // ERRSHOW(printf("[typeAndNameSign] AFTER %p->is_param = %d\n",$$, $$->is_param));
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
  $$->is_param = 1;
  SymEntry* funEntry = last_decl(&reshi, $ID);
  printf("!!! %p, %s: param @@@\n", funEntry, $ID);
  if(!declared_curr_fun) {
    SymEntry* neoEntry = add_entry(&reshi, $ID, TAG_PARAM);
    if(neoEntry) {
      neoEntry->type =  $BASE_TYPE;
      $$->type =  $BASE_TYPE;
      PARAM_RPT_NAME_CHECK(-1, 0);
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
  $$->is_param = 1;
  // TODO: checar por declaracao previa de parametro!
  SymEntry* neoEntry = add_entry(&reshi, $ID, TAG_PARAM );
  // SEMANTICO
  PARAM_RPT_NAME_CHECK(-3, -2);
  
  if($BASE_TYPE == TYPE_INT)    neoEntry->type = TYPE_ARRAY_INT;
  else if ($BASE_TYPE == TYPE_FLOAT) neoEntry->type = TYPE_ARRAY_FLOAT;
  else if ($BASE_TYPE == TYPE_CHAR) neoEntry->type = TYPE_ARRAY_CHAR;
  else {
    ERRSHOW(printf("BASE_TYPE deve mao identificado\n"));
    neoEntry->type = TYPE_UNDEFINED;
  }
  $$->type = neoEntry->type;  // IMPORTANTE
  if(neoEntry)
    link_symentry_no(&neoEntry, &$$);
  free($ID), $ID = NULL;
}

| MAT_TYPE BASE_TYPE ID {
  // TODO: checar por declaracao previa de parametro!
  $param = Token_New(STR(param), $ID);
  $$->is_param = 1;
  SymEntry* neoEntry = add_entry(&reshi, $ID, TAG_PARAM);
  // Semantico
  PARAM_RPT_NAME_CHECK(-1, 0);
  Type tipo;
  switch($BASE_TYPE) {
    case TYPE_CHAR: tipo = TYPE_MAT_CHAR; break;
    case TYPE_INT: tipo = TYPE_MAT_INT; break;
    case TYPE_FLOAT: tipo = TYPE_MAT_FLOAT; break;
  }
  $$->type = tipo;
  neoEntry->type = tipo;

  if($BASE_TYPE == TYPE_INT) neoEntry->type = TYPE_MAT_INT;  
  else if ($BASE_TYPE == TYPE_FLOAT) neoEntry->type = TYPE_MAT_FLOAT;
  else if ($BASE_TYPE == TYPE_CHAR) neoEntry->type = TYPE_MAT_CHAR;
  else {
    ERRSHOW(printf("BASE_TYPE deve mao identificado\n"));
    neoEntry->type = TYPE_UNDEFINED;
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
  // TODO: CHECAR TIPOS!
  MAKE_NODE(localStmt);
  char* leftAddr, *rightAddr = NULL;
  leftAddr = get_addr($lvalue);

  Type t1 = $lvalue->type, t2 = $rvalue->type;
  Type c1 = Type_Class(t1), c2 = Type_Class(t2);
  const char* s1 = type2string(t1), *s2 = type2string(t2);
  
  /*   BoldGray();
  printf("%s -- %s\n", s1, s2);
  Reset();*/

  // ################# VAI VIRAR FUNCAO
  int to_cast = 0;
  if(t1 == TYPE_UNDEFINED || t2 == TYPE_UNDEFINED ||
    to_base_type(t1) == TYPE_CHAR || to_base_type(t1) == TYPE_CHAR) {
    to_cast = 0;
    ERRSHOW(printf("Erro: UNDEFINED/char em atribuicao: %s = %s\n", s1, s2));
  } else if ( c1 == c2 && c1 == TYPE_MAT && t1 != t2 ) {
    to_cast = 1;
    WARSHOW(printf("Conversao entre matrizes. %s = %s\n", type2string(t1), type2string(t2)));
  } else if (c1 == TYPE_ARRAY && c2 == TYPE_ARRAY) {
    if(to_base_type(t1) > to_base_type(t2)) {
      to_cast = 1;
    } else {
      ERRSHOW(printf("Erro de tipo. %s = %s\n", type2string(t1), type2string(t2)));
    }
  } else if (c1 == c2 && t1 != t2){ 
    to_cast = 1;
    WARSHOW(printf("[Semantico] Warning de tipo em atribuicao: <%s> = <%s>\n",
     type2string(t1), type2string(t2)));
  } else to_cast = 1;
  if(to_cast) {
    if( t1 < t2 ) {
      ERRSHOW(printf("Nao eh possivel a atribuicao %s = %s : narrow casting\n", s1, s2));    
      rightAddr = "impossivel";  
    } else {
      if(can_cast(t2, t1)) {
        rightAddr = widen( $rvalue, $lvalue );
      } else {
        ERRSHOW(printf("Nao eh possivel a atribuicao %s = %s : cast inexistente\n", s1, s2));
      }
    }
  }
  CODESHOW(pf("mov %s, %s\n", leftAddr, rightAddr));
  // ################# VAI VIRAR FUNCAO


  add_Node_Child_If_Not_Null($$, $lvalue);
  add_Node_Child_If_Not_Null($$, $rvalue);
}
| newFlowControl {
  MAKE_NODE(localStmt);
  add_Node_Child_If_Not_Null($$, $newFlowControl);
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
    ERRSHOW(printf("[Semantico] Erro: Leitura de inteiro sobre tipo |%s|\n", type2string($lvalue->type)));
  }
}
| FREAD '(' lvalue ')' ';' {
  MAKE_NODE(localStmt);
  No* fread_no = Token_New("FREAD","FREAD");
  add_Node_Child_If_Not_Null($$, fread_no);
  add_Node_Child_If_Not_Null($$, $lvalue);
  if($lvalue->type != TYPE_FLOAT) {
    ERRSHOW(printf("[Semantico] Erro: Leitura de inteiro sobre tipo |%s|\n", type2string($lvalue->type)));
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

newFlowControl : {WARSHOW(printf("__newFlow%d:\n", __new_flow )); __new_flow++; }
 flowControl {
   $$ = yyvsp[0].no;
   __new_flow--;
   WARSHOW(printf("endFlow%d:\n", __new_flow));
}

flowControl :  IF '(' expr ')' {
    char* expr_addr = get_addr($expr);
    __after_if++;
    CODESHOW(printf("brz __afterIf%d, %s\n", __after_if, expr_addr));
    free(expr_addr);    
  } block {
    CODESHOW(printf("jump __endFlow%d\n", __new_flow-1 ) ) ;
    WARSHOW( printf("__afterIf%d:\n",  __after_if) );
  }
  ELSE {} flowControl {
      MAKE_NODE(flowControl);
      add_Node_Child_If_Not_Null($$, Token_New("IF","if"));
      add_Node_Child_If_Not_Null($$, $expr);
      add_Node_Child_If_Not_Null($$, $block);
      add_Node_Child_If_Not_Null($$, Token_New("ELSE","else"));
      add_Node_Child_If_Not_Null($$, yyvsp[0].no);
      __after_if--;
      WARSHOW(printf("__afterElse%d:\n", __after_if+1 ) ) ;
    }
// block e ';' foram movidos para cah de modo a nao haver conflito na gramatica
| block
| ';' {$$ = NULL;}
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
| IF '(' error ')' {} block {
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

  new_context();

  def_fun_rule = 1;
  SymEntry* old = last_decl(&reshi, $ID);
  // CHECAGEM DE REDECLARACAO FEITA AQUI. CHECAGEM DE PARAMETROS,
  // NAO PODE SER FEITA AQUI
  // printf(stderr, "lastDecl: (%p)\n", old);
  if(old) {
    if(old->def_fun) {
      printf("[defFun-Semantico] Erro: Funcao %s jah foi definida em l.%d, c.%d\n",
      old->id, old->local.line, old->local.col);
    }
    else if(old->tag == TAG_DECL_FUN) {
      fprintf(stderr, "Funcao %s foi pre-declarada\n", old->id);
      check_signature = 1;
      declared_curr_fun = 1;
    }
    else {
      fprintf(stderr,"Jah tem variavel com esse (%s) nome :/\n", old->id);
      aborta = 1;
    }
  }
  else {
    // fprintf(stderr, "definindo funcao %s\n", $ID); fflush(stdout);
    SymEntry* neoEntry = add_entry(&reshi, $ID, TAG_DEF_FUN);
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
  printf("%p ====== paramListVoid\n", $paramListVoid);
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
          // TODO: ATUALIZAR NOME DOS PARAMETROS PARA QUANDO FOR USAR A FUNCAO,
          // CONTAR OS NOMES DOS PARAMETROS USADOS NA DEFINICAO
          // SymEntry* neoEntry = add_entry(&reshi, $ID, TAG_DEF_FUN);
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
  if (!aborta) {  // nao modificar a entrada jah existente da tabela de simbolos
    tmp->tag = TAG_DEF_FUN;
    tmp->type = $BASE_TYPE;

    $$->param = $paramListVoid;
    printf("PARAM BECOME %p\n", $$->param);
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
  def_fun_rule = 0;
  currScope = GLOBAL_SCOPE;
  free($ID);$ID = NULL;
  
  old_context();
}

numListList :  numListList '{' numList '}' {
  MAKE_NODE(numListList);
  add_Node_Child_If_Not_Null($$, $1);
  add_Node_Child_If_Not_Null($$, $numList);
}
| %empty {
  $$ = NULL;
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
// Em todos os casos, faz-se:
//  1 - infere o tipo da expressao final ($$)
//  2 - verifica se ambos os operandos podem ser convertidos para tal tipo
expr : expr ARITM expr {

  MAKE_NODE(expr);
  $$->ival = $ARITM;
  No* e = $$, *e1 = $1, *e2 = $3;
  Type t1 = e1->type, t2 = e2->type;
  // printf("ARTM_OP: ");
  char* e2_addr, *e1_addr, *e_addr;
  e2_addr = get_addr(e2);
  e1_addr = get_addr(e1);
  e_addr = get_addr(e);
  char* op;
  switch($ARITM) {
    case '+': op = "add"; break;
    case '-': op = "sub"; break;
    case '/': op = "div"; break;
    case '*': op = "mul"; break;
  }
  CODESHOW(printf("%s %s, %s, %s\n", op , e_addr, e1_addr, e2_addr));
  free(e2_addr);
  free(e1_addr);
  free(e_addr);
  // abort();
  add_Node_Child_If_Not_Null($$, e1);
  add_Node_Child_If_Not_Null($$, e2);
  // SEMANTICO
  $$->type = bin_expr_type( t1, t2, $$->ival);
  // DBG(printf("RESULT TYPE: %s", type2string(e->type)));
  // DBG(printf(" from: %s + %s\n", type2string(e1->type), type2string(e2->type)));
  // printf("\t    : (is_const)%d + (is_const)%d\n", e1->is_const, e2->is_const);

  // printf("%s\n", widen($1 ,$$));
  // printf("%s\n", widen($3, $$));

  // GERACO DE CODIGO
}

| expr '%' expr {
  MAKE_NODE(expr);

  $$->ival = '%';
  add_Node_Child_If_Not_Null($$, $1);
  add_Node_Child_If_Not_Null($$, $3);
  // SEMANTICO
  $$->type = bin_expr_type( $1->type, $3->type, '%');
  if($3->type != TYPE_INT) {
    printf("[Erro] Operando aa direita de mohdulo deve ser INTEIRO!\n");
  }
  else if ($1->type != TYPE_INT) {
    printf("[Erro] Operador aa esquerda de mohdulo deve ser INTEIRO\n");
  }
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

| expr REL_OP expr {
  MAKE_NODE(expr);

  $$->ival = $REL_OP;
  add_Node_Child_If_Not_Null($$, $1);
  add_Node_Child_If_Not_Null($$, $3);
  // SEMANTICO
  $$->type = bin_expr_type( $1->type, $3->type, $$->ival);

  // GERADOR 
  No* e = $$, *e1 = $1, *e2 = $3;
  Type t1 = e1->type, t2 = e2->type;
  printf("REL_OP: ");
  char* e2_addr, *e1_addr, *e_addr;
  e2_addr = get_addr(e2);
  e1_addr = get_addr(e1);
  e_addr = get_addr(e);

  if( $$->ival <= 127 ) 
    CODESHOW(
      printf("|%c| %s, %s, %s\n", $$->ival ,
        e_addr, e1_addr, e2_addr))
  else
    CODESHOW(
      printf("|%d| %s, %s, %s\n", $$->ival ,
        e_addr, e1_addr, e2_addr))

}

| expr BIN_LOGI expr {
  MAKE_NODE(expr);

  $$->ival = $BIN_LOGI;
  $$->type = bin_expr_type( $1->type, $3->type, $$->ival);

  No* e = $$, *e1 = $1, *e2 = $3;
  Type t1 = e1->type, t2 = e2->type;
  // DBG(printf("BIN_LOGI\n"));
  char* e2_addr, *e1_addr, *e_addr;
  e2_addr = get_addr(e2);
  e1_addr = get_addr(e1);
  e_addr = get_addr(e);

  CODESHOW(printf("%c %s, %s, %s\n",$$->ival , e_addr, e1_addr, e2_addr));
  free(e2_addr);
  free(e1_addr);
  free(e_addr);


  
  add_Node_Child_If_Not_Null($$, $1);
  add_Node_Child_If_Not_Null($$, $3);
  // SEMANTICO
}
| '!' expr {
  MAKE_NODE(expr);
  // TODO: RECLAMAR SE NAO "BOOL"
  $$->type = TYPE_INT;
  $$->ival = '!';
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
    ERRSHOW(
      printf("[Semantico] Erro: nao pode converter nao-escalar (e.g %s) para inteiro.\n", type2string($3->type))
      );
  }
}
| FCAST '(' expr ')' {
  MAKE_NODE(expr);
  // TODO: checar se faz sentido a conversao
  $$->type = TYPE_FLOAT;  
  add_Node_Child_If_Not_Null($$, Token_New("FCAST", "FCAST"));
  add_Node_Child_If_Not_Null($$, $3);
  if(Type_Class($3->type) != TYPE_SCALAR) {
    ERRSHOW(printf("[Semantico] Erro: nao pode converter nao-escalar (e.g %s) para inteiro.\n",
      type2string($3->type)));
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
  printf("type of %s: %s\n", $ID, type2string(aux->type));
  printf("%s 1st param: %p\n", $ID, aux->astNode->param);
  printf("type of %s param: %s\n", $ID, type2string(aux->astNode->param->type));
  if(!aux){
    printf("Funcao %s, l.%d c.%lu nao declarada!\n", $ID, numlines, currCol - (strlen($ID) + 2));
  }
  else{
    $$->type = aux->type;
    if(is_fun (aux->tag)) {
      // printf("%s eh uma funcao!.\n", aux->id);
      // Ver se assinatura bate com a declaracao!
      if(aux->astNode) {
        int match = match_paramList(aux->astNode->param, $argList);
        if(match > 0) {
          printf("[++++Semantico++++] Argumentos de %s corretos\n", $ID);
          CODESHOW(printf("call %s, %d\n", $ID, $argList->ival));
        }
        else
          printf("[----Semantico----] Uso indevido de %s\n", $ID); 
      } else {
        printf("TODO : CHECAR SE ARGLIST EH VAZIO !!!\n");
      }
      
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
  $$->ival += 1;
}
| arg {
  $$ = $1;
  $$->ival = 1;
}

arg : lvalue {
  assert( $lvalue->symEntry );
  printf("param $%d (%s)\n", $1->symEntry->addr, $1->symEntry->id);
  $$ = $1;
}
| ID '(' expr ')' '(' expr ')' {
  SymEntry* entry = last_decl(&reshi, $ID);
  assert( entry );
  $$->type = entry->type;
  
  BoldCyan();
  if(entry->is_global)
    printf("param %s\n", entry->id);
  else
    printf("param $%d\n", entry->addr);

  printf("param %s\n", get_addr($3));
  printf("param %s\n", get_addr($6));
  Reset();

  MAKE_NODE(arg);
  add_Node_Child_If_Not_Null($$, Token_New("ID", $ID));
  add_Node_Child_If_Not_Null($$, $3);
  add_Node_Child_If_Not_Null($$, $6);
  // add_Node_Child_If_Not_Null($$, $6);
  // SEMANTICO    
  // SymEntry* entry = last_decl(&reshi, $ID);
  if(!entry) {  // var na odeclarada
    ERRSHOW(printf("[Semantico] Erro: Variavel %s, l.%d nao declarada\n", $ID, numlines);   );
  }
  else {
    if(is_fun(entry->tag)) {
      ERRSHOW(printf("[Semantico] Erro: Uso inadequado de funcao %s, l.%d\n", $ID, numlines));
    }
    else if(Type_Class(entry->type) != TYPE_MAT ) {
      ERRSHOW(printf("[Semantico] Erro: Variavel %s, l.%d nao eh matriz\n", $ID, numlines);   );
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
  // DBG(printf("[lvalue] RECOVERY-type: %s\n", type2string(entry->type)));
  // CHECK FOR NULL (== nao declarado)
  // printf("[ID: %s]entry->type: %s\n", $ID, type2string(entry->type));
  if(entry) {
    if(is_fun(entry->tag)) {
      printf("Identificador %s, l.%d c.%lu DECLARADO PREVIAMENTE como funcao em l.%d, c.%d!\n",
       $ID, numlines, currCol - (strlen($ID) + 2), entry->local.line, entry->local.col);
    }
    else {
      point_no_symentry(&entry, &$$);
      point_no_symentry(&entry, &tok);
      $$->type = entry->type;
      // DBG(printf("lvalue %s type: %s\n", $ID, type2string($$->type)));
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
      ERRSHOW(printf("[Semantico] Erro: %s nao eh indexavel!\n",  old->id));
    }
    else {
      point_no_symentry(&old, &$$);
      $$->type = old->type;
      $$->symEntry = old;
      switch( old->type ) {
        case TYPE_MAT_INT: $$->type = TYPE_UMAT_INT; break;
        case TYPE_MAT_FLOAT: $$->type = TYPE_UMAT_FLOAT; break;
        case TYPE_MAT_CHAR: $$->type = TYPE_UMAT_CHAR; break;
        case TYPE_ARRAY_CHAR: $$->type = TYPE_CHAR; break;
        case TYPE_ARRAY_INT: $$->type = TYPE_INT; break;
        case TYPE_ARRAY_FLOAT: $$->type = TYPE_CHAR; break;
        default:
          // nao deve entrar aqui...
          ERRSHOW(printf("[Semantico] Erro: %s nao eh indexavel!\n",  old->id));
      }
      point_no_symentry(&old, &tok);
      tok->type = old->type;
      tok->symEntry = old;      
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
  } else if(Type_Class(old->type) != TYPE_MAT) {
    ERRSHOW(printf("[Semantico] Variavel (%s:%s) nao eh matriz para ser indexada duplamente!\n", old->escopo, old->id));
  } else {
      point_no_symentry(&old, &$$);
      switch( old->type ) {
        case TYPE_MAT_INT: $$->type = TYPE_INT; break;
        case TYPE_MAT_FLOAT: $$->type = TYPE_FLOAT; break;
        case TYPE_MAT_CHAR: $$->type = TYPE_CHAR; break;
        default:
          // nao deve entrar aqui...
          ERRSHOW(printf("[Semantico] Erro: %s nao eh indexavel!\n",  old->id));
      }
      point_no_symentry(&old, &tok);    
  }
  int temp = temp_next();
  printf("old->id: %s\n", old->id);
  printf("old->astNode: %p\n", old->astNode);
  CODESHOW(printf("mov $%d, %s\n", temp, get_addr(old->astNode)));

  CODESHOW(printf("mul $%d, %s, %d\n", temp = temp_next(), get_addr($3), old->col  ));
  
  CODESHOW(printf("add $%d, $%d, %s\n", temp, temp, get_addr($6)));
  temp = temp_next();
  CODESHOW(printf("mov $%d, $%d[$%d]\n", temp,temp-2 , temp-1));
  $$->addr = temp;
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
  yyparse();
  if(root) {
    // show_Sub_Tree(root, 1, SVAL);
    // show_Lis(root,SVAL);
  }
  // print_reshi(reshi);
  yylex_destroy();
  
  // delete_all(reshi);
  free_All_Child(root);
}