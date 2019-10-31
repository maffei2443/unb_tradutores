#include <stdlib.h>
#include <stdio.h>
#include "Tree.h"
Field field = SVAL;
void test_add_n(No * head, int n) {
  for(int v = 1; v <= n; v++) {
    add_Child(head, v);  
  }
  free_All_Child(head);
}
void test_add_show_n(No * head, int n) {
  for(int v = 1; v <= n; v++) {
    add_Child(head, v);  
  }
  show_Lis((head)->child, field);
  free_All_Child(head);
}

int main(int argc, char ** argv) {
  No* head;
  head = No_New(0);

  printf("argc: %d\n", argc);
  int caso = 0;
  if(argc > 1) {
    caso = atoi(argv[1]);
  }
  if(0) {
    test_add_show_n(head, caso);
    free(head); head = NULL;
  }
  else {

    add_Node_Child(head, No_New(1));
    add_Node_Child(head, No_New(1));
    
    add_Child(head->child, 2);
    add_Child(head->child, 2);
    add_Child(head->child, 2);

    add_Child(head->child->child, 3);
    add_Child(head->child->child, 3);

    show_Sub_Tree(head, 1, SVAL);

    show_Lis(head, SVAL);
    free_All_Child(head);
    free(head); head = NULL;
  }

}