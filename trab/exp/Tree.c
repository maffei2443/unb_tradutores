#include "Tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ptfi(str, val) printf(str " %d\n",  (val))

void show_Spaces(int qtd){
  char*  p = malloc(sizeof(char) * qtd+1);
  memset(p, ' ', qtd);
  p[qtd] = '\0';  
  printf("%s", p);
  free(p);  p = NULL;
}


// Ok.
No* No_New(int v) {
  No* no = (No*)malloc(sizeof(No));
  no->child = NULL; no->n = NULL;
  no->childLast = NULL; no->p = NULL;
  no->v = v; no->sval = NULL;
  return no;
}

// Seta ponteiros internos de variavel do tipo No
// para NULL. Depois, dah free nessa variavel.
// NAO TESTADO
void No_Destroy(No* no) {
  no -> n = NULL; no -> p = NULL;
  no -> child = NULL; no -> childLast = NULL;  
  if(no->sval == NULL) free(no->sval), no->sval = NULL;
  free(no);  no = NULL;
}

void show_Lis(No* head) {
  int i = 0;
  while(head) {
    // for(int a = 0; a < i; a++) printf(" ");
    i++;
    printf("%d ",(head)->v);
    head = (head)->n;
  }
  printf("\n");
}


// TESTADO, FUNCIONA
void add_Child(No* no, int v) {
  if(!no) {
    printf("Erro: %p eh NULO.\n", no);
    printf("Nao foi possivel adicionar um filho.\n");
    return;
  }
  No* neo = No_New(v);
  if( (no)->childLast != NULL ) {
    (no)->childLast->n = neo;
    (no)->childLast = neo;
  }else { // primeiro filho
    (no)->child = neo;
    (no)->childLast = neo;
  }
  neo->p = no;
}
// TODO: testar
void add_Node_Child(No* no, No * newNo) {
  if(!no) {
    printf("Erro: %p aponsta pra NULO.\n", no);
    printf("Nao foi possivel adicionar um filho.\n");
    return;
  }
  if( (no)->childLast != NULL ) {
    (no)->childLast->n = newNo;
    (no)->childLast = newNo;
  }else { // primeiro filho
    (no)->child = newNo;
    (no)->childLast = newNo;
  }
  (newNo)->p = no;
}
// Adiciona novo irmao para no.
// LIMITACAO: no DEVE TER UM PAI!
// Motivo: insercao RAPIDA!
void add_Next(No* no, int v) {
  if ((no)->p){  // printf("INSERIR VIA PAI\n");    
    return add_Child(no->p, v);
  }
  else {  
    printf("[ERRO]O elemento PRECISA ter um pai.\n");    printf("Atribua-lhe um pai paa insercao mais rapida.\n");
    return;
    /* No* tmp = (*no)->n;
    if(!tmp) {  // Se nao tem proximo, insere logo.
      (*no)->n = No_New(v); //  printf("'tmp->n == %d\n", (*no)->n->v);
    }
    else {      // Senao, pode acessar tmp->n sem crashar
      while( tmp->n ) {
        tmp = tmp->n;
      }
      tmp->n = No_New(v); // printf("'tmp->n == %d\n", tmp->v);
    } */
  }
}


// Pega proximo, libera atual.
// ... Ao final, atual serah o ultimo
// NO LEAKS, mas erros :/
void free_Lis(No* no) {
  if(!no) return;
  No* next = no->n;
  while(next) {
      free(no);  // valgrind reclama; mas n dixa leak
      no = next;
      next = next->n;  
    } 
  free(no); no = NULL;
}

// Chama o "freelLis" para child,
// mas soh quando todos os childs jah o tiverem feito tambem.
// TESTADO, FUNCIONA
void free_All_Child(No * no) {
  No* child = (no)->child;
  No* tmp = no;
  if(!child) return;
  while(child != NULL) {    
    free_All_Child(child);
    child = child->n;
  }
  free_Lis(no->child);
}

int show_Sub_Tree(No* no, int lvl) {
  if(!no->child) return 0;
  No* tmp = no->child;
  while(tmp) {
    show_Sub_Tree(tmp, lvl + 1);
    tmp = tmp->n;
  }
  show_Spaces(lvl), show_Lis( no->child );
  return 1;
}
