#include "Tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>
#define ptfi(str, val) printf(str " %d\n",  (val))
int is_fun(Type t) {
  return t == TYPE_DEF_FUN || t == TYPE_DECL_FUN;
}

Type Type_Class(Type type) {
  switch (type)  {
    case TYPE_VOID:
      return TYPE_VOID;
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
  char*  p = calloc(qtd+2, sizeof(char));
  memset(p, ' ', qtd);
  p[qtd] = '\0';  
  printf("%s", p);
  free(p);  p = NULL;
}

// Ok.
No* No_New(int v) {
  No* no = (No*)calloc(1,sizeof(No));
  no->child = NULL;
  no->childLast = NULL;
  no->n = NULL;
  // no->p = NULL;
  no->type = TYPE_UNDEFINED;
  no->sval = NULL;  no->sval_alloc = 0;
  no->tname = NULL; no->tname_alloc = 0;
  no->symEntry = NULL;
  no->nextAux = NULL;
  no->param = NULL;
  // no->scope = NULL; no->scope_alloc = 0; 
  no->isToken = 0;
  no->hasAux = 0;
  no->ival = v;
  no->fval = 0.0;
  no->is_const = 0;
  return no;
}

No* Token_New(char* tname, char* sval) {
  No* token = No_New(-1);
  token->isToken = 1;
  token->tname_alloc = 1;
  token->tname = calloc(strlen(tname) + 1, sizeof(char));
  token->sval_alloc = 1;
  token->sval = calloc(strlen(sval) + 1, sizeof(char));

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
  no->nextAux = NULL; no->param = NULL;
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
  // fprintf(stderr,"[add_Node_Child_If_Not_Null] \n"); fflush(stdout);
  if(!no) {
    // printf("Erro: %p aponsta pra NULO.\n", no);
    // printf("Nao foi possivel adicionar um filho.\n");
    return;
  }
  else if (!newNo) {
    // fprintf(stderr, "Nao adiciona noh nulo como next!\n");
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
    if(head->hasAux) {  //   por enquanto, soh eh usado para PARAMETRO
      n_child--;    // para nao contar duas vezes o primeiro parametro ;)
      No* aux = head;
      while(aux) {
        auxCount++;
        printf("<%s, %s> ", aux->sval, type2string(aux->type));
        aux = aux->nextAux;
      }
    }
    else if(head->is_const) {
      switch (head->type) {
        case TYPE_INT: printf("%d ", /* head->tname, */ head->ival); break;
        case TYPE_FLOAT: printf("%f ", /* head->tname, */ head->fval); break;
        // case TYPE_INT: printf("< %s, %d>", head->tname, ); break;
      }
    }
    else if(head->isToken) {
      printf("%s ", head->sval);
    }
    else if(!strcmp(head->tname, "expr")) {
      printf("<%s, %s> ",head->tname, type2string(head->type));
    }
    else if(!strcmp(head->tname, "lvalue")) {
      printf("<lvalue, %s> ", type2string(head->type));
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
      printf("u should not pass \n");
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

// Estava em common
SymEntry* SymEntry_New(char* id, int tag, char* escopo){
  SymEntry* neo = (SymEntry*)calloc(1, sizeof(SymEntry));
  
  memcpy(neo->id, id, strlen(id));
  neo->id[strlen(id)] = '\0';
  neo->tag = tag;
  size_t t = strlen(escopo) + 1;
  neo->escopo = calloc( 1, t );
  memcpy(neo->escopo, escopo, t);
  neo->escopo[t] = '\0';
  neo->u.ival = 0;
  // neo->u.func.next = 0;
  neo->local.line = neo->local.col = -1;
  neo->type = TYPE_UNDEFINED;
  neo->astNode = NULL; // NAO MEXER NA ARVORE ABSTRATA!
  neo->def_fun = 0;    // usado para diferenciar entre declaracao e definicao de funcao
}
// Destroi entrada da TS e todas suas TS aninhadas 
// (valido apenas p/ declaracao de funcao)
void* SymEntry_Destroy(void* p){
  SymEntry* sym = (SymEntry*)p;
  if(!sym) return NULL;
  if(sym->tag == TYPE_DEF_FUN || sym->tag == TYPE_DECL_FUN) {
    No* tmp = sym->astNode->param;
    No* tmp2; 
    while(tmp) {
      tmp2 = tmp->nextAux;
      free(tmp);
      tmp = tmp2;
    }
    // trata-se se funcao! liberar portanto
    // a lista de nohs que compoem sua assinatura
    // free_Lis(sym->u.func.next); sym->u.func.next = NULL;
    // SymEntry_Destroy(sym->u.func.nestedSym); sym->u.func.nestedSym = NULL;
    // sym->u.func.upperSym = NULL;  // nao tentar dar free no pai; ciclo
  }
  free(sym);
  sym = NULL;
  return NULL;
}

char* type2string(Type t) {
  switch (t) {
    case TYPE_VOID: return "void";
    case TYPE_UNDEFINED: return "undefined";
    case TYPE_INT: return "int";
    case TYPE_FLOAT: return "float";
    case TYPE_SCALAR: return "scalar";
    case TYPE_ARRAY_INT: return "array(int)";
    case TYPE_ARRAY_FLOAT: return "array(float)";
    case TYPE_ARRAY: return "array(int|float)";
    case TYPE_MAT_INT: return "mat(int)";
    case TYPE_MAT_FLOAT: return "mat(float)";
    case TYPE_MAT: return "mat(int|float)";
    case TYPE_DECL_FUN: return "fun";
    case TYPE_DEF_FUN: return "fun";
    case TYPE_IF: return "if";
    case TYPE_PARAM: return "param";
    case TYPE_POINTER: return "pointer";
    case TYPE_INVALID: return "invalid";
  }
}
static char* t2s(Type t) {
  return type2string(t);
}
void print_reshi(SymEntry* reshi) {
    SymEntry *s;
    SymEntry *nexti;
    printf(">>>>>> TABELA DE SIMBOLOS <<<<<<<\n");
    for(s=reshi;s != NULL;s = nexti) {
      nexti = s->hh.next;
      show_entry(s);
      while(s->next) {
        show_entry(s->next);
        s = s->next;
      }      
    }
  printf("---------------------------\n");
}

void show_entry(SymEntry* s) {
  printf("%10s: ", s->escopo);
  int classType = Type_Class(s->tag);
  if(classType == TYPE_MAT) {
    printf("< %s, %s >", 
      t2s(s->tag == TYPE_INT ? TYPE_MAT_INT : TYPE_MAT_FLOAT) ,s->id);
  }
  else if (classType == TYPE_ARRAY) {
    printf("< %s, %s >", 
      t2s(s->tag == TYPE_INT ? TYPE_ARRAY_INT : TYPE_ARRAY_FLOAT) ,s->id);
  }
  else {
    switch(s->tag) {
      case TYPE_ARRAY_INT:
      case TYPE_ARRAY_FLOAT:
      case TYPE_INT:
      case TYPE_FLOAT:
        printf("< %s, %s>", type2string(s->tag), s->id);
        break;    
      case TYPE_DECL_FUN: case TYPE_DEF_FUN:
        printf("< fun(%s), %s>", type2string(s->type), s->id);
        break;
      case TYPE_PARAM:
        printf("< param, %s, %s>", s->id, type2string(s->type));
        break;      
      case TYPE_MAT_FLOAT: case TYPE_MAT_INT:
        printf("< mat(%s), %s>", t2s(s->type), s->id);
        break;
      
    }
  }
  printf("\t(%p)l. %d, c. %d\n", s,s->local.line, s->local.col);
}