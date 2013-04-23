#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <assert.h>
#include "sort.h"
#include "utils.h"

#define ARRAY_LENGTH 1024

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
	// bitonic_test();
	// radix_test();
	void (*bitonic)(int *, const size_t, const int threads);
	void (*radix)(int *, const size_t, const int threads);
	bitonic = &bitonic_psort;
	radix = &radix_psort;

	run_sort_tests(bitonic, "Bitonic", arr, len, (const int) nthreads);
	run_sort_tests(radix, "Radix", arr, len, (const int) nthreads);

	return 0;
}
