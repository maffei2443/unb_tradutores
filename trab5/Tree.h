#ifndef _TREE_H_
#define _TREE_H_
#ifdef NULL
  #undef NULL
  #define NULL ((void *)0)
#endif
#include <stdio.h>
#include <stdlib.h>
#include "Array.h"
#include "Common.h"

#include <assert.h>

#define ptfi(str, val) printf(str " %d\n",  (val))
#define DESTROY_PTR(ptr) {free(ptr);ptr = NULL;}
#define max(a,b)             \
({                           \
    __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a > _b ? _a : _b;       \
})

#define min(a,b)             \
({                           \
    __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a < _b ? _a : _b;       \
})

CommBlock comm_block;
LineComment lineComm;
Array currString;


int is_fun(Tag t);

Type Type_Class(Type type);


// Ok.
No* No_New(int v);

// not checked
// Recebe string com o VALOR do token.
// Aloca DINAMICAMENTE o valor em No->sval
No* Token_New(char* tname, char* sval);

void show_Spaces(int qtd);
// Seta ponteiros internos de variavel do tipo No
// para NULL. Depois, dah free nessa variavel.
void No_Destroy(No* no) ;

void show_Lis(No* head, Field field) ;


// TESTADO, FUNCIONA
void add_Child(No* no, int v) ;
void add_Node_Child_If_Not_Null(No* no, No * newNo);
void add_Node_Next(No* no, No* next) ;


// Pega proximo, libera atual.
// ... Ao final, atual serah o ultimo
// NO LEAKS, mas erros :/
void free_Param_Lis(No* no) ;

// Chama o "freelLis" para child,
// mas soh quando todos os childs jah o tiverem feito tambem.
// TESTADO, FUNCIONA
void free_All_Child(No * no) ;

// NAO TESTADO AINDA
int show_Sub_Tree(No* no, int lvl, Field field);
int ListSize(No* no);


// Should include another header except the default-ones
// extern int MAT_POW, EQ, NEQ, GE, LE, AND, OR;
SymEntry* SymEntry_New(char* id, int tag, char*);
void* SymEntry_Destroy(void*);
char* t2s(Type t);

void print_reshi(SymEntry*);
void show_entry(SymEntry*);

#endif