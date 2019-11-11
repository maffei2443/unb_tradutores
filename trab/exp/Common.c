#include "Common.h"

SymEntry* SymEntry_New(char* id, int tag, char* escopo){
  SymEntry* neo = (SymEntry*)calloc( sizeof(SymEntry), 1);
  
  memcpy(neo->id, id, strlen(id)+1); neo->id[strlen(id)+1] = '\0';
  neo->tag = tag;
  size_t t = strlen(escopo);
  neo->escopo = malloc( t );
  memcpy(neo->escopo, escopo, t);
  neo->escopo[t] = '\0';
  neo->u.ival = 0; neo->u.func.next = 0;
  neo->local.line = neo->local.col = -1;
  neo->type = TYPE_UNDEFINED;
}
// Destroi entrada da TS e todas suas TS aninhadas 
// (valido apenas p/ declaracao de funcao)
void* SymEntry_Destroy(void* p){
  SymEntry* sym = (SymEntry*)p;
  if(!sym) return NULL;
  if(sym->tag == HFUN) {
    // trata-se se funcao! liberar portanto
    // a lista de nohs que compoem sua assinatura
    free_Lis(sym->u.func.next); sym->u.func.next = NULL;
    SymEntry_Destroy(sym->u.func.nestedSym); sym->u.func.nestedSym = NULL;
    sym->u.func.upperSym = NULL;  // nao tentar dar free no pai; ciclo
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
    case TYPE_ARRAY_INT: return "array(int)";
    case TYPE_ARRAY_FLOAT: return "array(float)";
    case TYPE_MAT_INT: return "mat(int)";
    case TYPE_MAT_FLOAT: return "mat(float)";
  }
}
