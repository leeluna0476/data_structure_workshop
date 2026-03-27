#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct node {
	int data;
	struct node *link;
} node_t;

node_t *create_node(int data) {
	node_t *n = (node_t *)malloc(sizeof(node_t));
	n->data = data;
	n->link = NULL;
	return n;
}

int delete_node(node_t *n) {
	int data = n->data;
	free(n);
	return data;
}

typedef struct stack {
	node_t *top;
} stk_t;

void init_stk(stk_t *stk) {
	stk->top = NULL;
}

int is_empty_stk(stk_t *stk) {
	return !stk->top;
}

void push(stk_t *stk, char val) {
	node_t *n = create_node(val);
	if (stk->top) {
		n->link = stk->top;
		stk->top = n;
	}
	else {
		stk->top = n;
	}
}

char pop(stk_t *stk) {
	if (is_empty_stk(stk)) {
		return -1;
	}
	else {
		node_t *n = stk->top;
		stk->top = n->link;
		return delete_node(n);
	}
}

char peek(stk_t *stk) {
	if (is_empty_stk(stk)) {
		return -1;
	}
	else {
		return stk->top->data;
	}
}

int rank(char a) {
	switch (a) {
		case '(': case ')': return 1;
		case '+': case '-': return 2;
		case '*': case '/': return 3;
		default: return 0;
	}
}

int priority(char a, char b) {
	return rank(a) - rank(b);
}

void infix_to_postfix(char *exp) {
	stk_t stk;
	init_stk(&stk);
	while (*exp) {
		if (isupper(*exp)) {
			putchar(*exp);
		}
		else if (*exp == '(') {
			push(&stk, '(');
		}
		else {
			while (!is_empty_stk(&stk) && priority(peek(&stk), *exp) >= 0) {
				char c = pop(&stk);
				if (c == '(') {
					break;
				}
				putchar(c);
			}
			if (*exp != ')') {
				push(&stk, *exp);
			}
		}
		++exp;
	}

	while (!is_empty_stk(&stk)) {
		putchar(pop(&stk));
	}
	putchar('\n');
}

int main(void) {
	char exp[101];
	scanf("%s", exp);
	infix_to_postfix(exp);
}
