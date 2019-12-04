#include "Stack.h"
#include <stdio.h>
#include <stdlib.h>

int __new_flow = 0;
int __new_while = 0;
int __after_if = 0;
// Devem ser usados como prefixos de labels
Stack* __new_flow_stack = NULL;
Stack* __after_if_stack = NULL;

Stack* Stack_New(int v) {
	Stack* neo = calloc(1,sizeof(Stack));
	neo->next = NULL;
  neo->label_sfx = v;
	return neo;
}

Stack* Stack_Push(Stack* stack, int v) {
	if(stack) {
		Stack* neo = Stack_New(v);
		neo->next = stack;
		return neo;
	} else {
		Stack* neo = Stack_New(v);
		return neo;
	}
}

Stack* Stack_Pop(Stack* stack) {
	if(!stack) {
		printf("[Warning] Pop em pilha vazia\n");
		return NULL;
	}
	else {
		Stack* next = stack->next;
		free(stack);
		return next;
	}
}

int Stack_New_Flow_Push() {
  int to_push = __new_flow;
  __new_flow_stack = Stack_Push(__new_flow_stack, to_push);
  __new_flow++;
  return to_push;
}

int Stack_New_Flow_Pop() {
  int v = __new_flow_stack->label_sfx;
  Stack_Pop(__new_flow_stack);
  return v;
}

int Stack_After_If_Push() {
  int ret = __after_if;
  __after_if_stack = Stack_Push(__after_if_stack, __after_if);
  ret ++;
  return ret;
}

int Stack_After_If_Pop() {
  int v = __after_if_stack->label_sfx;
  Stack_Pop(__after_if_stack);
  return v;
}