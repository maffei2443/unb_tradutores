#ifndef _COMMON_H_
#define _COMMON_H_

#include "Array.h"
#include "uthash.h"
#include "Tree.h"
// Should include another header except the default-ones
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
  HINT, HFLOAT, HID, HCHR, HRES_WORD, HFUN
} _HASH_TYPES;

typedef struct {
  char id[257];
  _HASH_TYPES tag;
  Local local;
  char* escopo;
  union {
    int ival;
    char cval;
    float fval;
    struct {
      struct No* next;  // next eh usado para PARAMETROS DE FUNCOES
      struct SymEntry* upperSym;
      struct SymEntry** nestedSym;
    } func;
  } u;
  UT_hash_handle hh;
} SymEntry;

SymEntry* SymEntry_New(char* id, int tag, char*);
void* SymEntry_Destroy(void*);

#endif
