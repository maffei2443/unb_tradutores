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

short temp_next() {
  temp++;
  if(temp > 1023) {
    printf("[Erro] Esgotou-se o nuhmero maximo de variaveis temporarias em utilizacao simultanea (max = 2014)\n");
    assert(temp < (short)1024);
  }
  return temp;
}

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