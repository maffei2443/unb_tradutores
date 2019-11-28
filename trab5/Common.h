#ifndef COMMON_H
#define COMMON_H
/// Modulo contendo estruturas de dados livres de dependencias
/// e que portanto podem ser utilizadas por qualquer outro arquivo.
typedef struct {
  int lines, isChar, notChar;
  int lineInit, colInit;
} CommBlock;

typedef struct  {
  int lineInit,
      colInit,
      notChar,
      isChar;
} LineComment;

typedef struct {
  int line,
      col;
} StringStart;

typedef struct {
  int line, col;
} Local;

typedef enum {
  IVAL  = 0,
  SVAL,
  TVAL
} Field;

typedef enum {
  TYPE_CHAR = -3,
  TYPE_VOID = -1,
  TYPE_UNDEFINED = 0, 
  TYPE_INT = 1,
  TYPE_FLOAT = 2,
  TYPE_SCALAR = 3,
  TYPE_ARRAY_INT = 4,
  TYPE_ARRAY_FLOAT = 8,
  TYPE_ARRAY = 9,
  TYPE_MAT_INT = 16,
  TYPE_MAT_FLOAT = 32,
  TYPE_MAT = 33,
  TYPE_POINTER = 120,
  TYPE_LIST,
  TYPE_LIST_LIST
} Type;

typedef enum {
  TAG_UNDEFINED = 0,
  TAG_DECL_FUN = TYPE_POINTER + 1,
  TAG_DEF_FUN,
  TAG_PARAM
} Tag;

#endif