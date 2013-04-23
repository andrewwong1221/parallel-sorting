#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void print_array(int *arr, int len) {
	int i;
	for(i = 0 ; i < len; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

int validate_sort(int *arr, int len) {
	int i;
	int order = 1;
	for(i = 1; i < len; i++) {
		if(arr[i-1] > arr[i]) {
			order = 0;
		}
	}
	return order;
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

void run_sort_tests(void (*sortfunc)(int *, const size_t, const int),
		const char* name, int *arr, const size_t len, const int threads) {
	printf("========================\n");
	printf("%s Sort\n", name);
	printf("========================\n");
	/* Reverse array */
	printf("Reverse test\n");
	create_reverse(arr, len);
	sortfunc(arr, len, threads);
	assert(validate_sort(arr,len) != 0);

	/* Random array */
	printf("Random test\n");
	create_random(arr, len);
	sortfunc(arr, len, threads);
	assert(validate_sort(arr,len) != 0);
	printf("%s passed!\n", name);
	
	printf("------------------------\n");
}
