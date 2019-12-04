#ifndef STACK_H
#define STACK_H

typedef struct Stack{
	int label_sfx;
	struct Stack * next;
} Stack;

int __new_flow;
int __after_if;
int __new_while;
Stack* __new_flow_stack;
Stack* __after_if_stack;


Stack* Stack_New(int v);
Stack* Stack_Push(Stack* stack, int v);

Stack* Stack_Pop(Stack* stack);

int Stack_New_Flow_Push();
int Stack_New_Flow_Pop();

int Stack_After_If_Push();
int Stack_After_If_Pop();
#endif