#ifndef SYMTABLE_H
#define SYMTABLE_H
#pragma once

typedef struct {
  int counter;
  int isUsed;
  char * val;
  struct Node * next;
  struct Node * prev;
} Node;

typedef struct  {
  Node * first;
  int isInit;
  int size;
} SymTable;

void Node_Init(Node * no);
void SymTable_Init(SymTable * table);
void SymTable_Destroy(SymTable * table);
void SymTable_Insert(SymTable * table, char * sym);

#endif