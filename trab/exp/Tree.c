#include "Tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

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
  no->child = NULL;
  no->childLast = NULL;
  no->n = NULL;
  // no->p = NULL;
  no->sval = NULL;  no->sval_alloc = 0;
  no->tname = NULL; no->tname_alloc = 0; 
  no->isToken = 0;
  no->ival = v;
  no->fval = 0.0;
  return no;
}

No* Token_New(char* tname, char* sval) {
  No* token = No_New(-1);
  token->isToken = 1;
  token->tname_alloc = 1;  token->tname = calloc(strlen(tname) + 1, sizeof(char));
  token->sval_alloc = 1;  token->sval = calloc(strlen(sval) + 1, sizeof(char));
  if(!token->tname) abort();
  if(!token->sval ) abort();
  memcpy(token->tname, tname, strlen(tname));
  memcpy(token->sval, sval, strlen(sval));
  // printf("[Token_New(char* tname, char* sval)] sval = %s\n", sval);
  // printf("[Token_New(char* tname, char* sval)] token->sval = %s\n\n", token->sval);
  return token;
}

// Seta ponteiros internos de variavel do tipo No
// para NULL. Depois, dah free nessa variavel.
// NAO TESTADO
void No_Destroy(No* no) {
  // no -> p = NULL;
  no -> n = NULL;
  no -> child = NULL; no -> childLast = NULL;  
  if(no->sval == NULL && no->sval_alloc)
    DESTROY_PTR(no->sval);
  if(no->tname == NULL && no->tname_alloc)
    DESTROY_PTR(no->tname);
  DESTROY_PTR(no);
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
  // neo->p = no;
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
  // (newNo)->p = no;
}
// Adiciona novo irmao para no.
// LIMITACAO: no DEVE TER UM PAI!
// Motivo: insercao RAPIDA!
void add_Node_Next(No* no, No* next) {
  if(no == next) {printf("stupid loop!\n");return;}
  int _;
  if(no->n == no){
    printf("Ciclo! %p->n = %p!", no, no->n);
    scanf("%d", &_);
  }
  if(!(no->n)) {  // Se nao tem proximo, insere logo.
    no->n = next; //  printf("'tmp->n == %d\n", (*no)->n->ival);
  }
  else {      // Senao, pode acessar tmp->n sem crashar
    No* tmp = no; 
    while( tmp->n != NULL) {
      // printf("%p %p\n", tmp, tmp->n);
      tmp = tmp->n;
    }
    tmp->n = next; // printf("'tmp->n == %d\n", tmp->ival);
    if(next == tmp) printf("WTF?? no: %p, no->n: %p", no, no->n), abort();
  }
}


// Pega proximo, libera atual.
// ... Ao final, atual serah o ultimo
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

void show_Lis(No* head, Field field) {
  int i = 0;
  int n_child = ListSize(head);
  while(head) {
    // for(int a = 0; a < i; a++) printf(" ");
    i++;
    if(head->isToken) {
      printf("%s ", head->sval);
      // if(!head->tname) // "token" pode ser melhor especificado por sval
      //   printf("<token, %s> ", head->sval);
      // else 
      //   printf("<%s, %s> ", head->tname, head->sval);
    }
    else if(field == IVAL) {
      printf("%d ",head->ival);
    }
    else if (field == SVAL || field == TVAL) {
      if(head->tname && head->sval)
        printf("<%s, %s> ", head->tname, head->sval);
      else if (head->tname)
        printf("<%s, %d> ",head->tname, head->ival);
    }
    else {
      printf("u should not pass ");
    }   
    head = head->n;
  }
  printf("(n: %d) ", n_child);
  printf("\n");
}


int show_Sub_Tree(No* no, int lvl, Field field) {
  if(!no->child) return 0;
  No* tmp = no->child;
  while(tmp) {
    show_Sub_Tree(tmp, lvl + 1, field);
    tmp = tmp->n;
  }
  show_Spaces(lvl), show_Lis( no->child, field );
  return 1;
}

int ListSize(No* no) {
  int c = 0;
  for(; no; no = no->n, c++);
  return c;
}