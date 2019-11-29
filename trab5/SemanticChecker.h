#ifndef SEMANTIC_CHECKER_H
#define SEMANTIC_CHECKER_H
#include "Tree.h"

int match_paramList(No* , No*);
void link_symentry_no(SymEntry** sym, No** no);
Type bin_expr_type(Type left, Type right, int op);
SymEntry* add_entry(SymEntry** reshi, char* id, int tag);
SymEntry* last_decl(SymEntry** reshi, char* id);
int was_declared(SymEntry** reshi, char* id);

// Retorna TRUE sse n-esimos parametros dao match com os
// n-esimos parametros

void link_symentry_no(SymEntry** sym, No** no);
void point_no_symentry(SymEntry** sym, No** no);
void set_type_and_uni_link(No* p, SymEntry* old, No* tok) ;

int id_has_type(SymEntry** reshi, char* id, Type type);
int can_cast(Type t1, Type t2);

void delGambs();

void mensagem_redeclaracao(SymEntry* s);

void delete_all(SymEntry* tab);
#endif