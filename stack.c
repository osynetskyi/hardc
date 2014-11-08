#include <stdio.h>
#include <stdlib.h>

struct Node {
	struct Node *next;	
	int value;
};

struct Stack {
	struct Node *top;
};

void Stack_print(struct Stack *stack)
{
	struct Node *cur = stack->top;
	printf("Stacked values are: \n");
	while(cur != NULL) {
		printf("%d\n", cur->value);
		cur = cur->next;
	}
}

struct Node *Node_create(int value) {
	struct Node *current = malloc(sizeof(struct Node));
	current->next = NULL;
	current->value = value;
	return current;
}

void Node_delete(struct Node *node) {
	if(node->next) {
		Node_delete(node->next);
	}
	free(node);
}

struct Stack *Stack_create(struct Node *top) {
	struct Stack *stack = malloc(sizeof(struct Stack));
	stack->top = top;
	return stack;
}

void Stack_delete(struct Stack *stack) {
	if(stack->top) {
		Node_delete(stack->top);
	}
	free(stack);
}

struct Stack *push(struct Stack *stack, int value) {
	struct Node *new = Node_create(value);
	struct Node *old = stack->top;
	stack->top = new;
	new->next = old;
	return stack;
}

int pop(struct Stack *stack) {
	struct Node *new = stack->top->next;
	struct Node *old = stack->top;
	int res = stack->top->value;
	stack->top = new;
	Node_delete(old);
	return res;
}

int main(int argc, char *argv[])
{
	struct Node *node = Node_create(1);
	struct Stack *stack = Stack_create(node);
	Stack_print(stack);
	push(stack, 2);
	Stack_print(stack);
	pop(stack);
	Stack_print(stack);
	return 0;
}
