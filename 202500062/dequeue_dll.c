#include <stdlib.h>
#include <stdio.h>

typedef int Element;

void error(char *errmsg);

typedef struct node {
	Element data;
	struct node *front;
	struct node *back;
} node_t;

node_t *create_node(Element data);
Element delete_node(node_t *n);

// doubly-linked dequeue
typedef struct dequeue {
	node_t *rear;
} dequeue_t;

void init_dequeue(dequeue_t *dq);
int is_empty_dequeue(dequeue_t *dq);
int is_full_dequeue(dequeue_t *dq);

void link_node(dequeue_t *dq, node_t *n);
void unlink_node(node_t *n);

void add_front(dequeue_t *dq, Element e);
void add_rear(dequeue_t *dq, Element e);
Element delete_front(dequeue_t *dq);
Element delete_rear(dequeue_t *dq);
Element get_front(dequeue_t *dq);
Element get_rear(dequeue_t *dq);

#include <string.h>

typedef struct stack {
	dequeue_t dq;
	int size;
} stk_t;

void init_stk(stk_t *stk) {
	init_dequeue(&stk->dq);
	stk->size = 0;
}

void push(stk_t *stk, int e) {
	add_rear(&stk->dq, e);
	++stk->size;
}

int is_empty_stk(stk_t *stk) {
	return !stk->size;
}

int pop(stk_t *stk) {
	if (is_empty_stk(stk)) {
		return -1;
	}
	else {
		--stk->size;
		return delete_rear(&stk->dq);
	}
}

int size_stk(stk_t *stk) {
	return stk->size;
}

int peek(stk_t *stk) {
	if (is_empty_stk(stk)) {
		return -1;
	}
	else {
		return get_rear(&stk->dq);
	}
}

int main(void) {
	int N;
	scanf("%d", &N);
	stk_t stk;
	init_stk(&stk);
	char op[6];
	for (int i = 0; i < N; ++i) {
		scanf("%s", op);
		if (!strcmp(op, "push")) {
			int x;
			scanf("%d", &x);
			push(&stk, x);
		}
		else if (!strcmp(op, "pop")) {
			printf("%d\n", pop(&stk));
		}
		else if (!strcmp(op, "size")) {
			printf("%d\n", size_stk(&stk));
		}
		else if (!strcmp(op, "empty")) {
			printf("%d\n", is_empty_stk(&stk));
		}
		else {
			printf("%d\n", peek(&stk));
		}
	}
	while (!is_empty_stk(&stk)) {
		pop(&stk);
	}
}

void error(char *errmsg) {
	fprintf(stderr, "%s", errmsg);
	exit(1);
}

node_t *create_node(Element data) {
	node_t *n = (node_t *)malloc(sizeof(node_t));
	n->data = data;
	n->front = NULL;
	n->back = NULL;
	return n;
}

Element destroy_node(node_t *node) {
	Element data = node->data;
	free(node);
	return data;
}

void init_dequeue(dequeue_t *dq) {
	dq->rear = NULL;
}

int is_empty_dequeue(dequeue_t *dq) {
	return !dq->rear;
}

// unnecessary
int is_full_dequeue(dequeue_t *dq) {
	return 0;
}

void link_node(dequeue_t *dq, node_t *n) {
	if (is_empty_dequeue(dq)) {
		n->back = n;
		n->front = n;
		dq->rear = n;
	}
	else {
		node_t *first = dq->rear->back;
		n->back = first;
		n->front = dq->rear;
		first->front = n;
		dq->rear->back = n;
	}
}

// n1(rear)
// n2<->n1(rear)
// n3<->n2<->n1(rear)<->n3
void add_front(dequeue_t *dq, Element e) {
	node_t *n = create_node(e);
	link_node(dq, n);
}

// n1(rear)
// n1<->n2(rear)<->n1
// n1<->n2<->n3(rear)<->n1
void add_rear(dequeue_t *dq, Element e) {
	node_t *n = create_node(e);
	link_node(dq, n);
	dq->rear = n;
}

void unlink_node(node_t *n) {
	n->back->front = n->front;
	n->front->back = n->back;
}

// n1<->n2<->n3(rear)<->n1
Element delete_front(dequeue_t *dq) {
	if (is_empty_dequeue(dq)) {
		error("Underflow\n");
	}
	else {
		node_t *n = dq->rear->back;
		unlink_node(n);
		if (n->back == n) {
			dq->rear = NULL;
		}
		return destroy_node(n);
	}
}

Element delete_rear(dequeue_t *dq) {
	if (is_empty_dequeue(dq)) {
		error("Underflow\n");
	}
	else {
		node_t *n = dq->rear;
		unlink_node(n);
		dq->rear = n->front;
		if (n->back == n) {
			dq->rear = NULL;
		}
		return destroy_node(n);
	}
}

Element get_front(dequeue_t *dq) {
	if (is_empty_dequeue(dq)) {
		error("Underflow\n");
	}
	else {
		return dq->rear->back->data;
	}
}

Element get_rear(dequeue_t *dq) {
	if (is_empty_dequeue(dq)) {
		error("Underflow\n");
	}
	else {
		return dq->rear->data;
	}
}
