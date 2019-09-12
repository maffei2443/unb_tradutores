// Agradecimentos
#pragma once
// https://stackoverflow.com/questions/3536153/c-dynamically-growing-array

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
  char* array;
  size_t used;
  size_t size;
} Array;


extern void Array_Init(Array * a, size_t initSize);
extern void Array_Insert(Array * a, char * other);
extern void Array_Delete(Array* a);



// int main() {
//   Array buf;
//   Array_Init(&buf, 20);
//   while(1) {
//     char * pt;
//     pt = malloc(sizeof(char) * 20);
//     scanf("%s", pt);
//     printf("%s\n", pt);
//     Array_Insert(&buf, pt);
//     printf("Sum: %s\n", buf.array);
//     if (!strcmp("quit", pt)){
//       pt = NULL;
//       free(pt);
//       break;
//     }
//     free(pt);
//   }
//   Array_Delete(&buf);
// }