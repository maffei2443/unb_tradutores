#include "Tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>
#define ptfi(str, val) printf(str " %d\n",  (val))

Type Type_Class(Type type) {
  switch (type)  {
    case TYPE_VOID:
      return  TYPE_VOID;
    case TYPE_UNDEFINED:
      return TYPE_UNDEFINED;
    case TYPE_INT:
    case TYPE_FLOAT:
      return TYPE_SCALAR;      
    case TYPE_MAT_INT:
    case TYPE_MAT_FLOAT:
      return TYPE_MAT;
    default:
      return TYPE_INVALID;
  }
}


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
  no->type = TYPE_UNDEFINED;
  no->sval = NULL;  no->sval_alloc = 0;
  no->tname = NULL; no->tname_alloc = 0;
  no->symEntry = NULL;
  no->nextAux = NULL;
  // no->scope = NULL; no->scope_alloc = 0; 
  no->isToken = 0;
  no->hasAux = 0;
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
  if(!no) return;
  // NAO DEVE TER NEXT E AUX; UM OU OUTRO
  assert(!(no->hasAux == 1 && no->n != NULL));
  no->n = NULL;
  no->child = NULL; no -> childLast = NULL;
  no->nextAux = NULL;
  if(no->sval == NULL && no->sval_alloc)
    DESTROY_PTR(no->sval);
  if(no->tname == NULL && no->tname_alloc)
    DESTROY_PTR(no->tname);
  no->symEntry = NULL;  // NAO MEXR NA TABELA DE SIMBOLOS!
  // if(no->scope == NULL && no->scope_alloc)
  //   DESTROY_PTR(no->scope);
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
void add_Node_Child_If_Not_Null(No* no, No * newNo) {
  if(!no) {
    printf("Erro: %p aponsta pra NULO.\n", no);
    printf("Nao foi possivel adicionar um filho.\n");
    return;
  }
  else if (!newNo) {printf("Nao adiciona noh nulo como next!\n");return;}
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
  if(!no) {printf("[Tree.c:add_Node_Next] no eh NULO!\n");return;}
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
  if(!no) return;
  No* child = no->child;
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
  int auxCount = 0;
  while(head) {
    // for(int a = 0; a < i; a++) printf(" ");
    i++;
    if(head->hasAux) {
      n_child--;    // para nao contar duas vezes o primeiro parametro ;)
      No* aux = head;
      while(aux) {
        auxCount++;
        printf("<%s> ", aux->tname);
        aux = aux->nextAux;
      }
    }
    else if(head->isToken) {
      printf("%s ", head->sval);
    }
    else if(field == IVAL) {
      printf("%d ",head->ival);
    }
    else if (field == SVAL || field == TVAL) {
      if(head->tname && head->sval)
        printf("<%s, %s> ", head->tname, head->sval);
      else if (head->tname)
        printf("<%s> ",head->tname /*, head->ival */);
    }
    else {
      printf("u should not pass ");
    }   
    head = head->n;
  }
  printf("(n: %d) ", n_child + auxCount);
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