#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <assert.h>
#include "sort.h"
#include "utils.h"

#define ARRAY_LENGTH 1024

extern int verbose;
int nthreads = 1;
double start, end;
int *arr;
int len = ARRAY_LENGTH;

void usage() {
	printf("prog [-s <arraysize>] [-n <threads>]\n");
	exit(1);
}

void init() {
	arr = (int *)malloc(sizeof(int) * len);
	assert(arr != NULL);
}

void teardown() {
	free(arr);
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
	if(verbose) {
		printf("len=%d\n", len);
	}
	init();

	// sort function declarations
	void (*insertion) (int *, const size_t);
	void (*bitonic)(int *, const size_t, const int);
	void (*radix)(int *, const size_t);
	void (*sample)(int *, const size_t, const int);
	void (*merge)(int *, const size_t);
	void (*qsort_wrap)(int *, const size_t);

	// Sort functions
	insertion = &insertion_sort;
	bitonic = &bitonic_psort;
	radix = &radix_sort;
	sample = &sample_sort;
	merge = &merge_sort;
	qsort_wrap = &qsort_wrapper;

	//run_sort_tests(insertion, "Insert", arr, len);
	run_psort_tests(bitonic, "Bitonic", arr, len, (const int) nthreads);
	// run_sort_tests(radix, "Radix", arr, len);
	run_psort_tests(sample, "Sample", arr, len, (const int) nthreads);
	// run_sort_tests(merge, "Merge", arr, len);
	// run_sort_tests(qsort_wrap, "stdlib::qsort", arr, len);

	teardown();
	return 0;
}
