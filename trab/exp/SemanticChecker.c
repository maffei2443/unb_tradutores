#include "SemanticChecker.h"
#include "new_grammar.tab.h"
extern char* currScope;
extern char* GLOBAL_SCOPE;
extern int numlines;
extern int currCol;

int gambs_tam = 0;
int gambs_qtd = 0;

SymEntry** gambs;

int match_paramList(SymEntry* sym, No* no) {
  if(!sym || !no) return -1;
  No* oldParam = sym->astNode;
  No* param = no;
  while (oldParam && param){
    if(oldParam->type != param->type)
      break;
    oldParam = oldParam->nextAux;
    param = param->nextAux;
  }
  return !oldParam && !sym;
}


void link_symentry_no(SymEntry* sym, No* no) {
  sym->astNode = no;
  no->symEntry = sym;
}

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


// Retorna NULL caso nao o tenha sido;senao,
// retorna ponteiro para declracao mais prohxima.
SymEntry* was_declared(SymEntry** reshi, char* id){
  SymEntry* oldEntry = NULL;
  SymEntry* last_same_id = oldEntry;
  HASH_FIND_STR((*reshi), id, oldEntry);
  while( oldEntry ) {
    printf("old: %p, next: %p\n", oldEntry, oldEntry->next);
    if(strcmp(oldEntry->escopo, currScope) == 0){  // declaracao sob mesmo escopo
      return oldEntry;
    }
    else if(strcmp(oldEntry->escopo, GLOBAL_SCOPE) == 0){  // mesmo nome e escopo global
      last_same_id = oldEntry;
    }
    oldEntry = oldEntry->next;
  }
  return last_same_id;
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

int id_has_type(SymEntry** reshi, char* id, Type type) {
  SymEntry* sym = was_declared(reshi, id);
  if(!sym) return -1;
  assert(sym->type == sym->astNode->type);
  return sym->type == type;
}

// Retorna 1 de t1 pode ser promovido a t2, e 0 caso contrario
int can_cast(Type t1, Type t2) {
  
}

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
  if(gambs)
    free(gambs);
  gambs = NULL;
}
