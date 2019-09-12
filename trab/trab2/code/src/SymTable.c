#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SymTable.h"

// typedef struct {
//   int counter;
//   int isUsed;
//   char * val;
//   struct Node * next;
//   struct Node * prev;
// } Node;

// typedef struct  {
//   Node * first;
//   int isInit;
//   int size;
// } SymTable;


void Node_Init(Node * no) {
  no->counter = 0;  no->val = NULL; no->isUsed = 0;
  no->next = NULL; no->prev = NULL;
}

void SymTable_Init(SymTable * table) {
  table->isInit = 1;  table->size = 0;
  table->first = NULL; table->first = malloc(sizeof(Node));
}

void SymTable_Destroy(SymTable * table) {
  if(table != NULL) {
    table->isInit = 0;  table->size = 0;
    free(table->first); table->first = NULL;
  }
}

// Insere na tabela sse nao estah nela ainda. Se estah, aumenta um contador.
void SymTable_Insert(SymTable * table, char * sym) {
  if (table != NULL) {
    if (table->first == NULL) {
      Node_Init(table->first);
    }
    Node * entry = table->first;
    int found = 0;
    while (!found) {
      if(entry->isUsed);
    }
  }
}