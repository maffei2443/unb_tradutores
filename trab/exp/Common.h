#ifndef _COMMON_H_
#define _COMMON_H_

#include "Array.h"
#include "uthash.h"
#include "Tree.h"
#include <assert.h>
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

typedef struct SymEntry{
  char id[257];
  _HASH_TYPES tag;
  Local local;
  char* escopo;
  Type type;
  union {
    int ival;
    char cval;
    float fval;
    struct {
      struct No* next;
      struct SymEntry* upperSym;
      struct SymEntry** nestedSym;
    } func;
  } u;
  struct SymEntry* next; // encadeamento para caso de conflito
  UT_hash_handle hh;
} SymEntry;

enum Return {
  R_UNITIALIZED,
  R_INT,
  R_FLOAT,
  R_VOID
};

SymEntry* SymEntry_New(char* id, int tag, char*);
void* SymEntry_Destroy(void*);
char* type2string(Type t);
#endif
