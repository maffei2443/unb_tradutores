#ifndef _TREE_H_
#define _TREE_H_

#include <stdio.h>
#include <stdlib.h>
#define ptfi(str, val) printf(str " %d\n",  (val))

typedef enum {
  IVAL  = 0,
  SVAL,
  TVAL
} Field;

typedef enum {
  TYPE_INT = 1,
  TYPE_FLOAT = 2,
  TYPE_CHAR = 4,
  TYPE_ARRAY = 8,
  TYPE_MAT = 16
}Type;

typedef struct No {
  struct No * child;
  struct No * childLast;
  struct No * n;
  struct No * p;
  char* sval; char sval_alloc;
  char* tname; char tname_alloc;
  char isToken;    // nesse modo, usa-se mesmo noh para token e regra
  int ival;
} No;

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
void add_Node_Child(No* no, No * newNo);
// Adiciona novo irmao para no.
// LIMITACAO: no DEVE TER UM PAI!
// Motivo: insercao RAPIDA!
void add_Next(No* no, int v) ;


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

#endif