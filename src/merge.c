/*
 * Algorithm referenced from:
 * http://en.literateprograms.org/Merge_sort_(C)
 */
#include <stdio.h>
#include <string.h>
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

