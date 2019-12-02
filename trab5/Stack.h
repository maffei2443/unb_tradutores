#ifndef STACK_H
#define STACK_H

typedef struct Stack{
	int label_sfx;
	struct Stack * next;
} Stack;

Stack* Stack_New(int v);
Stack* Stack_Push(Stack* stack, int v);

Stack* Stack_Pop(Stack* stack);

#endif