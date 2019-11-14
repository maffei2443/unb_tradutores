#ifndef SEMANTIC_CHECKER_H
#define SEMANTIC_CHECKER_H
#include "Tree.h"

Type bin_expr_type(Type left, Type right, int op);

SymEntry* add_entry(SymEntry** reshi, char* id, int tag);
SymEntry* was_declared(SymEntry** reshi, char* id);
void addToDel(SymEntry** p);
void delGambs();

#endif