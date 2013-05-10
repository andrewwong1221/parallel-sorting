#include <stdio.h>
#include <stdlib.h>
#include "sort.h"
#include "utils.h"

#define MAX(A,B) ((A)>(B) ? (A) : (B))
#define MIN(A,B) ((A)>(B) ? (B) : (A))

static void insertion_sorter(int *a, const size_t len, int dec);

void insertion_sort(int *a, const size_t len) {
	insertion_sorter(a, len, 0);
}
void rev_insertion_sort(int *a, const size_t len) {
	insertion_sorter(a, len, 1);
}

static void insertion_sorter(int *a, const size_t len, int dec) {
	int i, j, temp;
	for(i = 1; i < len; i++) {
		j = i;
		// Don't sort once in order with last number because
		// everything below is already sorted
		while(j > 0 && ((a[j-1] < a[j]) == dec)) {
			// Swap numbers
			temp = a[j];
			a[j] = a[j-1];
			a[j-1] = temp;
			j--;
		}
	}
}

