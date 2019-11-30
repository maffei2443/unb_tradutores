#ifndef CODE_GEN_H
#define CODE_GEN_H
#include "Array.h"
#include "Common.h"
static short temp = -1;



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

// Provavelmente serah deprecated
char* widen(char* src, Type t_src ,Type t_dest);


char* widen_basic(char* src, Type t_src ,Type t_dest);

char* wrapper(char);

// Retorna string contendo nome que se deve usar para tal identificador.
// SE eh um identificador GLOBAL, retorna o nome na tabela de simbolos.
// SE eh um identificador LOCAL, retorna $<numero>
// SE eh um identificador parametro, deve cair no mesmo caso de 
//    identificador local.
// LEMBRAR DE DESALOCAR APOHS USAR O RESULTADO!
char* get_addr(No*);

unsigned long critical_error;
// int sprintf ( char * str, const char * format, ... );

#endif