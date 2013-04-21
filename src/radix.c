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

// static void init();
// static void teardown();

typedef unsigned uint;

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
	each(i, len) x[i] ^= INT_MIN;
	rad_sort_u(x, x+len, INT_MIN);
	each(i, len) x[i] ^= INT_MIN;
}
