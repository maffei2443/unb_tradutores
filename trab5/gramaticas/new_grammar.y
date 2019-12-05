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
  if(!neo_entry) {\
    neo_entry = last_decl(&reshi, yyvsp[__id]._id);    \
    ERRSHOW(printf("[Semantico] Parametros de mesmo nome! Arvore vai ficar inconsistente..\n"));\
  }\
  else {\
    neo_entry->type = yyvsp[__baseType].type;\
    yyval.no->type = yyvsp[__baseType].type;\
    neo_entry->tag = TAG_PARAM;\
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

unsigned if_counter = 0;
unsigned while_counter = 0;
unsigned newFlow_counter = 0;
unsigned closest_flow = 0;
unsigned closest_while = 0;
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

%type<no> IF ELSE WHILE countFlow

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
  
  add_Node_Child_If_Not_Null($$, Token_New("BASE_TYPE", t2s($BASE_TYPE)));
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
    char* l = get_no_addr($1);
    DBG(printf("[lvalue = rvalue] %s = %s\n", t2s(t1), t2s(t2)));
    if(left_class == right_class) {
      if(t1 == t2) {
          CODESHOW( printf("mov %s, %s\n", get_no_addr(decl), get_no_addr(rval)) );
          abort();
      } else {  // efetuar conversoes, jah que sao de mesma classe
        // Converter do tipo de rvalue -> declOrInitVar 
        if(left_class < right_class) {
          printf("[Warning] Conversao %s -> %s vai perder informacao\n", t2s(t1), t2s(t2));
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
          ERRSHOW(printf("[Semantico] Erro de Atribuicao: %s = %s\n!", t2s(t1), t2s(t2)));
        }
      } else if ( left_class == TYPE_MAT ) {
        if(right_class == TYPE_MAT) {
          CODESHOW(printf("TODO: atribuicao de matriz para matriz: %s <- %s\n", 
            t2s(t1), t2s(t2)));
        }
      } else if( left_class == TYPE_MAT) {
        if ($rvalue->type != TYPE_LIST_LIST) {
          ERRSHOW(printf("[Semantico] Erro: inicializacao de matriz com %s\n", t2s($rvalue->type)));
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
  SymEntry* old_entry = last_decl(&reshi, $ID);
  // printf("Recuperado da tabela de simbolos: %p\n", old_entry);
  // printf("base_type: %s\n", t2s($BASE_TYPE));
  char err = 0;
  if(old_entry) {
    if( !strcmp(old_entry->escopo, currScope) ) {
      ERRSHOW(printf("[Semantico] Erro: Redeclaracao de %s:%s!\n", old_entry->escopo, old_entry->id));
      err = 1;
    }
    else {
      printf("\tDeclaracoes sob escopos distintos.\n");
    }
  }

  if (!err) {
    SymEntry* neo_entry = add_entry(&reshi, $ID, TAG_UNDEFINED);
    if(neo_entry) {  // DE UTUDO CERTO
      neo_entry->type = $BASE_TYPE;
      MAKE_NODE(typeAndNameSign);
      link_symentry_no(&neo_entry, &$$);      
      add_Node_Child_If_Not_Null($$, Token_New("BASE_TYPE", t2s($BASE_TYPE)));
      add_Node_Child_If_Not_Null($$, Token_New("ID", $ID));
      
      // para facilitar geracao de cohdigo
      point_no_symentry(&neo_entry, &$$);     

      if(neo_entry->is_global) {
        GLOBALSHOW(
          printf("%s %s\n", t2s(to_base_type( neo_entry->type )),neo_entry->id);
        );
      }

    }
    else {
      printf("ERRO LOGICO: NAO DEVERIA ENTRAR AQUI! %s:%s ...\n", neo_entry->escopo, $ID);
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
  SymEntry* old_entry = last_decl(&reshi, $ID);
  // printf("Recuperado da tabela de simbolos: %p\n", old_entry);
  
  char err = 0;
  if(old_entry) {
    if( !strcmp(old_entry->escopo, currScope) ) {
      ERRSHOW(printf("[Semantico] Erro: Redeclaracao de %s:%s!\n", old_entry->escopo, old_entry->id));
      err = 1;
    }
    else {
      printf("\tDeclaracoes sob escopos distintos.\n");
    }
  }

  if (!err) {
    if ($num->type != TYPE_INT) {
      ERRSHOW(printf("[Semantico] Erro: Tamanho de vetor deve ser um inteiro! Encontrado: %s\n", t2s($num->type)));
      $$ = NULL;
      // TODO: add robusteza :/
    }  else if ($num->ival < 0) {
      ERRSHOW(printf("[Semantico] Erro: Tamanho deve ser >= 0\n"));
    }  else {   // DEU TUDO CERTO! 
      SymEntry* neo_entry = add_entry(&reshi, $ID, TAG_UNDEFINED);
      Type type = $BASE_TYPE == TYPE_FLOAT ? TYPE_ARRAY_FLOAT : TYPE_ARRAY_INT;
      if(neo_entry) {
        // TODO: checar se num eh inteiro. Se nao for, ERRO
        neo_entry->type = type;
        neo_entry->base_type = $BASE_TYPE;
        neo_entry->col = $num->ival;      
        MAKE_NODE(typeAndNameSign);
        // para facilitar geracao de codigo
        point_no_symentry(&neo_entry, &$$);
        add_Node_Child_If_Not_Null($$, Token_New("BASE_TYPE", t2s($BASE_TYPE)));
        add_Node_Child_If_Not_Null($$, Token_New("ID", $ID));
        link_symentry_no(&neo_entry, &$$->child_last);

        int sz = yyvsp[-1].no->ival;
        // char* e = get_no_addr();
        if(neo_entry->is_global) {
          GLOBALSHOW(
            printf("%s %s = {", t2s(to_base_type( neo_entry->type )),neo_entry->id);
            for(int i = 0; i < sz-1; i++) {
              printf("0, ");
            }
            printf("0 }\n");
          );
        }
        else {          
          char* e = get_no_addr( $$->child_last );
          CODESHOW(printf("mema %s, %d\n", e, sz)); 
          free(e);
        }

        add_Node_Child_If_Not_Null($$, $num);
      }
      else {
        printf("[BASE_TYPE ID '[' num ']'] ERRO LOGICO: NAO DEVERIA ENTRAR AQUI! %s:%s ...\n", neo_entry->escopo, $ID);
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
  SymEntry* old_entry = last_decl(&reshi, $ID);
  // printf("Recuperado da tabela de simbolos: %p\n", old_entry);
  
  char err = 0;
  if(old_entry) {
    if( !strcmp(old_entry->escopo, currScope) ) {
      ERRSHOW(printf("[Semantico] Erro: Redeclaracao de %s:%s!\n", old_entry->escopo, old_entry->id));
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
        ERRSHOW(printf("[Semantico] ERRO[2]: Quantidade de linhas de matriz deve ser um inteiro. (%s encontrado)\n", t2s($5->type)));
      }
      if(secNum) {
        ERRSHOW(printf("[Semantico] ERRO[2]: Quantidade de colunas de matriz deve ser um inteiro. (%s encontrado)\n", t2s($8->type)));
      }
      $$ = NULL;
    }
    else {    // TUDO CERTO: PODE CIRAR O NOH
      Type type = $BASE_TYPE == TYPE_FLOAT ? TYPE_MAT_FLOAT : TYPE_MAT_INT;
      SymEntry* neo_entry = add_entry(&reshi, $ID, TAG_UNDEFINED);
      if(neo_entry) {
        neo_entry->line = $5->ival;
        neo_entry->col = $8->ival;
        neo_entry->type = type;

        // TODO: checar se num eh inteiro. Se nao for, ERRO
        MAKE_NODE(typeAndNameSign);
/*  */
        point_no_symentry(&neo_entry, &$$);
        add_Node_Child_If_Not_Null($$, Token_New("BASE_TYPE", t2s($BASE_TYPE)));
        add_Node_Child_If_Not_Null($$, Token_New("ID", $ID));
        link_symentry_no(&neo_entry, &$$->child_last);

        int sz = yyvsp[-4].no->ival * yyvsp[-1].no->ival;
        // char* e = get_no_addr();
        if(neo_entry->is_global){
          GLOBALSHOW(
            printf("%s %s[%d] = {", t2s(to_base_type( neo_entry->type )),neo_entry->id, sz);
            for(int i = 0; i < sz-1; i++) {
              printf("0, ");
            }
            printf("0 }\n");
          );

        }
        else {          
          char* e = get_no_addr( $$->child_last );
          CODESHOW(printf("mema %s, %d\n", e, sz)); 
          free(e);
        }
        add_Node_Child_If_Not_Null($$, yyvsp[-4].no);
        add_Node_Child_If_Not_Null($$, yyvsp[-1].no);

/*  */

        // para facilitar geracao de cohdigo
        link_symentry_no(&neo_entry, &$$);
        $$->type = neo_entry->type;
      }
      else {
        printf("[BASE_TYPE ID '[' num ']'] ERRO LOGICO: NAO DEVERIA ENTRAR AQUI! %s:%s ...\n", neo_entry->escopo, $ID);
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
  // child_last eh usado como auxiliar para criar a lista na ordem correta ;)
  $1->child_last = NULL;
  $$ = $1;
  // printf("[paramListVoid] %p\n", $paramListVoid);
  // printf("[paramListVoid->type] %s\n", t2s($paramListVoid->type));

}
| %empty {$$ = NULL;}

paramList : paramList ',' param {
  // Para mantes a ordem correta dos parametros
  if(!$1->has_aux) {
    $1->has_aux = 1;
    $1->next_aux = $param;
    $1->child_last = $param;
  }
  else {
    $1->child_last->next_aux = $param;
    $1->child_last = $param;
  }
  $$ = $1;
}
| param 

param : BASE_TYPE ID {
  $$ = Token_New(STR(param), $ID);
  $$->is_param = 1;
  SymEntry* neo_entry = last_decl(&reshi, $ID);
  if(!declared_curr_fun) {
    SymEntry* neo_entry = add_entry(&reshi, $ID, TAG_PARAM);
    if(neo_entry) {
      neo_entry->type =  $BASE_TYPE;
      $$->type =  $BASE_TYPE;
      PARAM_RPT_NAME_CHECK(-1, 0);
    }
  }
  $$->type = $BASE_TYPE;
  free($ID), $ID = NULL;
}
| BASE_TYPE ID '[' ']' {
  $$ = Token_New(STR(param), $ID);
  $$->is_param = 1;
  // TODO: checar por declaracao previa de parametro!
  SymEntry* neo_entry = add_entry(&reshi, $ID, TAG_PARAM );
  // SEMANTICO
  PARAM_RPT_NAME_CHECK(-3, -2);
  
  if($BASE_TYPE == TYPE_INT)    neo_entry->type = TYPE_ARRAY_INT;
  else if ($BASE_TYPE == TYPE_FLOAT) neo_entry->type = TYPE_ARRAY_FLOAT;
  else if ($BASE_TYPE == TYPE_CHAR) neo_entry->type = TYPE_ARRAY_CHAR;
  else {
    ERRSHOW(printf("BASE_TYPE deve mao identificado\n"));
    neo_entry->type = TYPE_UNDEFINED;
  }
  $$->type = neo_entry->type;  // IMPORTANTE
  if(neo_entry)
    link_symentry_no(&neo_entry, &$$);
  free($ID), $ID = NULL;
}

| MAT_TYPE BASE_TYPE ID {
  // TODO: checar por declaracao previa de parametro!
  
  $param = Token_New(STR(param), $ID);
  DBG(printf("%p eh parametro!\n id == %s\n", $param, $ID));
  $$->is_param = 1;
  
  SymEntry* neo_entry = add_entry(&reshi, $ID, TAG_PARAM);
  // enderecos para os dois temporarios que guardam tamanho da matriz!
  // IMPORTANTE CHAMAR DEPOIS de ter inserido na tabela de simbolos
  temp_next();
  temp_next();

  // Semantico
  PARAM_RPT_NAME_CHECK(-1, 0);
  Type tipo;
  switch($BASE_TYPE) {
    case TYPE_CHAR: tipo = TYPE_MAT_CHAR; break;
    case TYPE_INT: tipo = TYPE_MAT_INT; break;
    case TYPE_FLOAT: tipo = TYPE_MAT_FLOAT; break;
  }
  $$->type = tipo;
  neo_entry->type = tipo;

  if($BASE_TYPE == TYPE_INT) neo_entry->type = TYPE_MAT_INT;  
  else if ($BASE_TYPE == TYPE_FLOAT) neo_entry->type = TYPE_MAT_FLOAT;
  else if ($BASE_TYPE == TYPE_CHAR) neo_entry->type = TYPE_MAT_CHAR;
  else {
    ERRSHOW(printf("BASE_TYPE deve mao identificado\n"));
    neo_entry->type = TYPE_UNDEFINED;
  }
  if(neo_entry)
    link_symentry_no(&neo_entry, &$$);  
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
  // $rvalue->is_arg = 1;
  MAKE_NODE(localStmt);
  add_Node_Child_If_Not_Null($$, $lvalue);
  add_Node_Child_If_Not_Null($$, $rvalue);  
  char* leftAddr, *rightAddr = NULL;
  leftAddr = get_no_addr($lvalue);

  Type t1 = $lvalue->type, t2 = $rvalue->type;
  if(t2 == TYPE_LIST || t2 == TYPE_LIST_LIST) {
    WARSHOW("Divida: nao foi implementado inicalizacao com vetor\n");
    
  }
  Type c1 = Type_Class(t1), c2 = Type_Class(t2);
  const char* s1 = t2s(t1), *s2 = t2s(t2);
  
  /*   BoldGray();
  printf("%s -- %s\n", s1, s2);
  Reset();*/

  // ################# VAI VIRAR FUNCAO
  if(t1 == TYPE_UNDEFINED || t2 == TYPE_UNDEFINED ||
    to_base_type(t1) == TYPE_CHAR || to_base_type(t1) == TYPE_CHAR) {
    ERRSHOW(printf("Erro: UNDEFINED/char em atribuicao: %s = %s\n", s1, s2));
  } else if (c1 == TYPE_ARRAY || c2 == TYPE_ARRAY) {
    ERRSHOW("Proibido operar com array!\n");
  } else if(c1 == c2) {
    if(t1 < t2) {
      ERRSHOW(printf("Nao eh possivel a atribuicao %s = %s : narrow casting\n", s1, s2));    
      rightAddr = "impossivel";
    } else {  // t1 > t2 e c1 eh matriz OU scalar
      if ( c1 == TYPE_MAT  ) {
        if(t1 > t2) {
          WARSHOW(printf("Conversao entre matrizes. %s = %s\n", t2s(t1), t2s(t2)));

          SymEntry* sym = $rvalue->sym_entry;

          BLUE("AQUI O CAST DE MATRIZES\n");
          CODESHOW(printf("param %s\n", get_no_addr($rvalue)));
          char* m_sz = get_mat_size($rvalue);
          CODESHOW(printf("param %s\n", m_sz ));    free(m_sz);
          CODESHOW(printf("call mat_i2f_temp, 2\n"));
          int temp = temp_next();
          CODESHOW(printf("pop $%d\n", temp));

          BLUE("END CAST\n");
          // PAra todos os efeitos, seu endereco antigo nao eh mais conhecido
          // printf("gogogo ! %d\n", temp);
          $rvalue->addr = temp;
          // abort();
          rightAddr = get_no_addr($rvalue);

          CODESHOW(printf("param $%d    // src\n", temp));
          CODESHOW(printf("param %s    // dest\n", get_no_addr($lvalue)));
          CODESHOW(printf("param %s    // qtd \n", get_mat_size($rvalue)));
          CODESHOW(printf("call __copyN, 3\n"));
        } else {  // soh mover (copiar), n precisa converter nada.
          WARSHOW(printf("no casts\n"));
          CODESHOW(printf("param %s    // src\n", get_no_addr($rvalue)));
          CODESHOW(printf("param %s    // dest\n", get_no_addr($lvalue)));
          CODESHOW(printf("param %s    // qtd \n", get_mat_size($rvalue)));
          CODESHOW(printf("call __copyN, 3\n"));
        }
      }
      else {  // converter de int -> float
        CODESHOW(printf("FAZER CONVERSAO FLOAT <--- INT\n"));

      }
    }
  } else {
    ERRSHOW(printf("Proibido operar em classes distintas (%s = %s)\n", s1, s2));
  }
  
  // FIM PARTE DO CAST

  // INICIO PARTE DO MOV
  if(c1 != c2) {
    ERRSHOW(printf("Nao permite-se atribuicao entre elementos de classes distintas\n"));
  }
  else {
    if( c1 == TYPE_MAT ) {  // supor que eh matriz
      // abort();
    } else if (c1 == TYPE_SCALAR) {
        rightAddr = get_no_addr($rvalue);
        CODESHOW(pf("mov %s, %s\n", leftAddr, rightAddr));
        free(rightAddr);
    }
    else {
      ERRSHOW(printf("Atribuicao entre vetores nao eh permitida!"));
    }

  }
  // ################# VAI VIRAR FUNCAO
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
    ERRSHOW(printf("[Semantico] Erro: Leitura de inteiro sobre tipo |%s|\n", t2s($lvalue->type)));
  }
}
| FREAD '(' lvalue ')' ';' {
  MAKE_NODE(localStmt);
  No* fread_no = Token_New("FREAD","FREAD");
  add_Node_Child_If_Not_Null($$, fread_no);
  add_Node_Child_If_Not_Null($$, $lvalue);
  if($lvalue->type != TYPE_FLOAT) {
    ERRSHOW(printf("[Semantico] Erro: Leitura de inteiro sobre tipo |%s|\n", t2s($lvalue->type)));
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

newFlowControl : countFlow
 flowControl {
   $$ = yyvsp[0].no;
   __new_flow--;
   if($flowControl != NULL && !strcmp($flowControl->tname, "flowControl") )
    LABELSHOW(printf("__endFlow%d:\n", $countFlow->ival));
}
countFlow : %empty {
  $$ = No_New( newFlow_counter );
  closest_flow = newFlow_counter;
  newFlow_counter++;
  // LABELSHOW(printf("__newFlow%d:\n", $$->ival ));
}
flowControl :  IF '(' expr ')' {
    if(yyvsp[-4].no->sval == NULL && yyvsp[-4].no->sval == NULL) {
      LABELSHOW(printf("__newFlow%d:\n", yyvsp[-4].no->ival ));
    }
    
    char* expr_addr = get_no_addr($expr);
    $1 = No_New(if_counter);
    if_counter++;

    CODESHOW(printf("brz __afterIfBlock%d, %s\n", $1->ival, expr_addr));
    free(expr_addr);    
  } block {
    CODESHOW(printf("jump __endFlow%d\n", closest_flow ) ) ;
    WARSHOW( printf("__afterIfBlock%d:\n",  $1->ival) );
  }
  ELSE flowControl {
      MAKE_NODE(flowControl);
      add_Node_Child_If_Not_Null($$, Token_New("IF","if"));
      add_Node_Child_If_Not_Null($$, $expr);
      add_Node_Child_If_Not_Null($$, $block);
      add_Node_Child_If_Not_Null($$, Token_New("ELSE","else"));
      add_Node_Child_If_Not_Null($$, yyvsp[0].no);
      LABELSHOW(printf("__afterElseBlock%d:\n", $1->ival ) ) ;

      No_Destroy($1); // usado como temporario (pilha)
    }
// block e ';' foram movidos para cah de modo a nao haver conflito na gramatica
| block {
  closest_flow--;
}
| ';' {
  $$ = NULL;
  closest_flow--;
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
| IF '(' error ')' {} block {
  printf("Erro : IF ( error ) block ELSE block\n");
  printf("Expressao mal formada\n");  
  $$ = NULL; 
}
loop : WHILE {
  $WHILE = No_New(while_counter);
  while_counter++;
  LABELSHOW(printf("__newWhile%d:\n", $WHILE->ival));
}'(' expr ')' {
  char* e = get_no_addr($expr);
  CODESHOW(printf("brz __endWhile%d, %s\n", $WHILE->ival ,e));
  free(e);
} block {
  MAKE_NODE(loop);
  add_Node_Child_If_Not_Null($$, Token_New("WHILE","while"));
  add_Node_Child_If_Not_Null($$, $expr);
  add_Node_Child_If_Not_Null($$, $block);
  CODESHOW(printf("jump __newWhile%d\n", $WHILE->ival));
  LABELSHOW(printf("__endWhile%d:\n", $WHILE->ival));
}

defFun : BASE_TYPE ID '('{

  new_context();
  FUNLABEL(printf("%s:\n", $ID));
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
    SymEntry* neo_entry = add_entry(&reshi, $ID, TAG_DEF_FUN);
    if(!neo_entry) {
      printf("Erro na definicao de funcao %s [bug]\n", $ID);
    }
    else {
      neo_entry->type = $BASE_TYPE;
      neo_entry->def_fun = 1;
    }
  }
  currScope = $ID;
} paramListVoid ')' '{' declList localStmtList '}' {
  // printf("%p ====== paramListVoid\n", $paramListVoid);
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
        fprintf(stderr,"entry->ast_node: %p, $paramListVoid: %p \n", entry->ast_node, $paramListVoid);
        int match = match_paramList(entry->ast_node->param, $paramListVoid);
        if(match > 0){
          printf("DEFINICAO de %s BATE COM DECLARACAO!\n", $ID);
          // TODO: ATUALIZAR NOME DOS PARAMETROS PARA QUANDO FOR USAR A FUNCAO,
          // CONTAR OS NOMES DOS PARAMETROS USADOS NA DEFINICAO
          // SymEntry* neo_entry = add_entry(&reshi, $ID, TAG_DEF_FUN);
          // neo_entry->type = $BASE_TYPE;
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
    // printf("PARAM BECOME %p\n", $$->param);
    link_symentry_no(&tmp, &$$);
  }
  else
    aborta = 0;
  No* _BASE_TYPE = Token_New(STR(BASE_TYPE), t2s($BASE_TYPE));
  No* _ID = Token_New(STR(ID), $ID);
  add_Node_Child_If_Not_Null($$, _BASE_TYPE);
  add_Node_Child_If_Not_Null($$, _ID);
  add_Node_Child_If_Not_Null($$, $paramListVoid);
  add_Node_Child_If_Not_Null($$, $declList);
  add_Node_Child_If_Not_Null($$, $localStmtList);  
  def_fun_rule = 0;
  currScope = GLOBAL_SCOPE;
  free($ID);$ID = NULL;
  if($BASE_TYPE == TYPE_INT) {
    CODESHOW(printf("return 0\n"));
  }
  else if($BASE_TYPE == TYPE_FLOAT) {
    CODESHOW(printf("return 0.0\n"));
  }
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
  e2_addr = get_no_addr(e2);
  e1_addr = get_no_addr(e1);
  e_addr = get_no_addr(e);
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
  // DBG(printf("RESULT TYPE: %s", t2s(e->type)));
  // DBG(printf(" from: %s + %s\n", t2s(e1->type), t2s(e2->type)));
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
  if($1->type == TYPE_INT && $3->type == TYPE_INT) {
    char *addr1 = get_no_addr($1), *addr2 = get_no_addr($3);
    CODESHOW(printf("mod $%d, %s, %s\n", temp_next() ,addr1, addr2));
  } else {ERRSHOW(printf("mod com operandos nao inteiros! %s %% %s",
    t2s($1->type), t2s($3->type)));}
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
  e2_addr = get_no_addr(e2);
  e1_addr = get_no_addr(e1);
  e_addr = get_no_addr(e);

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
  e2_addr = get_no_addr(e2);
  e1_addr = get_no_addr(e1);
  e_addr = get_no_addr(e);

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
      printf("[Semantico] Erro: nao pode converter nao-escalar (e.g %s) para inteiro.\n", t2s($3->type))
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
      t2s($3->type)));
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
  // fprintf(stderr,"type of %s: %s\n", $ID, t2s(aux->type));
  // fprintf(stderr,"%s 1st param: %p\n", $ID, aux->ast_node->param);
  // fprintf(stderr,"type of %s param: %s\n", $ID, t2s(aux->ast_node->param->type));
  if(!aux){
    printf("Funcao %s, l.%d c.%lu nao declarada!\n", $ID, numlines, currCol - (strlen($ID) + 2));
  }
  else{
    $$->type = aux->type;
    if(is_fun (aux->tag)) {
      // printf("%s eh uma funcao!.\n", aux->id);
      // Ver se assinatura bate com a declaracao!
      if(aux->ast_node) {
        int match = match_paramList(aux->ast_node->param, $argList);
        if(match > 0) {
          printf("[++++Semantico++++] Argumentos de %s corretos\n", $ID);
          CODESHOW(printf("call %s, %d\n", $ID, $argList->ival));
          // Gambiarra para marcar todos os argumentos como has_aux;
          // gambiarra pq nao parece nada legal, mas deve funcionar

          // No* tmp = 

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
      printf("\t ast_node: %p!.\n", aux->ast_node);
      // Ver se assinatura bate com a declaracao!
      int match = match_paramList(aux->ast_node->param, NULL);
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
  $1->is_arg = 1;
  if(!$1->has_aux) {
    $1->has_aux = 1;
    $1->next_aux = $arg;
    $1->child_last = $arg;
  }
  else {
    $1->child_last->next_aux = $arg;
    $1->child_last = $arg;
  }
  $$ = $1;
  $$->ival += 1;
}
| arg {
  $$ = $1;
  $$->has_aux = 0;
  $$->is_arg = 1;
}

arg : lvalue {
  assert( $lvalue->sym_entry );
  // printf("arg $%d (%s)\n", $1->sym_entry->addr, $1->sym_entry->id);
  $$ = $1;
  SymEntry * sym = $lvalue->sym_entry;
  sym->is_arg = 1;
  $$->is_arg = 1;
}
| ID '(' expr ')' '(' expr ')' {
  SymEntry* entry = last_decl(&reshi, $ID);
  // printf("arg $%d (%s)\n", entry->addr, entry->id);
  assert( entry );
  assert( entry->ast_node);
  // BoldCyan();

/*   if(entry->is_global)
    printf("param %s\n", entry->id);
  else
    printf("param $%d\n", entry->addr);
 */
  char *e = get_no_addr( entry->ast_node );
  
  CODESHOW(printf("param %s\n", e));
  // Empilhar dimensoes da matriz
  e = get_no_addr($3);
  CODESHOW(printf("param %s\n", e)); free(e);
  e = get_no_addr($6);
  CODESHOW(printf("param %s\n", e)); free(e);
  Reset();

  MAKE_NODE(arg);
  $$->type = entry->type;
  $$->is_arg = 1;
  entry->is_arg = 1;

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
      printf("argType: %s\n", t2s($$->type));
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
  // SHOWGRAY(printf("%s is arg? %d", $ID, entry->is_arg));
  if(entry) {
    if(is_fun(entry->tag)) {
      printf("Identificador %s, l.%d c.%lu DECLARADO PREVIAMENTE como funcao em l.%d, c.%d!\n",
       $ID, numlines, currCol - (strlen($ID) + 2), entry->local.line, entry->local.col);
    }
    else {
      point_no_symentry(&entry, &$$);
      point_no_symentry(&entry, &tok);
      $$->type = entry->type;
      // $$->is_arg = 
      // DBG(printf("lvalue %s type: %s\n", $ID, t2s($$->type)));
    }
  }
  else {
    $$->type = TYPE_UNDEFINED;
    printf("Variavel %s, l.%d c.%lu nao declarada!\n", $ID, numlines, currCol - (strlen($ID) + 2));
  }
  // printf("lvalue->type=%s \n", t2s( $$->type ));
  free($ID), $ID = NULL;
  assert($$->sym_entry);
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
      $$->sym_entry = old;
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
      tok->sym_entry = old;      
    }
  }
  free($ID); $ID = NULL;
  assert($$->sym_entry);
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
  printf("old->ast_node: %p\n", old->ast_node);
  CODESHOW(printf("mov $%d, %s\n", temp, get_no_addr(old->ast_node)));

  CODESHOW(printf("mul $%d, %s, %d\n", temp = temp_next(), get_no_addr($3), old->col  ));
  
  CODESHOW(printf("add $%d, $%d, %s\n", temp, temp, get_no_addr($6)));
  temp = temp_next();
  CODESHOW(printf("mov $%d, $%d[$%d]\n", temp,temp-2 , temp-1));
  $$->addr = temp;
  free($ID); $ID = NULL;
  assert($$->sym_entry);
}

rvalue : expr
| '{' numList '}' {
  $$ = $2;
  $$->type = TYPE_LIST;
  No* expr = yyvsp[0].no;
  if(expr->sym_entry)
    point_no_symentry(&(expr->sym_entry), &$$);
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
  print_reshi(reshi);
  yylex_destroy();
  
  // delete_all(reshi);
  free_All_Child(root);
}