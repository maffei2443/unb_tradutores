#ifndef _TREE_H_
#define _TREE_H_

#include <stdio.h>
#include <stdlib.h>
#include "Array.h"
#include "uthash.h"
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

typedef struct {
  int lines, isChar, notChar;
  int lineInit, colInit;
} CommBlock;
CommBlock comm_block;

typedef struct  {
  int lineInit,
      colInit,
      notChar,
      isChar;
} LineComment;
LineComment lineComm;

Array currString;
typedef struct {
  int line,
      col;
} StringStart;

typedef struct {
  int line, col;
} Local;

typedef enum {
  IVAL  = 0,
  SVAL,
  TVAL
} Field;

typedef enum {
  TYPE_INVALID = -2,
  TYPE_VOID = -1,
  TYPE_UNDEFINED = 0, 
  TYPE_INT = 1,
  TYPE_FLOAT = 2,
  TYPE_SCALAR = 3,
  TYPE_ARRAY_INT = 4,
  TYPE_ARRAY_FLOAT = 8,
  TYPE_ARRAY = 9,
  TYPE_MAT_INT = 16,
  TYPE_MAT_FLOAT = 32,
  TYPE_MAT = 33,
  TYPE_DECL_FUN = 60,
  TYPE_DEF_FUN = 61,
  TYPE_IF = 80,
  TYPE_PARAM = 100,
  TYPE_POINTER = 120,
}Type;

// Indica TIPO DA REGRA da entrada de simbolos

typedef struct SymEntry{
  char id[257];
  Type tag;
  Type type;  // nao ideal, MAS fica mais facil...
  char* escopo;
  Local local;
  char def_fun;

  union {
    int ival;
    char cval;
    float fval;
    struct {
      struct No* next;
      struct SymEntry* upperSym;
      struct SymEntry** nestedSym;
    } func;
  } u;
  struct No* astNode;
  struct SymEntry* next; // encadeamento para caso de conflito
  UT_hash_handle hh;
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
  float fval;
  
  //  Indica tipo do no (ex: expr, param, loop...)
  char* tname;        
  char is_const;
  char sval_alloc;
  char tname_alloc;
  Type type;
  char isToken;    // nesse modo, usa-se mesmo noh para token e regra
  char hasAux;
} No;

int is_fun(Type t);

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