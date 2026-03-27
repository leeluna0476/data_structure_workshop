#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MENU 200000
#define MAX_CUSTOMERS 100000

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

typedef struct queue {
	node_t *rear;
} queue_t;

int is_empty_q(queue_t *q) {
	return !q->rear;
}

void enqueue(queue_t *q, int val) {
	node_t *n = create_node(val);
	if (is_empty_q(q)) {
		q->rear = n;
		n->link = n;
	}
	else {
		n->link = q->rear->link;
		q->rear->link = n;
		q->rear = n;
	}
}

int dequeue(queue_t *q) {
	if (is_empty_q(q)) {
		return -1;
	}
	else {
		node_t *front = q->rear->link;
		q->rear->link = front->link;
		if (front == q->rear) {
			q->rear = NULL;
		}
		return delete_node(front);
	}
}

int main(void) {
	int n, m;
	scanf("%d %d", &n, &m);

	queue_t menulist[MAX_MENU + 1] = { 0, };

	for (int i = 0; i < n; ++i) {
		int k;
		scanf("%d", &k);
		for (int j = 0; j < k; ++j) {
			int a;
			scanf("%d", &a);
			enqueue(&menulist[a], i);
		}
	}

	int customers[MAX_CUSTOMERS] = { 0, };
	for (int i = 0; i < m; ++i) {
		int b;
		scanf("%d", &b);
		if (!is_empty_q(&menulist[b])) {
			int c = dequeue(&menulist[b]);
			++customers[c];
		}
	}

	for (int i = 0; i < n; ++i) {
		printf("%d ", customers[i]);
	}
	printf("\n");
}
