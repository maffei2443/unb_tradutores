// Agradecimentos
#ifndef ARRAY_H
#define ARRAY_H
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

Array* Array_New();
void Array_Init(Array * a, size_t initSize);
void Array_Insert(Array * a, char * other);
void Array_Delete(Array* a);

#endif