/*
 * Code for sequential radix sort largely based off of the examples listed on
 * http://rosettacode.org/wiki/Sorting_algorithms/Radix_sort
 */
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <pthread.h>
#include "sort.h"
#include "utils.h"
#define swap(a,b) { tmp = a; a = b; b = tmp; }
#define each(i,x) for(i = 0; i < x; i++)

#define MAX 10
#define SHOWPASS

typedef unsigned uint;

// static void init();
// static void teardown();
// void *runSort(void *data);


pthread_t *pool;
pthread_barrier_t barrier;
// static int *a;
// static unsigned long long totallen;
// static int nthreads;

static void rad_sort_u(uint *from, uint *to, uint bit) {
	if(!bit || to < from + 1) return;
	uint *ll = from, *rr = to - 1, tmp;
	while(1) {
		while(ll < rr && !(*ll & bit)) ll++;
		while(ll < rr && (*rr & bit)) rr--;
		if(ll >= rr) break;
		swap(*ll, *rr);
	}
	if(!(bit & *ll) && ll < to) ll++;
	bit >>= 1;
	rad_sort_u(from, ll, bit);
	rad_sort_u(ll, to, bit);
}

static inline void radix_sort_unsigned(uint *a, const size_t len) {
	rad_sort_u(a, a+len, (uint)INT_MIN);
}

void radix_sort(int *a, const size_t len)
{
	size_t i;
	uint *x = (uint*) a;
	// Flip negative signs so sorting works properly
	each(i, len) x[i] ^= INT_MIN;
	// Sort unsigned
	rad_sort_u(x, x+len, INT_MIN);
	// Flip negative signs back 
	each(i, len) x[i] ^= INT_MIN;
}

/* Parallel radix sort should sort from the lsb to the msb */
void radix_psort(int *arr, const size_t len, const int threads) {
	// int i;
	// a = arr;
	// totallen = len;
	// nthreads = threads;
	// init();

	// for(i = 1; i < nthreads; i++) {
	// 	pthread_create(&pool[i], NULL, runSort, (void *)i);
	// }
	// runSort((void *) 0);
	// for(i = 1; i < nthreads; i++) {
	// 	pthread_join(pool[i], NULL);
	// }

	// teardown();
}

// void *runSort(void *data) {
// 	int tid= (int) data;
// 	pthread_barrier_wait(&barrier);
// 	
// 
// }
// 
// void init() {
// 	pool = (pthread_t *)malloc(sizeof(pthread_t) * nthreads);
// 	pthread_barrier_init(&barrier, NULL, nthreads);
// }
// 
// 
// void teardown() {
// 	free(pool);
// 	pthread_barrier_destroy(&barrier);
// }
