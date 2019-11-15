#include <stdlib.h>
#include <stdio.h>

unsigned long *b;
int bMax = 1;
int bSize = 0;

void insert(unsigned long addr) {
  printf("insert: %u\n", addr);
  if(bSize + 1 >= bMax) {
    b = realloc(b, bMax);
    bMax *= 2;
  }
  b[bSize] = addr;
  bSize++;
}
