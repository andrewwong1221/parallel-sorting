#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "sort.h"
#include "utils.h"
#include "hrtimer_x86.h"

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
	int *orig = (int *) calloc(len, sizeof(int));
	int i;
	double start, end;
	printf("========================\n");
	printf("%s Sort\n", name);
	printf("========================\n");
	/* Reverse array */
	printf("Reverse test\n");
	create_reverse(orig, len);
	create_copy(copy, orig, len);
	radix_sort(copy, len);
	double total = 0;
	for(i = 0; i < ITER; i++) {
		create_copy(arr, orig, len);
		start = gethrtime_x86();
		sortfunc(arr, len, threads);
		end = gethrtime_x86();
		printf("%i: %f\n", i, end-start);
		total += end-start;
		assert(validate_sort(arr, copy, len) != 0);
	}
	printf("Time: %f\n", total/(ITER * 1.0));

	/* Random array */
	printf("Random test\n");
	create_random(orig, len);
	create_copy(copy, orig, len);
	radix_sort(copy, len);
	total = 0;
	for(i = 0; i < ITER; i++) {
		create_copy(arr, orig, len);
		start = gethrtime_x86();
		sortfunc(arr, len, threads);
		end = gethrtime_x86();
		printf("%i: %f\n", i, end-start);
		total += end-start;
		assert(validate_sort(arr, copy, len) != 0);
	}
	printf("Time: %f\n", total/(ITER*1.0));
	printf("%s passed!\n", name);
	
	printf("------------------------\n");
}

/* Sequential sort tests */
void run_sort_tests(void (*sortfunc)(int *, const size_t),
		const char* name, int *arr, const size_t len) {
	int *orig = (int *) calloc(len, sizeof(int));
	int *copy = (int *) calloc(len, sizeof(int));
	int i;
	double start, end;
	printf("========================\n");
	printf("%s Sort\n", name);
	printf("========================\n");
	/* Reverse array */
	printf("Reverse test\n");
	create_reverse(orig, len);
	create_copy(copy, orig, len);
	radix_sort(copy, len);
	double total = 0;
	for(i = 0; i < ITER; i++) {
		create_copy(arr, orig, len);
		start = gethrtime_x86();
		sortfunc(arr, len);
		end = gethrtime_x86();
		printf("%i: %f\n", i, end-start);
		total += end-start;
		assert(validate_sort(arr, copy, len) != 0);
	}

	printf("Time: %f\n", total/(ITER * 1.0));

	/* Random array */
	printf("Random test\n");
	create_random(orig, len);
	create_copy(copy, orig, len);
	radix_sort(copy, len);
	total = 0;
	for(i = 0; i < ITER; i++) {
		create_copy(arr, orig, len);
		start = gethrtime_x86();
		sortfunc(arr, len);
		end = gethrtime_x86();
		total += end-start;
		printf("%i: %f\n", i, end-start);
		assert(validate_sort(arr, copy, len) != 0);
	}
	printf("Time: %f\n", total/(ITER*1.0));
	printf("%s passed!\n", name);
	
	printf("------------------------\n");
}
