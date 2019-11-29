#ifndef SEMANTIC_CHECKER_H
#define SEMANTIC_CHECKER_H
#include "Tree.h"

#define SET_TYPE_AND_UNI_LINK(old, tok) \
      tok->type = old->type; \
      yylval.no->type = old->type; \
      point_no_symentry(&old, &tok); \

int match_paramList(No* , No*);

// Usar quando DECLARA uma variavel.
void link_symentry_no(SymEntry** sym, No** no);

// Usar quando USA uma variavel DELCARADA
void point_no_symentry(SymEntry** sym, No** no);

void set_type_and_uni_link(No* p, SymEntry* old, No* tok);

Type bin_expr_type(Type left, Type right, int op);
SymEntry* add_entry(SymEntry** reshi, char* id, int tag, short int local_pos);
SymEntry* last_decl(SymEntry** reshi, char* id);
int was_declared(SymEntry** reshi, char* id);

// Retorna TRUE sse n-esimos parametros dao match com os
// n-esimos parametros


int id_has_type(SymEntry** reshi, char* id, Type type);
int can_cast(Type t1, Type t2);

void addToDel(SymEntry** p);
void delGambs();

void mensagem_redeclaracao(SymEntry* s);

void delete_all(SymEntry* tab);
#endif