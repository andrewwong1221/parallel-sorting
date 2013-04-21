#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <assert.h>
#include "sort.h"
#include "utils.h"

#define ARRAY_LENGTH 1024

static void bitonic_test();
static void radix_test();

int verbose = 0;
int nthreads = 1;
double start, end;
int *arr;
int len = ARRAY_LENGTH;

void usage() {
	printf("prog [-s <arraysize>] [-n <threads>]\n");
	exit(1);
}

extern char *optarg;
int main(int argc, char *argv[]) {
	int i;
	while((i = getopt(argc, argv, "s:n:v")) != -1) {
		switch(i) {
			case 's':
				// Fix this later
				len = atoi(optarg);
				if(len < 1)
					usage();
				break;
			case 'n':
				// Set number of threads
				nthreads = atoi(optarg);
				// Currently assumes the user isn't stupid
				if(nthreads < 1)
					usage();
				break;
			case 'v':
				verbose = 1;
				break;
			default:
				usage();
				break;
		}
	}
	printf("len=%d\n", len);
	arr = (int *)malloc(sizeof(int) * len);
	bitonic_test();
	radix_test();
	return 0;
}
void bitonic_test() {
	printf("========================\n");
	printf("Bitonic Sort\n");
	printf("========================\n");

	/* Reverse array */
	printf("Reverse test\n");
	create_reverse(arr, len);
	// Sort the array
	bitonic_psort(arr, len, nthreads);
	// print_array(arr,len);
	//printf("SORTED: %d\n", validate_sort(arr, len));
	assert(validate_sort(arr,len) != 0);

	printf("Random test\n");
	/* Random Array */
	create_random(arr, len);
	bitonic_psort(arr, len, nthreads);
	// Ensure the array is sorted
	// printf("SORTED: %d\n", validate_sort(arr, len));
	assert(validate_sort(arr,len) != 0);

	printf("Bitonic Passed!\n");
	printf("------------------------\n");
}


void radix_test() {
	printf("========================\n");
	printf("Radix Sort\n");
	printf("========================\n");

	/* Reverse array */
	printf("Reverse test\n");
	create_reverse(arr, len);
	radix_sort(arr, len);
	// printf("Sorted: %d\n", validate_sort(arr,len));
	assert(validate_sort(arr,len) != 0);

	/* Random array */
	printf("Random test\n");
	create_random(arr, len);
	radix_sort(arr, len);
	assert(validate_sort(arr,len) != 0);
	// printf("Sorted: %d\n", validate_sort(arr,len));
	printf("Radix Passed!\n");
	printf("------------------------\n");

}


