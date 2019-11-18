#include "Array.h"

void Array_Init(Array * a, size_t initSize) {
  a->array = (char*)calloc(initSize, sizeof(char));
  a->used = 0; a->size = initSize;
}

void Array_Insert(Array * a, char * other) {
  size_t tam = strlen(other);
  // printf("TAM: %lu\n", tam);
  if(a->used + tam + 1 >= a->size) {
    a->size = (a->used + tam) * 2 + 1;
    a->array = (char*)realloc(a->array, a->size * sizeof(char));
  }
  memcpy(  a->array + a->used, other, (tam+1) * sizeof(char) ); 
  a->used += tam;
  // com tamanho necessario alocado, comecem os jogos...
}

void Array_Delete(Array* a) {
  if(a->size > 0) {
    free(a->array);
    a->array = NULL;
    a->used = 0;
    a->size = 0;
  }
}
