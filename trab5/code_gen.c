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

// Obs; nao funciona para matrizes!
char* widen(No* src ,No* dest) {
  char * ret;

  Type t1, t2;
  if(src->sym_entry)t1 = src->sym_entry->type;
  else t1 = src->type;
  if(dest->sym_entry)t2 = dest->sym_entry->type;
  else t2 = dest->type;

  // if(t1 == t2) ret = get_no_val(src);  // antigo: esta correto?
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
    // WARSHOW(printf("FAZER CONVERSAO MAT_INT --> MAT_FLOAT\n"));
    // // O que fazer: checar se variavel eh global ou local.
    // char* e = get_no_val(src);
    // CODESHOW(printf("param %s\n", e)); free(e);
    // e = get_mat_size(src);
    // CODESHOW(printf("param %s\n", e)); free(e);
    // WARSHOW(printf("FIM CONVERSAO MAT_INT --> MAT_FLOAT\n"));
    WARSHOW(printf("widen nao estah preparado para matrizes!"));
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
  if(!no) return calloc(1,1);
  if(no->is_const) {
    switch(no->type) {
      case TYPE_INT: {
        char* ret = itoa(no->ival, calloc(20, sizeof(char)));
        // for debug purposes
        return ret;
      }
      case TYPE_FLOAT: {
        char* buf = calloc(20, sizeof(char));
        sprintf(buf, "%f", no->fval);
        return  buf;
      }
    }
  }  
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
    // printf("Addr of %s : %s\n", no->tname , buf);
    return buf;
  }
}
char* get_no_addr(No* no) {
  // printf("Addr of >tname = %s\n", no->tname);
  
  if(!no) return calloc(10, sizeof(char));
  if(no->is_const) {
    switch(no->type) {
      case TYPE_INT: {
        char* ret = itoa(no->ival, calloc(20, sizeof(char)));
        // for debug purposes
        return ret;
      }
      case TYPE_FLOAT: {
        char* buf = calloc(20, sizeof(char));
        sprintf(buf, "%f", no->fval);
        return  buf;
      }
    }
  }
  char* tmp = get_no_val(no);
  // DBG(printf("tmp: %s", tmp));
  char* ret;
  // Caso especial de escalares
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
  if(!no) return calloc(1,1);
  if(no->temp_mat.line != -1 && no->temp_mat.col != -1) { // matriz temporaria
    return itoa( no->temp_mat.line * no->temp_mat.col , calloc(20, sizeof(char)));
  }
  // printf("no->sval, no->tname: %s : %s\n", no->sval, no->tname);
  printf("line: %d, col: %d\n", no->temp_mat.line, no->temp_mat.col);
  printf("[get_mat_size] abort");
  abort();
  // show_entry(no->sym_entry);
  assert(no->sym_entry);
  if(Type_Class(no->type) != TYPE_MAT ) {
    ERRSHOW(printf("%s nao eh matriz!\n", no->sym_entry->id));
    return calloc(1,1);
  }
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
    char* ret = itoa( s->line * s->col , calloc(20, sizeof(char)));
    return ret;
  }
}

void check_type_and_convert_on_lr_attr(No* lvalue, No* rvalue) {
  // CASO ESPECIAL : ATRIBUICAO DE ESCALAR A ELEMENTO DA MATRIZ
  char* left_addr, *right_addr = NULL;
  left_addr = get_no_addr(lvalue);
  Type t1 = lvalue->type, t2 = rvalue->type;
  Type c1 = Type_Class(t1), c2 = Type_Class(t2);
  const char* s1 = t2s(t1), *s2 = t2s(t2);

  if(t2 == TYPE_LIST || t2 == TYPE_LIST_LIST) {
    WARSHOW(printf("Divida: nao foi implementado inicalizacao com vetor"));
    return;
  }
  if(t1 == TYPE_UNDEFINED || t2 == TYPE_UNDEFINED ||
    to_base_type(t1) == TYPE_CHAR || to_base_type(t1) == TYPE_CHAR) {
    ERRSHOW(printf("Erro: UNDEFINED/char em atribuicao: %s = %s\n", s1, s2));
  } else if (c1 == TYPE_ARRAY || c2 == TYPE_ARRAY) {
    ERRSHOW("Proibido atribuiacao entre array!\n");
  } else if(c1 == c2) {
    if(t1 < t2) {
      ERRSHOW(printf("Nao eh possivel a atribuicao %s = %s : narrow casting\n", s1, s2));    
      right_addr = "impossivel";
    } else {  // t1 >= t2 e c1 eh matriz OU scalar
      if ( c1 == TYPE_MAT  ) {
        if(t1 > t2) {
          WARSHOW(printf("Conversao entre matrizes. %s = %s", t2s(t1), t2s(t2)));

          SymEntry* sym = rvalue->sym_entry;

          BLUE("AQUI O CAST DE MATRIZES\n");
          CODESHOW(printf("param %s\n", get_no_addr(rvalue)));
          char* m_sz = get_mat_size(rvalue);
          CODESHOW(printf("param %s\n", m_sz ));    free(m_sz);
          CODESHOW(printf("call mat_i2f_temp, 2\n"));
          int temp = temp_next();
          CODESHOW(printf("pop $%d\n", temp));

          BLUE("END CAST\n");
          // PAra todos os efeitos, seu endereco antigo nao eh mais conhecido
          // printf("gogogo ! %d\n", temp);
          rvalue->addr = temp;
          // abort();
          right_addr = get_no_addr(rvalue);

          CODESHOW(printf("param $%d    // src =1\n", temp));
          CODESHOW(printf("param %s    // dest\n", get_no_addr(lvalue)));
          CODESHOW(printf("param %s    // qtd \n", get_mat_size(rvalue)));
          CODESHOW(printf("call __copyN, 3\n"));
        } else {  // soh mover (copiar), n precisa converter nada.
          // WARSHOW(printf("no casts\n"));
          CODESHOW(printf("param %s    // src =2\n", get_no_addr(rvalue)));
          CODESHOW(printf("param %s    // dest\n", get_no_addr(lvalue)));
          DBG(printf("Tamanhos: %d, %d", rvalue->temp_mat.line, rvalue->temp_mat.col));
          CODESHOW(printf("param %d    // qtd \n", rvalue->temp_mat.line * rvalue->temp_mat.col  ));
          CODESHOW(printf("call __copyN, 3\n"));
        }
      }
      else if (c1 == TYPE_SCALAR) { 
        DBG(printf("scalar on check_type_and_convert_on_lr_attr"));
        assert(lvalue->child->sym_entry);
        Type t = lvalue->sym_entry->type;
        Type clt = Type_Class(t);
        if( clt != TYPE_SCALAR) {
          DBG(printf("%s", t2s(t)));
          WARSHOW(printf("ahhhhh droga!"));
        }
        if(t1 > t2) { // converter de float <-- float(inteiro)
          int temp = temp_next();
          right_addr = get_no_addr( rvalue );
          BoldCyan();
          printf("\tinttofl ");        
          if(left_addr[0] == '&') printf("%s, ",left_addr + 1);
          else printf("%s, ",left_addr);
          free(left_addr);
          if(right_addr[0] == '&') printf("%s\n",right_addr + 1);
          else printf("%s\n",right_addr);
          free(right_addr);
        } else {
          right_addr = get_no_addr(rvalue);
          BoldCyan();
          printf("\tmov ");
          if(left_addr[0] == '&') printf("%s, ",left_addr + 1);
          else printf("%s, ",left_addr);
          free(left_addr);
          if(right_addr[0] == '&') printf("%s\n",right_addr + 1);
          else printf("%s\n",right_addr);
          free(right_addr);
        }
      }
    }
  } else {
    ERRSHOW(printf("Proibido operar em classes distintas (%s = %s)\n", s1, s2));
  }  
}

// Espera receber um noh que tenha como endereco uma matriz.
// Se for matriz global, gera o cohdigo intermediario necessario. Senao,
// retorna o temporario associado aa matriz local.
char* get_mat_base( No* no ) {
  assert(Type_Class(no->type) == TYPE_MAT);
  char* addr = get_no_addr(no);
  if(addr[0] == '&') {
    int temp = temp_next();
    CODESHOW(printf("mov $%d, %s\n", temp, addr));
    char* buf = calloc(20, sizeof(char));
    sprintf(buf, "$%d", temp);
    free(addr);
    return buf;
  } else {
    return addr; 
  }
}