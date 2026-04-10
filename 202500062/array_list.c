#include <stdio.h>
#include <stdlib.h>

typedef int Element;
#define MAX 16
typedef struct list {
	Element storage[MAX];
	int size;
} list_t;

void init_list(list_t *l) {
	l->size = 0;
}

int is_empty_list(list_t *l) {
	return !l->size;
}

int is_full_list(list_t *l) {
	return l->size == MAX;
}

int error(char *errmsg) {
	fprintf(stderr, "%s", errmsg);
	return -1;
//	exit(1);
}

// pos = 1, e = 4
// [1][2][3][ ][ ][ ]
// [1][4][2][3][ ][ ]
void insert(list_t *l, int pos, Element e) {
	if (is_full_list(l)) {
		error("overflow\n");
	}
	else if (pos < 0 || pos > l->size) {
		error("index out of range\n");
	}
	else {
		for (int i = l->size; i > pos; --i) {
			l->storage[i] = l->storage[i - 1];
		}
		l->storage[pos] = e;
		++l->size;
	}
}

// pos = 1
// [1][4][2][3][ ][ ]
// [1][2][3][ ][ ][ ]
Element delete(list_t *l, int pos) {
	if (is_empty_list(l)) {
		return error("underflow\n");
	}
	else if (pos < 0 || pos >= l->size) {
		return error("index out of range\n");
	}
	else {
		Element e = l->storage[pos];
		for (int i = pos; i < l->size - 1; ++i) {
			l->storage[i] = l->storage[i + 1];
		}
		--l->size;
		return e;
	}
}

Element get_entry(list_t *l, int pos) {
	if (is_empty_list(l)) {
		return error("underflow\n");
	}
	else if (pos < 0 || pos >= l->size) {
		return error("overflow\n");
	}
	else {
		return l->storage[pos];
	}
}

int size_list(list_t *l) {
	return l->size;
}

typedef struct stack {
	list_t l;
} stk_t;

void init_stk(stk_t *stk) {
	init_list(&stk->l);
}

int is_full_stk(stk_t *stk) {
	return is_full_list(&stk->l);
}

int is_empty_stk(stk_t *stk) {
	return is_empty_list(&stk->l);
}

void push(stk_t *stk, Element e) {
	if (is_full_stk(stk)) {
		error("overflow\n");
	}
	else {
		insert(&stk->l, size_list(&stk->l), e);
	}
}

Element pop(stk_t *stk) {
	if (is_empty_stk(stk)) {
		return error("underflow\n");
	}
	else {
		return delete(&stk->l, size_list(&stk->l) - 1);
	}
}

Element peek(stk_t *stk) {
	return get_entry(&stk->l, size_list(&stk->l) - 1);
}

int main(void) {
	list_t l;
	init_list(&l);

	int A[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	for (int i = 0; i < sizeof(A) / sizeof(A[0]); ++i) {
		insert(&l, i, A[i]);
	}

	printf("=====GET_ENTRY=====\n");
	for (int i = 0; i < sizeof(A) / sizeof(A[0]); ++i) {
		printf("%d\n", get_entry(&l, i));
	}

	printf("=====DELETE(size-1)=====\n");
	for (int i = 0; i < sizeof(A) / sizeof(A[0]); ++i) {
		printf("%d\n", delete(&l, size_list(&l) - 1));
	}
	insert(&l, 1, 1);
}
