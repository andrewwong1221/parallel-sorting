#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "sort.h"

void print_array(int *arr, int len) {
	int i;
	for(i = 0 ; i < len; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

int validate_sort(int *arr, int *copy, int len) {
	int i;
	int ordered = 1;
	for(i = 0; i < len; i++) {
		if(arr[i] != copy[i]) {
			ordered = 0;
		}
	}
#if DEBUG
	if(!ordered) {
		for(i = 1; i < len; i++) {
			if(arr[i-1] > arr[i]) {
				printf("Error at a[%d] == %d and a[%d] == %d\n", i-1, arr[i-1], i, arr[i]);
			}
		}
	}
#endif
	return ordered;
}

void create_copy(int *copy, int *arr, int len) {
	int i; 
	for(i = 0; i < len; i++) {
		copy[i] = arr[i];
	}
}

void create_reverse(int *arr, int len) {
	int i;
	for(i = 0; i < len; i++) {
		arr[i] = len - i;
	}

}

void create_random(int *arr, int len) { 
	int i;
	for(i = 0; i < len; i++)
		arr[i] = rand();
}

/* Four calls to random then divide by four */
void create_gauss(int *a, int len) {
	int i;
	for(i = 0; i < len; i++) {
		a[i] = rand();
		a[i] += rand();
		a[i] += rand();
		a[i] += rand();
		a[i] /= 4;
	}
}

/* Fill the array with zeros */
void create_zero(int *a, int len) {
	int i;
	for(i = 0; i < len; i++) {
		a[i] = 0;
	}
}

void create_duplicates(int *a, int len) {
	int i;
	for(i = 0; i < len; i++) {
		a[i] = rand() % (len / 2);
	}

}

void run_psort_tests(void (*sortfunc)(int *, const size_t, const int),
		const char* name, int *arr, const size_t len, const int threads) {
	int *copy = (int *) calloc(len, sizeof(int));
	printf("========================\n");
	printf("%s Sort\n", name);
	printf("========================\n");
	/* Reverse array */
	printf("Reverse test\n");
	create_reverse(arr, len);
	create_copy(copy, arr, len);
	radix_sort(copy, len);
	sortfunc(arr, len, threads);
	assert(validate_sort(arr, copy, len) != 0);

	/* Random array */
	printf("Random test\n");
	create_random(arr, len);
	create_copy(copy, arr, len);
	radix_sort(copy, len);
	sortfunc(arr, len, threads);
	assert(validate_sort(arr, copy, len) != 0);
	printf("%s passed!\n", name);
	
	printf("------------------------\n");
}

/* Sequential sort tests */
void run_sort_tests(void (*sortfunc)(int *, const size_t),
		const char* name, int *arr, const size_t len, const int threads) {
	int *copy = (int *) calloc(len, sizeof(int));
	printf("========================\n");
	printf("%s Sort\n", name);
	printf("========================\n");
	/* Reverse array */
	printf("Reverse test\n");
	create_reverse(arr, len);
	create_copy(copy, arr, len);
	radix_sort(copy, len);
	sortfunc(arr, len);
	assert(validate_sort(arr, copy, len) != 0);

	/* Random array */
	printf("Random test\n");
	create_random(arr, len);
	create_copy(copy, arr, len);
	radix_sort(copy, len);
	sortfunc(arr, len);
	assert(validate_sort(arr, copy, len) != 0);
	printf("%s passed!\n", name);
	
	printf("------------------------\n");
}
