#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void push(stk_t *stk, int val) {
	node_t *n = create_node(val);
	if (stk->top) {
		n->link = stk->top;
	}
	stk->top = n;
}

int pop(stk_t *stk) {
	if (is_empty_stk(stk)) {
		return 0;
	}
	else {
		node_t *n = stk->top;
		stk->top = n->link;
		return delete_node(n);
	}
}

int peek(stk_t *stk) {
	if (is_empty_stk(stk)) {
		return 0;
	}
	else {
		return stk->top->data;
	}
}

void destroy_stk(stk_t *stk) {
	while (!is_empty_stk(stk)) {
		pop(stk);
	}
}

#define max(a, b) (a > b ? a : b)

int generate_stack_series(int n) {
	stk_t num;
	init_stk(&num);

	char s[200000];
	char *sp = s;
	int pushed_max = 0;

	for (int i = 0; i < n; ++i) {
		int a;
		scanf("%d", &a);
		for (int j = pushed_max + 1; j <= a; ++j) {
			push(&num, j);
			*sp++ = '+';
		}
		pushed_max = max(pushed_max, a);
		if (peek(&num) < a) {
			destroy_stk(&num);
			return 0;
		}
		pop(&num);
		*sp++ = '-';
	}

	*sp = '\0';
	sp = s;
	while (*sp) {
		printf("%c\n", *sp);
		++sp;
	}

	return 1;
}

int main(void) {
	int n;
	scanf("%d", &n);
	if (!generate_stack_series(n)) {
		printf("NO\n");
	}
}
