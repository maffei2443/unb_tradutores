#include "SemanticChecker.h"

extern char* currScope;
extern char* GLOBAL_SCOPE;

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