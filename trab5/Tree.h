#ifndef _TREE_H_
#define _TREE_H_
#ifdef NULL
  #undef NULL
  #define NULL ((void *)0)
#endif
#include <stdio.h>
#include <stdlib.h>
#include "Array.h"
#include "code_gen.h"
#include "uthash.h"
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

typedef struct SymEntry{
  
  char id[257];
  short int temp_num;   // numero usado para quando se for salvar seu valor/endereço, escolher o temporario associado
  Tag tag;
  Type type;  // nao ideal, MAS fica mais facil...
  Type base_type;
  char* escopo;
  Local local;
  char def_fun;
  int line, col;
  struct No* astNode;
  struct SymEntry* next; // encadeamento para caso de conflito
  UT_hash_handle hh;
  short local_pos;
  // numero utilizado para localizacao da variahvel no escopo local!
  // Deve comecar em 0 para cada escopo
} SymEntry;

typedef struct No {
  // struct No * p;   // ponteiro para pai
  struct No * child;
  struct No * childLast;
  struct No * n;
  struct No * nextAux;
  struct No * param;  // usado apenas por entradas representando FUNCOES
  SymEntry* symEntry;

  char* sval;
  int ival;
  int iaux;
  float fval;
  
  //  Indica tipo do no (ex: expr, param, loop...)
  char* tname;        
  char is_const;
  char sval_alloc;
  char tname_alloc;
  char code_alloc;
  Type type;
  char isToken;    // nesse modo, usa-se mesmo noh para token e regra
  char hasAux;
  Code* code;
} No;

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
void free_Lis(No* no) ;

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
char* type2string(Type t);

void print_reshi(SymEntry*);
void show_entry(SymEntry*);

#endif