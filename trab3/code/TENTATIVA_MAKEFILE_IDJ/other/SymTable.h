#ifndef SYMTABLE_H
#define SYMTABLE_H
#pragma once

extern int numlines, currCol;

typedef struct node{
  // int n;
  int counter;
  int isUsed;
  char * val;
  struct node * next;
  struct node * prev;
} Node;

typedef struct {
  Node * first;
  int isInit;
  int size;
} SymTable;

Node * Node_Init();
SymTable * SymTable_Init();
void SymTable_Destroy(SymTable * table);
Node* SymTable_Insert(SymTable * table, char * sym);
Node* SymTable_Show(SymTable * table);

#endif