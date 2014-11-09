#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

struct Node {
	struct Node *next;	
	int value;
};

struct Stack {
	struct Node *top;
};

void Stack_delete(struct Stack *stack);

void die(const char *message, struct Stack *stack)
{
	if(errno) {
		perror(message);
	} else {
		printf("ERROR: %s\n", message);
	}

	Stack_delete(stack);
	exit(1);
}

void Stack_print(struct Stack *stack)
{
	if(!stack->top) {
		printf("Stack is empty\n");
	} else {
		struct Node *cur = stack->top;
		printf("Stacked values are: \n");
		while(cur != NULL) {
			printf("%d ", cur->value);
			cur = cur->next;
		}
		printf("\n");
	}
}

struct Node *Node_create(int value) {
	//printf("Memory for node %d allocated\n", value);
	struct Node *current = malloc(sizeof(struct Node));
	/*if(!current) {
		die("Memory error!");
	}*/
	current->next = NULL;
	current->value = value;
	return current;
}

void Node_delete(struct Node *node) {
	if(node->next) {
		Node_delete(node->next);
	}
	if(node) {
		//printf("Memory from node %d freed\n", node->value);
		free(node);
	}
}

struct Stack *Stack_create(struct Node *top) {
	//printf("Memory for stack allocated\n");
	struct Stack *stack = malloc(sizeof(struct Stack));
	if(!stack) {
		die("Memory error!", stack);
	}
	stack->top = top;
	return stack;
}

void Stack_delete(struct Stack *stack) {
	if(stack->top) {
		Node_delete(stack->top);
	}
	//printf("Memory from stack freed\n");
	free(stack);
}

struct Stack *push(struct Stack *stack, int value) {
	struct Node *new = Node_create(value);
	struct Node *old = stack->top;
	stack->top = new;
	new->next = old;
	printf("Pushed %d into stack\n", value);
	return stack;
}

int pop(struct Stack *stack) {
	if(!stack->top) {
		die("Stack is empty!", stack);
	}
	struct Node *new = stack->top->next;
	struct Node *old = stack->top;
	int res = stack->top->value;
	stack->top = new;
	old->next = NULL;
	Node_delete(old);
	return res;
}

int main(int argc, char *argv[])
{
	struct Stack *stack = Stack_create(Node_create(1));
	Stack_print(stack);
	push(stack, 2);
	Stack_print(stack);
	int res = pop(stack);
	printf("Popped %d from stack\n", res);
	push(stack, 3);
	push(stack, 4);
	push(stack, 5);
	Stack_print(stack);
	res = pop(stack);
	printf("Popped %d from stack\n", res);
	res = pop(stack);
	printf("Popped %d from stack\n", res);
	res = pop(stack);
	printf("Popped %d from stack\n", res);
	res = pop(stack);
	printf("Popped %d from stack\n", res);
	res = pop(stack);
	printf("Popped %d from stack\n", res);
	Stack_print(stack);
	Stack_delete(stack);

	return 0;
}
