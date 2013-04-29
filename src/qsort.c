#include <stdio.h>
#include <stdlib.h>

static int comp(const void *a, const void *b) {
	const int ia = *((int *)a);
	const int ib = *((int *)b);
	if(ia > ib) { return 1;  }
	if(ia < ib) { return -1; }
	return 0; // Equal
}

/* Uses the built in qsort from stdlib and the compare function above */
void qsort_wrapper(int *a, const size_t len) {
	qsort(a, len, sizeof(int), comp);
}
