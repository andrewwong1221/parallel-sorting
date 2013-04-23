/* 
 * Code largely based off the sample implementation
 * provided by fh-flensburg.de:
 * http://www.iti.fh-flensburg.de/lang/algorithmen/sortieren/bitonic/bitonicen.htm
 *
 * WARNING: Only sorts array of len = 2^k
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "sort.h"

#define ASCENDING 1
#define DESCENDING 0
#define MIN(a,b) ((a)<(b) ? (a) : (b))
#define MAX(a,b) ((a)<(b) ? (b) : (a))

void bitonicSort(int lo, int n, int dir);
void bitonicMerge(int lo, int n, int dir);
void compare(int i, int j, int dir);
void swap(int i, int j);
void *runSort(void *data);


static int *a;
static int nthreads;
static unsigned long long totallen;
pthread_t *pool;
pthread_barrier_t barrier;

// Initialize shared resources
static void init() {
	pool = (pthread_t *)malloc(sizeof(pthread_t) * (nthreads));
	pthread_barrier_init(&barrier, NULL, nthreads);
}

// free/destroy shared resources
static void teardown() {
	free(pool);
	pthread_barrier_destroy(&barrier);
}

// Call the sort function
void bitonic_sort(int *arr, const size_t len) {
	bitonic_psort(arr, len, 1);
}

// Parallel bitonic sort method
void bitonic_psort(int *arr, const size_t len, const int threads) {
	int i;
	nthreads = threads;
	totallen = len;
	a = arr;
	init();

	for(i = 1; i < nthreads; i++) {
		pthread_create(&pool[i], NULL, runSort, (void *)i);
	}
	runSort((void *) 0);
	for(i = 1; i < nthreads; i++) {
		pthread_join(pool[i], NULL);
	}

	teardown();
}

// Assigns work to a particular thread id
void *runSort(void *data) {
	int tid = (int) data;
	// printf("Hello from tid %d\n", tid);
	pthread_barrier_wait(&barrier);
	// Start timer?
	int sectionsize = totallen / nthreads;
	bitonicSort(sectionsize * tid, sectionsize, (tid+1)%2);
	
	// Merge
	int i;
	// De
	for(i = nthreads / 2; i > 0; i /= 2) {
		pthread_barrier_wait(&barrier);
		if(tid < i) {
			int length = totallen / i;
			int start = tid*length;
			// int end = start + length;
			// fprintf(stderr, "%d: Merging: %d - %d, %d, %d\n", tid, start, end, length, (tid+1)%2);
			// Merge results from two threads
			bitonicMerge(start, length, (tid+1)%2);
		}
		else {
			// Do nothing if thread is not needed
			// printf("Thread %d waiting\n", tid);
		}
	}
	return NULL;
}

// Sort the array
void bitonicSort(int lo, int n, int dir) {
	// printf("bitonicSort(lo=%d, n=%d, dir=%d)\n", lo, n, dir);
	// do nothing if n <= 1 (nothing to sort)
	if(n > 1) {
		int m = n/2;
		bitonicSort(lo, m, ASCENDING);
		bitonicSort(lo+m, m, DESCENDING);
		bitonicMerge(lo, n, dir);
	}
}

void bitonicMerge(int lo, int n, int dir) {
	if(n > 1) {
		int m = n/2;
		int i;
		for(i = lo; i < lo+m; i++)
			compare(i, i+m, dir);
		bitonicMerge(lo, m, dir);
		bitonicMerge(lo+m, m, dir);
	}
}

// Compare two different indices and swap based on current direction
void compare(int i, int j, int dir) {
	if(dir == (a[i]>a[j]))
		swap(i, j);
}


// Swap two indices in the array
void swap(int i, int j) {
	int t = a[i];
	a[i] = a[j];
	a[j] = t;
}
