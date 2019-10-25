#ifndef _TREE_H_
#define _TREE_H_

#include <stdio.h>
#include <stdlib.h>
#define ptfi(str, val) printf(str " %d\n",  (val))

typedef struct No {
  struct No * child;
  struct No * childLast;
  struct No * n;
  struct No * p;
  char* sval;
  int v;
} No;

// Ok.
No* No_New(int v);
void show_Spaces(int qtd);
// Seta ponteiros internos de variavel do tipo No
// para NULL. Depois, dah free nessa variavel.
void No_Destroy(No* no) ;

void show_Lis(No* head) ;


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
int show_Sub_Tree(No* no, int lvl);

#endif