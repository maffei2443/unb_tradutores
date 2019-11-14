#ifndef SEMANTIC_CHECKER_H
#define SEMANTIC_CHECKER_H
#include "Tree.h"

int match_paramList(SymEntry* sym, No* no);
void link_symentry_no(SymEntry* sym, No* no);
Type bin_expr_type(Type left, Type right, int op);
SymEntry* add_entry(SymEntry** reshi, char* id, int tag);
SymEntry* was_declared(SymEntry** reshi, char* id);

// Retorna TRUE sse n-esimos parametros dao match com os
// n-esimos parametros



int match_decl();


int id_has_type(SymEntry** reshi, char* id, Type type);
int can_cast(Type t1, Type t2);

void addToDel(SymEntry** p);
void delGambs();

#endif