#ifndef _COMMON_H_
#define _COMMON_H_

#include "Tree.h"

#include <assert.h>
// Should include another header except the default-ones
// extern int MAT_POW, EQ, NEQ, GE, LE, AND, OR;
SymEntry* SymEntry_New(char* id, int tag, char*);
void* SymEntry_Destroy(void*);
char* type2string(Type t);
#endif
