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


Node * Node_Init() {
  Node * no = malloc(sizeof(no));
  no->counter = 0;  no->val = NULL; no->isUsed = 0;
  no->next = NULL; no->prev = NULL;
  return no;
}

SymTable * SymTable_Init() {
  SymTable * table = malloc(sizeof(SymTable));
  table->isInit = 1;  table->size = 0;
  table->first = NULL; table->first = malloc(sizeof(Node));
  return table;
}

void SymTable_Destroy(SymTable * table) {
  if(table != NULL) {
    table->isInit = 0;  table->size = 0;
    free(table->first); table->first = NULL;
  }
}

// Insere na tabela sse nao estah nela ainda. Se estah, aumenta um contador.
Node* SymTable_Insert(SymTable * table, char * sym) {
  if (table == NULL) abort();
  if (table->first == NULL) {
    table->first = Node_Init();
  }
  Node * entry = table->first;
  Node * prev = table->first->prev;
  int found = 0;
  while (!found && entry->isUsed) {
    if (strcmp(sym, entry->val) == 0) {  // se achou na tabela, counter++
      found = 1;
      ++entry->counter;// printf("eq\n");
    }
    else if (entry->next != NULL) {
      prev = entry;  entry = entry->next;// printf("next\n");
    }
    else if (entry->next == NULL) {  // proximo eh NULL; portanto inserir ali
      entry->next = Node_Init(); // printf("EOL\n");
      prev = entry;  entry = entry->next;//      printf("alloc\n");
      break;
    }
  }
  // Entao nao estah usado o entry, MAS estah alocado!
  if(!found) {
    // printf("hula\n");printf("it->prev == NULL? %d\n", entry->prev == NULL);printf("prev? %p\n", prev);
    entry->prev = prev;
    entry->val = malloc(sizeof(char) * strlen(sym));
    strcpy(entry->val, sym); entry->isUsed = 1;
    entry->counter++;
  }
  entry->prev = prev;
  return entry;
}
