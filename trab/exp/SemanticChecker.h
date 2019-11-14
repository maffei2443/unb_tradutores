#ifndef SEMANTIC_CHECKER_H
#define SEMANTIC_CHECKER_H
#include "Tree.h"

SymEntry* add_entry(SymEntry** reshi, char* id, int tag);
SymEntry* was_declared(SymEntry** reshi, char* id);
void addToDel(SymEntry** p);
void delGambs();

#endif