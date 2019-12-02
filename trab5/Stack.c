#include "Stack.h"
#include <stdio.h>
#include <stdlib.h>

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
