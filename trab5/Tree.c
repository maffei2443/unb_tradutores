#include "Tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>
#define ptfi(str, val) printf(str " %d\n",  (val))
int is_fun(Tag t) {
  return t == TAG_DEF_FUN || t == TAG_DECL_FUN;
}

Type Type_Class(Type type) {
  switch (type)  {
    case TYPE_CHAR:
      return TYPE_CHAR;
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
      return TYPE_UNDEFINED;
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
// obs: NÃO INICIALIZA code
No* No_New(int v) {
  No* no = (No*)calloc(1,sizeof(No));
  // NOTA: em teoria, nada (exceto inicializacao de ival) abaixo eh necessario por conta do calloc.
  no->type = TYPE_UNDEFINED;
  // Aqui ficarah o cohdigo associado a cada variavel, tal qual no livro
  // no->code = Array_New();
  // Array_Init(&no->code, 10);
  no->child = NULL;
  no->childLast = NULL;
  no->n = NULL;
  // no->p = NULL;
  no->sval = NULL;  no->sval_alloc = 0;
  no->tname = NULL; no->tname_alloc = 0;
  no->symEntry = NULL;
  no->nextAux = NULL;
  no->param = NULL;
  // no->scope = NULL; no->scope_alloc = 0; 
  // no->isToken = 0;
  // no->hasAux = 0;
  no->ival = v;
  no->code = NULL;
  // no->iaux = 0;
  // no->fval = 0.0;
  // no->is_const = 0;
  no->addr = -1;  // seta como sem temporario associado!
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
  // printf("ALOCOU %p\n", token);
  return token;
}

// Seta ponteiros internos de variavel do tipo No
// para NULL. Depois, dah free nessa variavel.
// NAO TESTADO
void No_Destroy(No* no) {
  // printf("[No_Destroy] %p\n", no);
  // if(!no) return;
  // // NAO DEVE TER NEXT E AUX; UM OU OUTRO
  // assert(!(no->hasAux == 1 && no->n != NULL));
  // no->n = NULL;
  // no->child = NULL; no -> childLast = NULL;
  // no->nextAux = NULL; no->param = NULL;
  if(no->sval_alloc)
    DESTROY_PTR(no->sval);
  if(no->tname_alloc) {
    DESTROY_PTR(no->tname);
  }
  if (no->param) {
    free_Param_Lis(no->param);
  }
  // no->symEntry = NULL;  // NAO MEXR NA TABELA DE SIMBOLOS!
  // if(no->scope == NULL && no->scope_alloc)
  //   DESTROY_PTR(no->scope);
  // Code_Destroy(no->code);
  // // free(no->code);
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
void free_Param_Lis(No* no) {
  printf("[free_Param_Lis] %p\n", no);
  if(!no) return;
  No* param = no;
  while(param->hasAux) {
      printf("\t will free %p\n", param);
      No* next = param->nextAux;
      No_Destroy(param);  // valgrind reclama; mas n dixa leak
      param = next;
  }
}

// Chama o "freelLis" para child,
// mas soh quando todos os childs jah o tiverem feito tambem.
// TESTADO, FUNCIONA
void free_All_Child(No * no) {
  // printf("[free_All_Child] ToFree? %p\n", no);
  if(!no) return;
  No* child = no->child;
  while(child != NULL) {
    No* nxt = child->n;
    free_All_Child(child);
    child = nxt;
  }
  // printf("[free_All_Child-final] %p\n", no);
  No_Destroy(no);
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
    else if(head->tname && !strcmp(head->tname, "expr")) {
      printf("<%s, %s> ",head->tname, type2string(head->type));
    }
    else if(head->tname && !strcmp(head->tname, "lvalue")) {
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
  if(!no) return 0;
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
  printf("CONSTRUINDO <<<>>>>>> %s\n", id);
  neo->line = -1;
  neo->col = -1;
  memcpy(neo->id, id, strlen(id));
  neo->id[strlen(id)] = '\0';
  neo->tag = tag;
  size_t t = strlen(escopo) + 1;
  neo->escopo = calloc( 1, t );
  memcpy(neo->escopo, escopo, t);
  neo->local.line = neo->local.col = -1;
  neo->type = TYPE_UNDEFINED;
  neo->astNode = NULL; // NAO MEXER NA ARVORE ABSTRATA!
  neo->def_fun = 0;    // usado para diferenciar entre declaracao e definicao de funcao
  return neo;
}
// Destroi entrada da TS e todas suas TS aninhadas 
// (valido apenas p/ declaracao de funcao)
void* SymEntry_Destroy(void* p){
  SymEntry* sym = (SymEntry*)p;
  if(!sym) return NULL;
  printf("DESTRUINDO >>> %p->id, sval = %s, %s\n", sym,sym->id, "sym->sval");
  if(sym->tag == TAG_DEF_FUN || sym->tag == TAG_DECL_FUN) {
    if(!sym->astNode) {
      printf("$$$ Funcao %s nao tem parametros $$$\n", sym->id);
    }
  }
  if(sym->escopo)
    DESTROY_PTR(sym->escopo);
  DESTROY_PTR(sym);
  return NULL;
}

char* type2string(Type t) {
  switch (t) {
    case TYPE_CHAR: return "char";
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
    case TYPE_POINTER: return "pointer";
    case TYPE_LIST: return "list(num)";
    case TYPE_LIST_LIST: return "list(list(num))";
    default:
      switch (t) {
      case TAG_DECL_FUN: return "fun-decl";
      case TAG_DEF_FUN: return "fun-def";
      case TAG_PARAM: return "param";
    }
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
  if(s->tag) {
    switch(s->tag) {
      case TAG_DECL_FUN: case TAG_DEF_FUN:
        printf("< fun(%s), %s>", type2string(s->type), s->id);
        break;
      case TAG_PARAM:
        printf("< param, %s, %s>", s->id, type2string(s->type));
        break;
    }
  }
  else {
    switch(s->type) {
      case TYPE_MAT_INT:
      case TYPE_MAT_FLOAT:
      case TYPE_MAT:
        printf("< %s[%d][%d], %s>", type2string(s->type), s->line, s->col, s->id);
        break;
      case  TYPE_ARRAY_INT:
      case  TYPE_ARRAY_FLOAT:
      case  TYPE_ARRAY:
        printf("< %s[%d], %s>", type2string(s->type), s->col, s->id);
        break;

      case  TYPE_CHAR:
      case  TYPE_VOID:
      case  TYPE_UNDEFINED:
      case  TYPE_INT:
      case  TYPE_FLOAT:
      case  TYPE_SCALAR:
      case  TYPE_POINTER:
        printf("< %s, %s>", type2string(s->type), s->id);
        break;        
      default:
        printf("NOT FOUND TYPE FOR: %s", type2string(s->type));
    }
  }  
  printf("\t(%p)l. %d, c. %d\n", s,s->local.line, s->local.col);
}