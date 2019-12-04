#include "code_gen.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Tree.h"
#include "Colorfy.h"
#include "SemanticChecker.h"
#include "Common.h"
//////

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

// Retorna endereco de src, caso nao seja necessario conversao.
// Noutro caso, retorna o local de onde estah o valor convertido.
// OBS: dever ser dado FREE pela funcao chamadora.
// PROBLEMAS POSSIVEIS: se src nao for passivel de dar free.
// SOLUCAO: criar copia!

char* widen(No* src ,No* dest) {
  char * ret;

  Type t1, t2;
  if(src->sym_entry)t1 = src->sym_entry->type;
  else t1 = src->type;
  if(dest->sym_entry)t2 = dest->sym_entry->type;
  else t2 = dest->type;

  if(t1 == t2) ret = get_no_val(src);
  // Senao, tem tipos distintos e ASSUME 
  if (!can_cast(t1, t2)) {
    return calloc(1, sizeof(char));
  }
  else if (t1 == TYPE_INT && t2 == TYPE_FLOAT) {
    int temp;
    temp = temp_next();
    char* temp_addr = calloc(8, sizeof(char));
    temp_addr[0] = '$';
    char* temp_as_str = itoa(temp, calloc(6, sizeof(char)));  // numero maximo de temporario eh 1023
    memcpy(temp_addr + 1, temp_as_str, strlen(temp_as_str) + 1);
    ret = temp_addr;
    if(src->is_const) { 
      CODESHOW(printf("inttofl %s, %d\n", temp_addr, src->ival));
    } else {
      CODESHOW(printf("inttofl %s, %s\n", temp_addr, get_no_val(src)));
    }
  } else if( t1 == TYPE_MAT_INT && t2 == TYPE_MAT_FLOAT ){
    CODESHOW(printf("FAZER CONVERSAO MAT_INT --> MAT_FLOAT\n"));
    // O que fazer: checar se variavel eh global ou local.
    char* e = get_no_val(src);
    CODESHOW(printf("param %s\n", e)); free(e);
    e = get_mat_size(src);
    CODESHOW(printf("param %s\n", e)); free(e);

    ret = "DUMMY";
  } else {
    ret =get_no_val( src );
  }
  return ret;
}


// obs: apenas para casting EXPLICITO
char* narrow(No* src, No* dest) {
  char * ret;
  if(src->type == dest->type) ret = get_no_val(src);
  else if (src->type == TYPE_FLOAT && dest->type == TYPE_INT) {
    int temp;
    temp = temp_next();
    char* temp_addr = calloc(8, sizeof(char));
    temp_addr[0] = '$';
    char* temp_as_str = itoa(temp, calloc(6, sizeof(char)));  // numero maximo de temporario eh 1023
    memcpy(temp_addr + 1, temp_as_str, strlen(temp_as_str) + 1);
    ret = temp_addr;
    if(src->is_const) { 
      // Conversao de constante:
      // - pegar novo temporario, salvar nele o resultado da conversao.
      // - retornar string com esse temporario      
      CODESHOW(printf("fltoint %s, %d\n", temp_addr, src->ival));
    } else {
      CODESHOW(printf("fltoint %s, %s\n", temp_addr, get_no_val(src)));
    }
  } else if( src->type == TYPE_MAT_INT && dest->type == TYPE_MAT_FLOAT ){
    
  } else {
    ret =get_no_val( src );
    if(src->is_const)
      fprintf(stderr, "Sem conversao para %f\n",  src->fval);
    else
      fprintf(stderr, "Sem conversao para %s\n", src->sym_entry->id);    
  }
  return ret;
  
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
    printf("[Erro] Tipo %s ou %s nao suporta opecao +|*|-|/\n", t2s(t_src), t2s(t_src));
  }
  return addr;
}

// Retorna VALOR associado a um noh.
// Em caso de constante, eh string contendo o valor.
// Em caso de variavel local, eh string contendo o registrador
// que armazena o valor
// Em caso de variahvel global, retorna seu nome.
// NAO POSSUI GERA COHDIGO, MAS PODE MODIFICAR temp pois chama temp_next
char* get_no_val(No* no) {
  // DBG(printf("[getAddr] with %p->is_param = %d...\n", no, no->is_param));
  if(no->sym_entry && no->sym_entry->is_global) {  // eh identificador GLOBAL
    return str_ptr_clone(no->sym_entry->id);
  } 
  else {
    char* buf = calloc(22, sizeof(char));
    
    if (no->is_const) {  // se eh constante, nao precisa de temporario associado
      switch(no->type){
        case TYPE_INT:  sprintf(buf, "%d",  no->ival); break;
        case TYPE_FLOAT: sprintf(buf, "%f",  no->fval); break;
        case TYPE_CHAR: sprintf(buf, "%c",  no->ival); break;
      }
    } else if(no->sym_entry && no->addr == -1) {  // o && eh pra ficar mais facil pra gerar cohdigo de acesso aa matriz
      sprintf(buf, "$%d", no->sym_entry->addr);
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
char* get_no_addr(No* no) {
  if(!no) return calloc(10, sizeof(char));
  char* tmp = get_no_val(no);
  char* ret;
  if( no->sym_entry && no->sym_entry->is_global ) {
    ret = calloc(strlen(tmp) + 3, sizeof(char));
    ret[0] = '&';
    memcpy(ret+1, tmp, strlen(tmp));    
  } else {
    ret = tmp;
  }
  return ret;
}
// Retorna endereco de onde estah o tamanho de uma matriz.
// Gera cohdigo caso tenha de ser computado em tempo de execucao
char* get_mat_size(No* no) {
  assert(no->sym_entry);
  free(get_no_val(no));   // garante que no possui endereco [gambiarra]
  if(no->sym_entry->line == -1 && no->sym_entry->col == -1) {    // computar em tempo de execucao, pois eh argumento
    int mat_addr = no->sym_entry->addr;
    int temp = temp_next();
    CODESHOW(printf("mul $%d, $%d, $%d // tamanho da matriz, em tempo de execucao\n", temp,mat_addr+1 ,mat_addr+2));
    char* ret = calloc(20, sizeof(char));
    sprintf(ret, "$%d", temp);
    return ret;
  } else {  // possui valores estaticos para as dimensoes
    SymEntry* s = no->sym_entry;
    return itoa( s->line * s->col , calloc(20, sizeof(char)));
  }
}