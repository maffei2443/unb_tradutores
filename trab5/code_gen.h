#ifndef CODE_GEN_H
#define CODE_GEN_H
#include "Array.h"
#include "Common.h"
static short temp = -1;

typedef struct {
  struct Code* next;
  struct Code* last;
  Array* text;
  char text_alloc;
} Code;

short int local_pos;

/**
 * C++ version 0.4 char* style "itoa":
 * Written by Lukás Chmela
 * Released under GPLv3.
 */
char* itoa(int value, char* result);

/// Retorna prohximo valor para ser usado como temporario
short temp_next();

/// Reseta tempo de modo que na proxima chamada retorna o valor 0.
int tempo_reset();

Code* Code_New(char* text);

void Code_Destroy(Code* code);

char* str_ptr_clone(const char* src);

// char* widen(char* src, Type t_src ,Type t_dest);

char* wrapper(char);

unsigned long critical_error;
// int sprintf ( char * str, const char * format, ... );

#endif