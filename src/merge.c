/*
 * Algorithm referenced from:
 * http://en.literateprograms.org/Merge_sort_(C)
 */
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <pthread.h>
#include "sort.h"
#include "utils.h"
#define MAX(A,B) ((A)>(B) ? (A) : (B))
#define MIN(A,B) ((A)>(B) ? (B) : (A))

static void init();
static void teardown();
static void sort_array(int *a, const size_t len);
static void merge_arrays(int *a, const size_t lena, int *b, const size_t lenb);

static size_t totallen;
static int *buffer;

static void init() {
	buffer = (int *) calloc(sizeof(int), totallen);
}
static void teardown() {
	free(buffer);
}

void merge_sort(int *a, const size_t len) {
	totallen = len;
	init();
	sort_array(a, len);
	teardown();
}

static void sort_array(int *a, const size_t len) {
	if(len <= 1) {
		return;
	}
	int m = len/2;
	sort_array(a, m);
	sort_array(a+m, len - m);
	merge_arrays(a, m, a+m, len - m);
	memcpy(a, buffer, len*sizeof(int));
}

static void merge_arrays(int *a, const size_t lena, int *b, const size_t lenb) {
	int i1 = 0, i2 = 0, ib = 0;
	// Compare two lists
	while(i1 < lena && i2 < lenb) {
		if(a[i1] <= b[i2]) {
			buffer[ib] = a[i1];
			i1++;
		}
		else {
			buffer[ib] = b[i2];
			i2++;
		}
		ib++;
	}
	// Copy remaining values
	while(i1 < lena) {
		buffer[ib] = a[i1];
		i1++;
		ib++;
	}
	while(i2 < lenb) {
		buffer[ib] = b[i2];
		i2++;
		ib++;
	}
}

void two_way_merge(int *a, const size_t len) {
	buffer = (int *) malloc(sizeof(int) * len);
	if(buffer == NULL) {
		perror("NOT ENOUGH MEMORY");
	}
	int m = len / 2;
	merge_arrays(a, m, a+m, len - m);
	memcpy(a, buffer, len*sizeof(int));
	free(buffer);
}

void k_way_merge(int *a, int **arrs, const size_t len, int k) {
	int *counter = (int *)malloc(sizeof(int) * k);
	// Must be divisible
	int sectsize = len / k;
	int i;
	for(i = 0; i < k; i++) {
		counter[i] = 0;
	}
	for(i = 0; i < len; i++) {
		// Find min
		int j;
		int min = INT_MAX, minidx = 0;
		for(j = 0; j < k; j++) {
			if(counter[j] < sectsize && arrs[j][counter[j]] < min) {
				min = arrs[j][counter[j]];
				minidx = j;
			}
		}
		a[i] = arrs[minidx][counter[minidx]];
		counter[minidx]++;
	}
	free(counter);
}

