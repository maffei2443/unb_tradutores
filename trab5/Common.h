#ifndef COMMON_H
#define COMMON_H

#include "uthash.h"
#include "Array.h"
#include "Colorfy.h"
#ifdef NULL
  #undef NULL
  #define NULL ((void *)0)
#endif

#define CODESHOW(X) \
  {BoldCyan(); \
  X;\
  Reset();}
#define ERRSHOW(X) \
  {BoldRed(); \
  X;\
  Reset();}
#define WARSHOW(X) \
  {BoldYellow(); \
  X;\
  Reset();}
#define DBG(X) \
  {BoldGreen(); \
  X;\
  Reset();}

#define BLUE(X) \
  {BoldCyan(); \
  printf(X);\
  Reset();}
#define STR(x) #x
/// Modulo contendo estruturas de dados livres de dependencias
/// e que portanto podem ser utilizadas por qualquer outro arquivo.

typedef struct {
  struct Code* next;
  struct Code* last;
  Array* text;
  char text_alloc;
} Code;

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
  TYPE_CHAR = -10,
  TYPE_UNDEFINED = 0, 
  TYPE_INT = 1,
  TYPE_FLOAT = 10,
  TYPE_SCALAR = 20,
  TYPE_ARRAY_CHAR = 30,
  TYPE_ARRAY_INT = 40,
  TYPE_ARRAY_FLOAT = 50,
  TYPE_ARRAY = 60,

/******/
  // Para diferenciar linha de matriz de array
  TYPE_UMAT_CHAR = -1,
  TYPE_UMAT_INT = -2,
  TYPE_UMAT_FLOAT = -3,
  TYPE_UMAT = -4,
/******/
  TYPE_MAT_CHAR = 70,
  TYPE_MAT_INT = 80,
  TYPE_MAT_FLOAT = 90,
  TYPE_MAT = 100,
  TYPE_POINTER = 110,
  TYPE_LIST = 120,
  TYPE_LIST_LIST = 130
} Type;

typedef enum {
  TAG_UNDEFINED = 0,
  TAG_DECL_FUN = TYPE_POINTER + 1,
  TAG_DEF_FUN,
  TAG_PARAM
} Tag;

typedef enum {
  BASE_TYPE_UNDEFINED = 0,
  BASE_TYPE_INT,
  BASE_TYPE_FLOAT
} Base_Type;

// Indica TIPO DA REGRA da entrada de simbolos

typedef struct SymEntry{
  
  char id[257];
  short int addr;   // numero usado para quando se for salvar seu valor/endereço, escolher o temporario associado
  Tag tag;
  Type type;  // nao ideal, MAS fica mais facil...
  Base_Type base_type;
  char is_global;
  char* escopo;
  Local local;
  char def_fun;
  int line, col;
  struct No* astNode;
  struct SymEntry* next; // encadeamento para caso de conflito
  UT_hash_handle hh;
} SymEntry;

typedef struct No {
  // struct No * p;   // ponteiro para pai
  struct No * child;
  struct No * childLast;
  struct No * n;
  struct No * nextAux;
  struct No * param;  // usado apenas por entradas representando FUNCOES
  SymEntry* symEntry;

  char* sval;
  int ival;
  int iaux;
  float fval;
  
  //  Indica tipo do no (ex: expr, param, loop...)
  char* tname;        
  char is_const;
  char sval_alloc;
  char tname_alloc;
  char code_alloc;
  Type type;
  char isToken;    // nesse modo, usa-se mesmo noh para token e regra
  char hasAux;
  Code* code;
  int addr;
   // campo utilizado basicamente por EXPRESSOES, para usar como temporario (ver. pgn 389)
  //  Contudo, pode ser utilizado para outros fins, evidentemente
} No;

unsigned long critical_error;
int temp;
int old_temp;  // para restaurar valor de temp. NUNCA deve ser diretamente utilizado
int temp_next();
// Funcoes para salvar/restaurar valor de temp
void new_context();
void old_context();
#endif