#include "SemanticChecker.h"
#include "new_grammar.tab.h"
#include "Common.h"
extern int temp;    // usado para enumerar os temporarios. Deve ser zerado e restaurado cada vez que entra em definicao de funcao
extern char* currScope;
extern char* GLOBAL_SCOPE;
extern int numlines;
extern int currCol;

int gambs_tam = 0;
int gambs_qtd = 0;

SymEntry** gambs;
// Retorna 1 se a lista da match.
// -2 se ambos sao NULL
// -1 se noh eh NULL
// TODO: FIX IT
int match_paramList(No* oldParam, No* param) {
  // printf("sym: %p vs no: %p\n", sym, no);
  if(!oldParam && !param) return 1;   // ambas funcoes sem argumento
  if(!oldParam || !param) return 0;   // apenas 1 eh sem argumento
  // printf("oldParam: %p vs param: %p\n", oldParam, param);
  // printf("oldParam: %s vs param: %s OK\n", type2string(oldParam->type), type2string(no->type));
  printf("%s vs %s\n", type2string(oldParam->type), type2string(param->type));
  printf("%s vs %s\n", oldParam->sval, param->sval);
  while (oldParam && param){
    if(oldParam->type != param->type)
      break;
    else {
      printf("pametro igual!\n");
      // Alterar os ponteiros por fora, aqui nao estah dando nada certo.
    }
    oldParam = oldParam->nextAux;
    param = param->nextAux;
  }
  printf("OK, FOI mach_paramList\n");
  return !oldParam && !param;
}

void link_symentry_no(SymEntry** sym, No** no) {
  assert(*no && *sym);
  // printf("(BI directional) linking... ( %p )%s <--> %p\n", *sym,(*sym)->id, *no);
  (*no)->symEntry = *sym;
  (*sym)->astNode = *no;
  // fprintf(stderr, "\t[link_symentry_no]\t %p %p\n", *sym, *no);	  // fprintf(stderr, "\t[link_symentry_no]\t %p %p\n", *sym, *no);
}


// Utilizado em caso de utilização MAS nao de declaracao de variavel local
void point_no_symentry(SymEntry** sym, No** no) {
  assert(*no && *sym);
  // printf("(UNI directional) linking... %s <--> %p\n", (*sym)->id, *no);
  (*no)->symEntry = *sym;
  (*no)->type = (*sym)->type;
}

/* 
void set_type_and_uni_link(SymEntry** old, No** tok) {
    (*tok)->type = (*old)->type;
    point_no_symentry(old, tok);
}
*/


//  Retorna TYPE_UNDEFINED nos casos:
// - left/right ser TYPE_UNDEFINED
// - left/right ser TYPE_VOID
// - left/right ser TYPE_ARRAY
// - expressão mal formada como por exemplo divisão de 
// escalar por matriz
Type bin_expr_type(Type left, Type right, int op) {
  printf("\n[bin_expr_type] tipos:  = %s <<%c>> %s\n", type2string(left),op, type2string(right));
  Type leftClass = Type_Class(left);
  Type rightClass = Type_Class(right);
  if(left == TYPE_CHAR || right == TYPE_CHAR){
    printf("[Semantico] ERRO: TIPO CHAR NAO PODE SER USADO PARA REALIZACAO DE OPERACOES\n");
    return TYPE_UNDEFINED;
  }
  if(left == TYPE_UNDEFINED || right == TYPE_UNDEFINED) return TYPE_UNDEFINED;// erro de inicializacao...
  else if(left == TYPE_VOID || right == TYPE_VOID ) return TYPE_VOID;// tentando usar retorno de funcao VOID
  else if(leftClass == TYPE_ARRAY || rightClass == TYPE_ARRAY) return TYPE_UNDEFINED;
  // NAO SE PODE OPERAR SOBRE ARRAYS.
  printf("**** %s %s\n\n", type2string(leftClass), type2string(rightClass));  
  switch (op)  {
    case '%': 
      if(left == right && left == TYPE_INT) return TYPE_INT;
      else return TYPE_UNDEFINED;
    case '+': case '-':
      if(leftClass == rightClass) return max(left, right);
      else if(leftClass == TYPE_SCALAR && rightClass == TYPE_MAT) return right;
      else {
        return TYPE_UNDEFINED;
      }
    case '*':
      if(leftClass == rightClass) max(left, right);
      else if(leftClass == TYPE_SCALAR && rightClass == TYPE_MAT) return right;
      else return TYPE_UNDEFINED;
    case '/':
      if(leftClass == rightClass) max(left, right);
      else if(leftClass == TYPE_MAT && rightClass ==  TYPE_SCALAR ) return left;
      else return TYPE_UNDEFINED;
    case '@':
      if(leftClass == TYPE_MAT && rightClass == TYPE_MAT) return max(left, right);
      else return TYPE_UNDEFINED;
      /* code */
    case MAT_POW:
      if(leftClass == TYPE_MAT && rightClass == TYPE_SCALAR) {
        return left;
      }
      else
        return TYPE_UNDEFINED;
    case EQ:  case NEQ:
    case GE:  case LE:
    case '<':  case '>':
    case AND:  case OR:
      return left == right ? TYPE_INT : TYPE_UNDEFINED;
    default:
      printf("[Semantico] Expressao com tipos %s, %s e operacao %c sem tipo definido!",
        type2string(left), type2string(right), op); 
      return TYPE_UNDEFINED;
  }
}

// Retorna NULL caso nao o tenha sido;senao,
// retorna ponteiro para declracao mais prohxima.
SymEntry* last_decl(SymEntry** reshi, char* id){
  // fprintf(stderr, "[last_decl] para %s", id);
  SymEntry* oldEntry = NULL;
  SymEntry* last_same_id = oldEntry;
  HASH_FIND_STR((*reshi), id, oldEntry);
  while( oldEntry ) {
    if(strcmp(oldEntry->escopo, currScope) == 0){  // declaracao sob mesmo escopo
      // fprintf(stderr," retornou (%p, %s)\n", oldEntry, oldEntry->id);
      return oldEntry;
    }
    else if(strcmp(oldEntry->escopo, GLOBAL_SCOPE) == 0){  // mesmo nome e escopo global
      last_same_id = oldEntry;
    }
    oldEntry = oldEntry->next;
  }
  // fprintf(stderr, " retornou [outWhile] (%p, %s)\n", last_same_id, last_same_id->id);
  return last_same_id;
}
// TODO: diferenciar da funcao de cima!
int was_declared(SymEntry** reshi, char* id){
  SymEntry* oldEntry = NULL;
  SymEntry* last_same_id = oldEntry;
  HASH_FIND_STR((*reshi), id, oldEntry);
  while( oldEntry ) {
    if(strcmp(oldEntry->escopo, currScope) == 0){  // declaracao sob mesmo escopo
      return !!oldEntry;
    }
    else if(strcmp(oldEntry->escopo, GLOBAL_SCOPE) == 0){  // mesmo nome e escopo global
      last_same_id = oldEntry;
    }
    oldEntry = oldEntry->next;
  }
  return !!last_same_id;
}

SymEntry* add_entry(SymEntry** reshi, char* id, int tag) {
    SymEntry* neoEntry = NULL;
    HASH_FIND_STR((*reshi), id, neoEntry);/* id already in the hash? */
    if (neoEntry == NULL) {
      neoEntry = SymEntry_New(id, tag, currScope);
      if( !strcmp(currScope, GLOBAL_SCOPE) ) {
        neoEntry->is_global = 1;
        printf("\t\t%s eh GLOBAL!\n", id);
      } else {
        neoEntry->is_global = 0;
        neoEntry->addr = temp_next();
        printf("%s:%s com $%d associado\n", neoEntry->id, currScope, neoEntry->addr);

      }
      printf("\t\tNEO_ENTRY: %p\n", neoEntry);
      printf("<<<<<< add (%p) id, tag: %s, %s\n", neoEntry, id, type2string(tag));
      neoEntry->local.line = numlines;
      neoEntry->local.col = currCol;
      HASH_ADD_STR( (*reshi), id, neoEntry );/* id: name of key field */
    }
    else {    // Checar se eh declaracao no msm escopo. Se for, nao adiciona e dah pau (retorna NULL);
      printf("Possivel conflito com %s:%s\n", id, neoEntry->escopo);
      for(;neoEntry->next;neoEntry = neoEntry->next) {
        if(strcmp(id, neoEntry->id) == 0 && strcmp(currScope, neoEntry->escopo)) {
          printf("[Semantico1] Erro: redeclaracao de %s:%s em l.%d, r.%d\n",
            currScope, id, neoEntry->local.line, neoEntry->local.col);
          return NULL;
        }
      }
      if( strcmp(id, neoEntry->id) == 0 && !strcmp(currScope, neoEntry->escopo) ) {          
        if(tag == TAG_DEF_FUN && neoEntry->tag == TAG_DECL_FUN) {
          printf("Caso especial de declaracao previa de %s\n", id);
        }
        else
          printf("[Semantico2] Erro: redeclaracao de %s:%s em l.%d, r.%d\n",
            currScope, id, neoEntry->local.line, neoEntry->local.col);
        return NULL;
      }
      else {
        neoEntry->next = SymEntry_New(id, tag, currScope);
        printf(">>>>> add (%p) id, tag: %s, %s\n", neoEntry->next, id, type2string(tag));
        neoEntry->next->local.line = numlines;
        neoEntry->next->local.col = currCol;
        return neoEntry->next;
      }
    }
    return neoEntry;
}

int id_has_type(SymEntry** reshi, char* id, Type type) {
  SymEntry* sym = last_decl(reshi, id);
  if(!sym) return -1;
  assert(sym->type == sym->astNode->type);
  return sym->type == type;
}

// Retorna 1 de t1 pode ser promovido a t2, e 0 caso contrario
int can_cast(Type t1, Type t2) {
  
}


void delGambs() {
  printf("QTD : %d\n", gambs_qtd);
  for(int i = 0;i < gambs_qtd;i++){
    printf("id, addr: %s, %p\n", (gambs[i])->id, gambs[i]);
    SymEntry_Destroy(gambs[i]);
    gambs[i] = NULL;
  }
  if(gambs)
    free(gambs);
  gambs = NULL;
}

void delete_all(SymEntry* tab) {
  SymEntry *current_user, *tmp;

  HASH_ITER(hh, tab, current_user, tmp) {
    HASH_DEL(tab, current_user);  /* delete; users advances to next */
    printf("__calling__... %p\n", current_user);
    if (current_user)
      SymEntry_Destroy(current_user);            /* optional- if you want to free  */
  }
  // free(tab);
}
// msg_erros

void mensagem_redeclaracao(SymEntry* s) {
    printf("[Semantico] Identificador %s jah foi definida em l.%d, c.%d como nao-funcao!\n",
      s->id, s->local.line, s->local.col);
}