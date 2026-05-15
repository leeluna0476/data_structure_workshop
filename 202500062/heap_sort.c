#include <stdio.h>
#include <stdlib.h>

//#define MAX 1024
typedef struct heap {
	int *storage;
	int max;
	int size;
	int (*cmp)(int, int);
} heap_t;

#define PARENT(i) (i >> 1)
#define LEFT(i) (i << 1)
#define RIGHT(i) ((i << 1) + 1)
#define SWAP(a, b, tmp) tmp = a; a = b; b = tmp;

int ascend(int a, int b) {
	return a - b;
}

int descend(int a, int b) {
	return b - a;
}

// m == 0: min heap
// m == 1: max heap
void init_heap(heap_t *hp, int max, int m) {
	static int (*cmp[2])(int, int) = { ascend, descend };

	hp->max = max + 1;
	hp->storage = malloc(sizeof(int) * hp->max);
	hp->size = 0;
	hp->cmp = cmp[!!m];
}

void destroy_heap(heap_t *hp) {
	free(hp->storage);
}

int is_empty_heap(heap_t *hp) {
	return !hp->size;
}

int is_full_heap(heap_t *hp) {
	return hp->size + 1 == hp->max;
}

void add_heap(heap_t *hp, int e) {
	if (is_full_heap(hp)) {
		return;
	}
	else {
		hp->storage[++hp->size] = e;
		int i = hp->size;
		while (i > 1) {
			int p = PARENT(i);
			if (hp->cmp(hp->storage[p], hp->storage[i]) <= 0) {
				break;
			}
			int tmp;
			SWAP(hp->storage[p], hp->storage[i], tmp)
			i = p;
		}
	}
}

int delete_heap(heap_t *hp) {
	if (is_empty_heap(hp)) {
		return -1;
	}
	else {
		int r = hp->storage[1];
		hp->storage[1] = hp->storage[hp->size--];
		int i = 1;
		while (LEFT(i) <= hp->size) {
			int l = LEFT(i);
			int r = RIGHT(i);
			int c = l == hp->size ? l :
				hp->cmp(hp->storage[l], hp->storage[r]) <= 0 ? l : r;
			if (hp->cmp(hp->storage[i], hp->storage[c]) <= 0) {
				break;
			}
			int tmp;
			SWAP(hp->storage[i], hp->storage[c], tmp)
			i = c;
		}
		return r;
	}
}

// time complexity = O(n log2(n))
// stable = false
// in_place = false (구현 방식을 달리하면 제자리정렬 가능)
int *heap_sort(int *arr, int size, char reversed, char copy) {
	heap_t hp;
	init_heap(&hp, size, !!reversed);

	int *p = copy ? malloc(sizeof(int) * size) : arr;
	for (int i = 0; i < size; ++i) {
		add_heap(&hp, arr[i]);
	}

	for (int i = 0; i < size; ++i) {
		p[i] = delete_heap(&hp);
	}

	destroy_heap(&hp);
	return p;
}

void print_arr(int *arr, int size) {
	for (int i = 0; i < size; ++i) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

int main(void) {
	int arr[10] = { 6, 2, 1, 8, 1, 9, 4, 4, 4, 2 };
	int size = sizeof(arr) / sizeof(arr[0]);

	in_place_heap_sort(arr, size);
	print_arr(arr, size);

//	printf("Original:\n");
//	print_arr(arr, size);
//
//	heap_sort(arr, sizeof(arr) / sizeof(arr[0]), 0, 0);
//	printf("Ascending order:\n");
//	print_arr(arr, size);
//
//	int *p2 = heap_sort(arr, sizeof(arr) / sizeof(arr[0]), 1, 1);
//	printf("Descending order:\n");
//	print_arr(p2, size);

//	free(p1);
//	free(p2);
}
//
//// size => O(n)
//void max_heapify(int *arr, int size) {
//	int i = size - 1;
//	while (i) {
//		int p = (i - 1) >> 1;
//		if (arr[i] > arr[p]) {
//			int tmp;
//			SWAP(arr[i], arr[p], tmp)
//		}
//		--i;
//	}
//}
//
//// log2(size) => O(log2n)
//void sift_root(int *arr, int size) {
//	int nsize = size - 1;
//
//	int tmp;
//	SWAP(arr[0], arr[nsize], tmp)
//
//	int i = 0;
//	while ((i << 1) + 1 < nsize) {
//		int l = (i << 1) + 1;
//		int r = (i << 1) + 2;
//		int c = l == nsize - 1 ? l : arr[l] > arr[r] ? l : r;
//		if (arr[i] < arr[c]) {
//			SWAP(arr[i], arr[c], tmp)
//		}
//		i = c;
//	}
//}
//
//// size + size log2(size) => O(n + nlog2n) => O(nlog2n)
//void in_place_heap_sort(int *arr, int size) {
//	max_heapify(arr, size);
//	for (int i = 0; i < size; ++i) {
//		sift_root(arr, size - i);
//	}
//}
