#include <stdlib.h>
#include <stdio.h>

typedef int Element;
typedef struct node {
	Element data;
	struct node *next;
} node_t;

node_t *create_node(Element data) {
	node_t *n = (node_t *)malloc(sizeof(node_t));
	n->data = data;
	n->next = NULL;
	return n;
}

Element delete_node(node_t *n) {
	Element data = n->data;
	free(n);
	return data;
}

// head ptr VS head node
typedef struct list {
	node_t *head; // head ptr
	int size;
} list_t;

void init_list(list_t *l) {
	l->head = NULL;
	l->size = 0;
}

int is_empty_list(list_t *l) {
	return !l->head; // or !l->size
}

// is_full: optional

void error(char *errmsg) {
	fprintf(stderr, "%s", errmsg);
	exit(1);
}

// returns NULL if pos < 0 or pos >= size
node_t *get_node(node_t *head, int pos) {
	if (pos < 0) {
		return NULL;
	}
	else {
		node_t *n = head;
		int cnt = 0;
		while (n && cnt < pos) {
			n = n->next;
			++cnt;
		}
		return n;
	}
}

void insert(list_t *l, int pos, Element e) {
	if (pos < 0 || pos > l->size) {
		error("index out of range\n");
	}
	else {
		node_t *n = create_node(e);
		if (!pos) {
			n->next = l->head;
			l->head = n;
		}
		else {
			node_t *prev = get_node(l->head, pos - 1);
			n->next = prev->next;
			prev->next = n;
		}
		++l->size;
	}
}

Element delete(list_t *l, int pos) {
	if (pos < 0 || pos >= l->size) {
		error("index out of range\n");
	}
	else if (is_empty_list(l)) {
		error("underflow\n");
	}
	else {
		node_t *n;
		if (!pos) {
			n = l->head;
			l->head = n->next;
		}
		else {
			node_t *prev = get_node(l->head, pos - 1);
			n = prev->next;
			prev->next = n->next;
		}
		--l->size;
		return delete_node(n);
	}
}

Element get_entry(list_t *l, int pos) {
	if (pos < 0 || pos >= l->size) {
		error("index out of range\n");
	}
	else if (is_empty_list(l)) {
		error("underflow\n");
	}
	else {
		return get_node(l->head, pos)->data;
	}
}

int size_list(list_t *l) {
	return l->size;
}

int main(void) {
	list_t l;
	init_list(&l);

	int A[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	for (int i = 0; i < sizeof(A) / sizeof(A[0]); ++i) {
		printf("INSERT(%d, %d)\n", i, A[i]);
		insert(&l, i, A[i]);
	}

	for (int i = 0; i < sizeof(A) / sizeof(A[0]); ++i) {
		printf("GET_ENTRY(%d)=%d\n", i, get_entry(&l, i));
	}

	printf("DELETE(%d)=%d\n", 5, delete(&l, 5));
	for (int i = 0; i < size_list(&l); ++i) {
		printf("GET_ENTRY(%d)=%d\n", i, get_entry(&l, i));
	}

//	printf("=====DELETE(size-1)=====\n");
//	for (int i = 0; i < sizeof(A) / sizeof(A[0]); ++i) {
//		printf("%d\n", delete(&l, 0));
//	}
//	insert(&l, 1, 1);
}
