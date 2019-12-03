#ifndef SEMANTIC_CHECKER_H
#define SEMANTIC_CHECKER_H
#include "Tree.h"

int match_paramList(No* , No*);
void link_symentry_no(SymEntry** sym, No** no);
Type bin_expr_type(Type left, Type right, int op);

static Type expr_mod(Type, Type);
static Type expr_add(Type, Type);
static Type expr_sub(Type, Type);
static Type expr_mul(Type, Type);
static Type expr_div(Type, Type);
static Type expr_mat_mul(Type, Type);
static Type expr_mat_pow(Type, Type);
static Type expr_bool(Type, Type, int op);
static Type expr_attr(Type, Type);

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

void delBLUE();

void mensagem_redeclaracao(SymEntry* s);

void delete_all(SymEntry* tab);
#endif