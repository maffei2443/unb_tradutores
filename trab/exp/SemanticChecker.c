#include "SemanticChecker.h"

extern char* currScope;
extern char* GLOBAL_SCOPE;
extern int numlines;
extern int currCol;

int gambs_tam = 0;
int gambs_qtd = 0;

SymEntry** gambs;
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
