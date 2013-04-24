/*
 * Algorithm based of the discussion here:
 * http://www.umiacs.umd.edu/research/EXPAR/papers/spaa96/node7.html
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include "sort.h"
#include "utils.h"
#define SAMPLES 5
#define DEBUG 0
#define MAX(A,B) ((A)>(B) ? (A) : (B))
#define MIN(A,B) ((A)>(B) ? (B) : (A))

static int *a, *samples, *splitters, *tmp;
static int **counts, **startptrs;
static int nthreads, sectsize;
static unsigned long long totallen;
pthread_t *pool;
pthread_barrier_t barrier;

static void init();
static void teardown();
static void *runSort(void *data);
static void select_samples(const int tid);
static void copy_elements(const int tid);
static void count_elements(const int tid);
static void sort_elements(const int tid);
static void find_start_idxs(const int tid);
static int binary_search(int num, int *s, const int len);

// Initialize Shared resources 
static  void init() {
	int i;

	pool = (pthread_t*) malloc(sizeof(pthread_t) * nthreads);
	pthread_barrier_init(&barrier, NULL, nthreads);
	samples = (int *)malloc(sizeof(int) * SAMPLES * (nthreads - 1));
	splitters = (int *) malloc(sizeof(int) * nthreads - 1);
	tmp = (int *) malloc(sizeof(int) * totallen);
	counts = (int **) malloc(sizeof(int *) * nthreads);
	startptrs = (int **) malloc(sizeof(int *) * nthreads);
	for(i = 0; i < nthreads; i++) {
		counts[i] = (int *)calloc(nthreads, sizeof(int));
		startptrs[i] = (int *)calloc(nthreads, sizeof(int));
	}
	for(i = 0; i < totallen; i++) {
		tmp[i] = a[i];
	}
}

// free/destroy shared resources
static void teardown() {
	int i;
	for(i = 0; i < nthreads; i++) {
		free(counts[i]);
		free(startptrs[i]);
	}
	free(counts);
	free(pool);
	free(samples);
	free(splitters);
	free(tmp);
	pthread_barrier_destroy(&barrier);
}

/* Only a parallel version exists */
void sample_sort(int *arr, const size_t len, const int threads) {
	int i;
	a = arr;
	totallen = len;
	nthreads = threads;
	sectsize = (totallen / nthreads);
	init();

	for(i = 1; i < nthreads; i++) {
		pthread_create(&pool[i], NULL, runSort, (void *)i);
	}

	// Main thread
	runSort((void *)0);

	// Wait for threads to finish
	for(i = 1; i < nthreads; i++) {
		pthread_join(pool[i], NULL);
	}

	teardown();
}

static void *runSort(void *data) {
	int i;
	int tid = (int) data;
	// Better random numbers
	srand(time(NULL));


	// Wait until all threads initialized
	pthread_barrier_wait(&barrier);
	if(nthreads > 1) {
		select_samples(tid);
		pthread_barrier_wait(&barrier);
	// Sort the sample array using radix sort
		if(tid == 0) {
			radix_sort(samples, SAMPLES*(nthreads-1));
			// Copy array
			// print_array(samples, (nthreads - 1) * SAMPLES);
			for(i = 0; i < nthreads - 1; i++) {
				splitters[i] = samples[i*SAMPLES + SAMPLES/2];
			}
			// printf("Splitters (%d:%d)\n", SAMPLES, (int)totallen/(nthreads -1));
			// print_array(splitters, nthreads-1);
		}
		pthread_barrier_wait(&barrier);
		count_elements(tid);
		pthread_barrier_wait(&barrier);
		if(tid == 0) {
			find_start_idxs(tid);
		}
		pthread_barrier_wait(&barrier);
		copy_elements(tid);
		pthread_barrier_wait(&barrier);
		sort_elements(tid);
	}
	else {
		radix_sort(a, totallen);
	}
	return NULL;
}

/* Put samples into shared sample array */
static void select_samples(const int tid) {
	int samplesize = totallen / (nthreads - 1);
	int startidx = tid * samplesize;
	// printf("samplesize = %d\n", samplesize);
	int copyidx = tid * SAMPLES;
	int i;
	if(tid != (nthreads - 1)) {
		// Copy samples
		for(i = 0; i < SAMPLES; i++) {
			samples[copyidx+i] = a[startidx + (rand() % samplesize)];
		}
	}
}

/* Count elements from each subdivision */
static void count_elements(const int tid) {
	int i;
	if(tid != nthreads - 1) {
		for(i = 0; i < sectsize; i++) {
			int idx = binary_search(tmp[(tid*sectsize)+i], splitters, nthreads-1);
			// printf("binary search tmp[%d] = %d ==> %d\n", tid*sectsize+i, tmp[tid*sectsize+i], idx);
			counts[tid][idx]++;
			// printf("counts[%d][%d] = %d\n", tid, idx, counts[tid][idx]);
		}
	}
	else {
		int extra = totallen - sectsize*nthreads;
		for(i = 0; i < sectsize+extra; i++) {
			int idx = binary_search(tmp[(tid*sectsize)+i], splitters, nthreads-1);
			// printf("binary search tmp[%d] = %d ==> %d\n", tid*sectsize+i, tmp[tid*sectsize+i], idx);
			counts[tid][idx]++;
			// printf("counts[%d][%d] = %d\n", tid, idx, counts[tid][idx]);
		}

	}
}

/* Copy from temp array into array */
static void copy_elements(const int tid) {
	int i;
	int *localptrs = (int *)malloc(sizeof(int) * nthreads);
	for(i = 0; i < nthreads; i++) {
		localptrs[i] = startptrs[tid][i];
	}
	if(tid != nthreads-1) {
		for(i = 0; i < sectsize; i++) {
			int idx = (tid*sectsize)+i;
			int bin = binary_search(tmp[idx], splitters, nthreads-1);
			// printf("tmp[%d] = %d\tcopyto a[%d]\n", idx, tmp[idx], localptrs[bin]);
			a[localptrs[bin]++] = tmp[idx];
		}
	}
	else {
		int extra = totallen - sectsize*nthreads;
		for(i = 0; i < sectsize+extra; i++) {
			int idx = (tid*sectsize)+i;
			int bin = binary_search(tmp[idx], splitters, nthreads-1);
			// printf("tmp[%d] = %d\tcopyto a[%d]\n", idx, tmp[idx], localptrs[bin]);
			a[localptrs[bin]++] = tmp[idx];
		}
	}

	free(localptrs);
}

static void sort_elements(const int tid) {
	int elts = 0, i;
	for(i = 0; i < nthreads; i++) {
		elts += counts[i][tid];
	}
#if DEBUG
	printf("%d: elts=%d\n", tid, elts);
#endif
	radix_sort(&a[startptrs[0][tid]], elts);
}

static void find_start_idxs(const int tid) {
	int i, j; 
	int idx = 0;
	for(j = 0; j < nthreads; j++) {
		for(i = 0; i < nthreads; i++) {
			startptrs[i][j] = idx;
			idx += counts[i][j];
		}
	}
	// printf("idx (%d) == totallen (%llu)\n", idx, totallen);
}

/* Return the bin the num should go in */
static int binary_search(int num, int *s, const int len) {
	int low = 0;
	int high = len;
	int idx;
	while(low < high) {
		idx = (high + low) / 2;
		if(num < s[idx]) {
			high = idx;
		}
		else {
			low = idx + 1;
		}
	}
	if(len > 0) {
		if(num >= s[idx]) {
			return idx + 1;
		}
	}
	return idx;
}

