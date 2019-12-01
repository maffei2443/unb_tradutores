#include "code_gen.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Tree.h"
//////
unsigned long critical_error = 0;
short int local_pos = 0;

/* https://stackoverflow.com/questions/9655202/how-to-convert-integer-to-string-in-c */

char* itoa(int i, char b[]){
    char const digit[] = "0123456789";
    char* p = b;
    if(i<0){
        *p++ = '-';
        i *= -1;
    }
    int shifter = i;
    do{ //Move to where representation ends
        ++p;
        shifter = shifter/10;
    }while(shifter);
    *p = '\0';
    do{ //Move back, inserting digits as u go
        *--p = digit[i%10];
        i = i/10;
    }while(i);
    return b;
}  


///////

// short temp_next() {
//   temp++;
//   if(temp > 1023) {
//     printf("[Erro] Esgotou-se o nuhmero maximo de variaveis temporarias em utilizacao simultanea (max = 2014)\n");
//     assert(temp < (short)1024);
//   }
//   return temp;
// }

int temp_reset() {
  temp = -1;
}

Code* Code_New(char* text) {
  Code* no = calloc(1, sizeof(Code));
  no->text = Array_New();
  Array_Init(no->text, strlen(text) + 1);
  // Array_Insert(no->text, text);
  no->text_alloc = 1;
}

void Code_Destroy(Code* code) {
  if(!code) return;
  Array_Delete(code->text);
  free(code);
  code = NULL;
}

char* str_ptr_clone(const char* src) {
  int sz = strlen(src) + 1;
  char* ret = calloc(1, sz);
  memcpy(ret, src, sz);
  return ret;
}

// Retorna NULL caso nao seja necessario conversao.
// Noutro caso, retorna o local de onde estah o valor convertido.
// OBS: dever ser dado FREE pela funcao chamadora.
// PROBLEMAS POSSIVEIS: se src nao for passivel de dar free.
// SOLUCAO: criar copia!

char* widen(char* src, Type t_src ,Type t_dest) {
  // inicio - igual ao livro
  // NAO USAR POR ENQUANTO
  abort();
  src = str_ptr_clone(src);
  if(t_src == t_dest) return src;
  else if (t_src == TYPE_INT && t_dest == TYPE_FLOAT) {
    short  a;
    char* buf = itoa(a=temp_next(), calloc(1, 200));
    char* buf2 = calloc(1, 200 + strlen(buf) + 1);
    sprintf(buf2, "inttofl $%d, %s", a, buf);
    free(buf);
    buf2 = realloc(buf2, strlen(buf2)+1);
    return buf2;
  }
  return NULL;
  // final - igual ao livro
  Type maior = max(t_src,t_dest), menor = min(t_src, t_dest);
  Type c1 = Type_Class(t_src), c2 = Type_Class(t_dest);
  

  if((c1 == TYPE_MAT) == (c2 == TYPE_MAT)) {  // ambos ou matriz ou nao matriz
    
    if(maior == menor) {
      
    }
  }
  else {

  }
  // return temp;
}

// Utilizado para promocao de tipo nas operacoes de:
// +
// -
// /
// *
// Caso algum dos operadores NAO SEJA INTEIRO, retorna NULL.

char* widen_basic(char* src, Type t_src, Type t_dest) {
  
  if( ! ( Type_Class(t_src) == TYPE_SCALAR && Type_Class(t_dest) == TYPE_SCALAR) )
    return NULL;
  
  if(t_src == t_dest) return str_ptr_clone(src);
  char* addr = calloc(10, sizeof(char));
  
  if (t_src == TYPE_INT && t_dest == TYPE_FLOAT) {
    int temp = temp_next();
    printf("inttofl $%d, %s\n", temp, src);
    sprintf(addr, "$%d", temp);
  }
  else if (t_src == TYPE_FLOAT && t_dest == TYPE_INT) {
    int temp = temp_next();
    printf("fltoint $%d, %s\n", temp, src);
    sprintf(addr, "$%d", temp);
  }
  else {
    critical_error++;
    printf("[Erro] Tipo %s ou %s nao suporta opecao +|*|-|/\n", type2string(t_src), type2string(t_src));
  }
  return addr;
}

char* get_addr(No* no) {
  if(no->symEntry && no->symEntry->is_global) {  // eh identificador GLOBAL
    return str_ptr_clone(no->symEntry->id);
  } 
  else {
    char* buf = calloc(22, sizeof(char));
    
    if (no->is_const) {  // se eh constante, nao precisa de temporario associado
      switch(no->type){
        case TYPE_INT:  sprintf(buf, "%d",  no->ival); break;
        case TYPE_FLOAT: sprintf(buf, "%f",  no->fval); break;
        case TYPE_CHAR: sprintf(buf, "%c",  no->ival); break;
      }
    } else if(no->symEntry) {  // eh variavel local
      sprintf(buf, "$%d", no->symEntry->temp_num);
    } else if (no->addr == -1){  // atribuir endereco temporario
      int temp = temp_next();
      no->addr = temp;
      sprintf(buf, "$%d", temp);
    }
    else {  // jah tem endereco temporario associado
      sprintf(buf, "$%d", no->addr);
    }
    
    return buf;
  }
}