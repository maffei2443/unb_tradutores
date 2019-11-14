#include "SemanticChecker.h"

extern char* currScope;
extern char* GLOBAL_SCOPE;
extern int numlines;
extern int currCol;

extern int MAT_POW, EQ, NEQ, GE, LE, AND, OR;

int gambs_tam = 0;
int gambs_qtd = 0;

SymEntry** gambs;

// enum gerada pelo bison; gambs feita automaticamente por
// script python

// REPLACE FROM HERE
enum _yytokentype
  {
    _EQ = 258,
    _NEQ = 259,
    _GE = 260,
    _LE = 261,
    _AND = 262,
    _OR = 263,
    _MAT_POW = 264,
    _AHEAD = 265,
    _BASE_TYPE = 266,
    _WHILE = 267,
    _V_INT = 268,
    _V_FLOAT = 269,
    _V_ASCII = 270,
    _MAT_TYPE = 271,
    _IF = 272,
    _ID = 273,
    _ICAST = 274,
    _FCAST = 275,
    _ELSE = 276,
    _RETURN = 277,
    _PRINT = 278,
    _IREAD = 279,
    _FREAD = 280,
    _COPY = 281,
    _ERRU = 282
  };
// UNTIL HERE




//  Retorna TYPE_UNDEFINED nos casos:
// - left/right ser TYPE_UNDEFINED
// - left/right ser TYPE_VOID
// - left/right ser TYPE_ARRAY
// - expressão mal formada como por exemplo divisão de 
// escalar por matriz
Type bin_expr_type(Type left, Type right, int op) {
  Type leftClass = Type_Class(left);
  Type rightClass = Type_Class(right);
  if(left == TYPE_UNDEFINED || right == TYPE_UNDEFINED) return TYPE_UNDEFINED;// erro de inicializacao...
  else if(left == TYPE_VOID || right == TYPE_VOID ) return TYPE_VOID;// tentando usar retorno de funcao VOID
  else if(leftClass == TYPE_ARRAY || rightClass == TYPE_ARRAY) return TYPE_UNDEFINED;
  // NAO SE PODE OPERAR SOBRE ARRAYS.
 
  switch (op)  {
    case '+': case '-':
      if(leftClass == rightClass) max(left, right);
      else if(left == TYPE_MAT && right == TYPE_SCALAR) return left;
      else return TYPE_UNDEFINED;
    case '*':
      if(leftClass == rightClass) max(left, right);
      else if(left == TYPE_SCALAR && right == TYPE_MAT) return left;
      else return TYPE_UNDEFINED;
    case '/':
      if(leftClass == rightClass) max(left, right);
      else if(left == TYPE_MAT && right ==  TYPE_SCALAR ) return left;
      else return TYPE_UNDEFINED;
    case '@':
      if(leftClass == TYPE_MAT && rightClass == TYPE_MAT) return max(left, right);
      else return TYPE_UNDEFINED;
      /* code */
    case _MAT_POW:
      if((left == TYPE_MAT_INT || left == TYPE_MAT_FLOAT)
        && (right == TYPE_INT || right == TYPE_FLOAT)) {
        return left == TYPE_MAT_INT ? TYPE_MAT_INT : TYPE_MAT_FLOAT;
      }
      else
        return TYPE_UNDEFINED;

    case _EQ:  case _NEQ:
    case _GE:  case _LE:
    case '<':  case '>':
    case _AND:  case _OR:
      return TYPE_INT;
    default: 
      return TYPE_UNDEFINED;
  }
}


// Retorna NULL caso nao o tenha sido;senao,
// retorna ponteiro para declracao mais prohxima.
SymEntry* was_declared(SymEntry** reshi, char* id){
  SymEntry* oldEntry = NULL;
  SymEntry* last_same_id = oldEntry;
  HASH_FIND_STR((*reshi), id, oldEntry);
  while( oldEntry ) {
    printf("old: %p, next: %p\n", oldEntry, oldEntry->next);
    if(strcmp(oldEntry->escopo, currScope) == 0){  // declaracao sob mesmo escopo
      return oldEntry;
    }
    else if(strcmp(oldEntry->escopo, GLOBAL_SCOPE) == 0){  // mesmo nome e escopo global
      last_same_id = oldEntry;
    }
    oldEntry = oldEntry->next;
  }
  return last_same_id;
}

SymEntry* add_entry(SymEntry** reshi, char* id, int tag) {
    SymEntry* newEntry = NULL;
    HASH_FIND_STR((*reshi), id, newEntry);/* id already in the hash? */
    if (newEntry == NULL) {
      newEntry = SymEntry_New(id, tag, currScope);
      newEntry->local.line = numlines;
      newEntry->local.col = currCol;
      HASH_ADD_STR( (*reshi), id, newEntry );/* id: name of key field */
      addToDel(&newEntry);
    }
    else {    // Checar se eh declaracao no msm escopo. Se for, nao adiciona e dah pau (retorna NULL);
      printf("Possivel conflito com %s:%s\n", id, newEntry->escopo);
      for(;newEntry->next;newEntry = newEntry->next) {
        if(strcmp(id, newEntry->id) == 0 && strcmp(currScope, newEntry->escopo)) {
          printf("Erro: redeclaracao de %s:%s em l.%d, r.%d\n",
            currScope, id, newEntry->local.line, newEntry->local.col);
          return NULL;
        }
      }
      if( /* 0 &&  */strcmp(id, newEntry->id) == 0 && !strcmp(currScope, newEntry->escopo) ) {          
        printf("Erro: redeclaracao de %s:%s em l.%d, r.%d\n",
          currScope, id, newEntry->local.line, newEntry->local.col);
        return NULL;
      }
      else {
        newEntry->next = SymEntry_New(id, tag, currScope);
        newEntry->next->local.line = numlines;
        newEntry->next->local.col = currCol;
      }
    }
    return newEntry;
}

void addToDel(SymEntry** p) {
  if(gambs_qtd  >= gambs_tam) {
    gambs_tam = 2 * (gambs_tam + 1);
    gambs = (SymEntry**)realloc(gambs, gambs_tam*sizeof(SymEntry*));
  }
  gambs[gambs_qtd] = *p;
  // printf("AddToDel: %p\n", gambs[gambs_qtd]);
  // printf("\tcom id: %s\n", gambs[gambs_qtd]->id);
  gambs_qtd++;
}

void delGambs() {
  printf("QTD : %d\n", gambs_qtd);
  for(int i = 0;i < gambs_qtd;i++){
    printf("id: %s\n", (gambs[i])->id);
    SymEntry_Destroy(gambs[i]);
    gambs[i] = NULL;
  }
  if(gambs)
    free(gambs);
  gambs = NULL;
}
